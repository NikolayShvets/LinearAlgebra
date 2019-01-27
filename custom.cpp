#include "custom.h"
#include <math.h>
#include "model.h"
#include <iostream>



using namespace std;
int sgn(long double val)
{
   return (val>0)?(1):((val<0)?(-1):(0));
}

TArenstorfModel2::TArenstorfModel2(): TArenstorfModel()
{
	X0[0] = 0.994;//y1
	X0[1] = 0;//y2
	X0[2] = 0;//y1'
	X0[3] = -2.0317326295573368357302057924;//y2'
}

void TArenstorfModel2::do_thing(const TVector& X, long double t) {}

const long double TArenstorfModel::m = 0.012277471;
TArenstorfModel::TArenstorfModel():TModel()
{
	X0.resize(4);
	X0[0] = 0.994; //y1
	X0[1] = 0;     //y2
	X0[2] = 0;     //y1'
	X0[3] = -2.00158510637908252240537862224; //y2'	
}
void TArenstorfModel::do_thing(const TVector& X, long double t) {}


void TArenstorfModel::getRight(const TVector& X, long double t, TVector& Y)
{	
	Y.resize(4);
	long double D1 = pow(pow(X[0]+m,2)+pow(X[1],2),1.5);
	long double D2 = pow(pow(X[0]-(1-m),2)+pow(X[1],2),1.5);
	Y[0] = X[2];
	Y[1] = X[3];
	/*y1''*/Y[2] = X[0]+2*X[3]-(1-m)*(X[0]+m)/D1-m*(X[0]-(1-m))/D2;
	/*y2''*/Y[3] = X[1]-2*X[2]-(1-m)*X[1]/D1-m*X[1]/D2;
}

TRealMathPendulum::TRealMathPendulum():TModel()
{
	X0.resize(2);
	X0[0] = 0;//0.5236;//angle
	X0[1] = 1;//angle'
}

void TRealMathPendulum::do_thing(const TVector& X, long double t) {}

void TRealMathPendulum::getRight(const TVector& X, long double t, TVector& Y)
{
	double h = l*(1 - cos(X[0]));
	double Ec = 0.5*m*powl(X[1]*l,2)+m*g*powl(l*sin(X[0]),2)/(2*l);//1/4*k*powl(l*sin(X[0]),2)*(1+cos(2*powl(k/m,2)));
	double Ep ; //1/4*k*powl(l*sin(X[0]),2)*(1-cos(2*powl(k/m,2)));
	Y.resize(2);
	Y[0] = X[1];
	Y[1] = -g/l*sin(X[0]) - dE*X[1];
	//x' = t
	// t'+w^2sin[x]
}

TRealPhisPendulumTS::TRealPhisPendulumTS():TModel()
{
	X0.resize(2);
	X0[0] = 2;
	X0[1] = 0;
}

void TRealPhisPendulumTS::do_thing(const TVector& X, long double t) {}

void TRealPhisPendulumTS::getRight(const TVector& X, long double t, TVector& Y)
{
	Y.resize(2);
	Y[0] = X[1];
	Y[1] = (-k*X[0] - sgn(X[1])*mu*g*m)/m;
}


TLinearizeModel::TLinearizeModel():TModel()
{
	X0.resize(6);
	X0[0] = 0;
	X0[1] = 0;
	X0[2] = 0;
	X0[3] = 0;
	X0[4] = 0;
	X0[5] = 0;
}

void TLinearizeModel::getRight(const TVector& X, long double t, TVector& Y)
{
	cout<<"v==> "<<test_nu<<endl;
	Y.resize(6);
	Y[0] = X[1];
	Y[1] = 1./powl(Tff,2)*(Kff*test_nu-2.*X[1]*Tff*xiff-X[0]);
	Y[2] = 1./T3*((calc_f1(0, X[0]-X[4]*K7)*K1-X[5]*K6)*K2*K3-X[2]);
	Y[3] = calc_f2(0, X[2])*K4;
	Y[4] = X[5];
	Y[5] = 1./powl(T4, 2)*(X[3]-2.*T4*xi4*X[5]-X[4]);
	///////////////////////////////////////////////////
}
long double TLinearizeModel::func_1(long double arg)
{	
	if(arg < -s_1-z/2.)
		return -s_1;
	if (arg < -z/2.)
		return arg + z/2.;
	if (arg < z/2.)
		return 0.0;
	if (arg < s_1+z/2.)
		return arg - z/2.;
	if (arg >=s_1  + z/2.)
		return s_1;
}
long double TLinearizeModel::func_2(long double arg)
{
	
	derivat = arg - argprev; 
	if((arg > z_2/2+s_2))
		temp = s_2;
	else if ((arg >= -s_2-z_2/2.)&&(arg < z_2/2.-s_2)&&(derivat > 0.0))
		temp = -s_2;
	else if ((arg >= z_2/2.-s_2)&&(arg < s_2+z_2/2.) && (derivat > 0.0))
		temp = arg - z_2/2.;
	else if ((arg >= s_2-z_2/2.)&&(arg < s_2+z_2/2.)&&(derivat < 0.0))
		temp = s_2;
	else if ((arg < -s_2-z_2/2.))
		temp = -s_2;
	else if ((arg >=-s_2-z_2/2.) && (arg < s_2-z_2/2.) && (derivat < 0.0))
		temp = arg + z_2/2.;
	else temp = 0.0;
	return temp;
	
}
long double TLinearizeModel::calc_f1(int c, long double arg)
{
	switch(c) {
		case 0: /*cout<<"lin_1_case_0==> "<<func_1(arg)<<endl;*/ return func_1(arg);
		case 1: /*cout<<"lin_1_case_1==> "<<Klin_1*arg<<endl;*/return Klin_1*arg;
		default: return 0;
	}
}
long double TLinearizeModel::calc_f2(int c, long double arg) 
{
	switch(c) {
		case 0: /*cout<<"lin_2_case_0==> "<<func_2(arg)<<endl;*/return func_2(arg);
		case 1: /*cout<<"lin_2_case_1==> "<<Klin_2*arg<<endl;*/return Klin_2*arg;
		default: return 0;
	}
}
void TLinearizeModel::do_thing(const TVector& X, long double t) {
	argprev = X[2];
}


