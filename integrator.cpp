#include <stdio.h>
#include <math.h>
#include "integrator.h"
#include "model.h"
#include <iostream>
#include <fstream>
using namespace std;

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

const long double TDormandPrinceIntegrator::c[7] = { 0.0, 1.0/5, 3.0/10, 4.0/5, 8.0/9, 1.0, 1.0 };
const long double TDormandPrinceIntegrator::a[7][6] = {
            { },
            { 1.0/5 },
            { 3.0/40, 9.0/40 },
            { 44.0/45, -56.0/15, 32.0/9 },
            { 19372.0/6561, -25360.0/2187, 64448.0/6561, -212.0/729 },
            { 9017.0/3168, -355.0/33, 46732.0/5247, 49.0/176, -5103.0/18656 },
            { 35.0/384, 0.0, 500.0/1113, 125.0/192, -2187.0/6784, 11.0/84 }
		};

const long double TDormandPrinceIntegrator::b1[7] = { 35.0/384, 0.0, 500.0/1113, 125.0/192, -2187.0/6784, 11.0/84, 0.0 };
const long double TDormandPrinceIntegrator::b2[7] = { 5179.0/57600, 0.0, 7571.0/16695, 393.0/640, -92097.0/339200, 187.0/2100, 1.0/40 };

TDormandPrinceIntegrator::TDormandPrinceIntegrator(): TIntegrator() 
{
	double v = 1.;
	while (1.+v > 1.){ 
		u = v;
		v = v/2.;
	} 
}

long double TDormandPrinceIntegrator::Run(TModel* model)
{
	
	white_noise wn;
	
	long double
		t = model->getT0(),
		t_out = t,
		t1 = model->getT1(),
		h,
		h_new = model->getSamplingIncrement(),
		e = 0;
	TVector // Это вектор состояния на начало шага
		X = model->getInitialConditions(),
		// Это вектор состояния на конец шага (решение 4-го порядка)
		X1(X.size()),
		// Это вектор состояния на конец шага для коррекции величины шага (решение 5-го порядка)
		X2(X.size()),
		// Это вектор для выдачи результата
		Xout(X.size()),
		// Это буфер для вычисления коэффициентов К
		Y(X.size());
		
		ofstream test_file("integrations_test.txt");
		
	model->prepareResult();
	
	for ( int j = 7; j > 0; --j, K[j].resize(X.size()));
	int N = 0;
	
	while (t < t1){
		h = h_new;

        for(int i = 0; i < 7; i++){
            for(int j = 0; j <= X.high(); j++){
                Y[j] = X[j];
                for(int k = 0; k < i; k++){
                    Y[j]=Y[j]+K[k][j]*a[i][k]*h;
                    //cout<<Y[j]<<endl;
                }
                //cout<<"********"<<endl;
            }
            model->getRight(Y, t + c[i]*h, K[i]);
        }
        //новые значения результатов и локальной ошибки
        e = 0;
        for(int i = 0; i <= X.high(); i++){
            X1[i] = X[i];
            X2[i] = X[i];
            for(int j = 0; j < 7; j++){
                X1[i] = X1[i] + K[j][i]*b1[j]*h;
                //cout<<X1[i]<<endl;
                X2[i] = X2[i] + K[j][i]*b2[j]*h;
            }
            e+=powl(h*(X1[i]-X2[i])/max(max(fabsl(X[i]),fabsl(X1[i])),max((long double)1e-5, u/Eps)),2);

        }
        e = sqrtl(e/X.size());//выводить ошибку
        cout<<"error==> "<<e<<endl;
		//коррекция шага
        h_new = h/max(0.1, min(5., powl(e/Eps,0.2)/0.9));

		if(e > Eps)
			continue;
		

        //формируем результат плотной выдачей
        while((t_out < t + h)&&(t_out <= t1)){
            long double theta = (t_out - t)/h, b[6];
            b[0] = theta*(1+theta*(-1337.0/480.+theta*(1039.0/360.+theta*(-1163./1152.))));
            b[1] = 0;
            b[2] = 100.*powl(theta,2)*(1054./9275.+theta*(-4682./27825.+theta*(379./5565.)))/3.;
            b[3] = -5.*powl(theta,2)*(27./40.+theta*(-9.0/5+theta*(83.0/96)))/2.;
            b[4] = 18225.*powl(theta,2)*(-3./250.+theta*(22./375.+theta*(-37./600.)))/848.;
            b[5] = -22.*powl(theta,2)*(-3./10.+theta*(29./30.+theta*(-17./24.)))/7.;


            //результат выдачи
            for(int i = 0; i <= X.high(); i++){
                long double summa = 0;
                for(int j = 0; j <=5; j++)
                    summa = summa+b[j]*K[j][i];
                Xout[i] = X[i]+h*summa;
            }

            //передаем результат в модель
            model->addResult(Xout, t_out);
            t_out+=model->getSamplingIncrement();
        }
        X = X1;
		t+=h;
        cout<<"time==> "<<t<<endl;
		model->T = t_out;
		model->test_nu = wn.get_nu(model->T);
        //model->do_thing(X, t);
          //  for (int i = 0; i < X.length(); i ++) test_file << "X[" << i << "] = " << X[i] << "|";
            //test_file << endl;
		
		N++;
	}
	
    return Eps / pow( N, 1.5 );
}
