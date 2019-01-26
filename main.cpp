#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "LinearAlgebra.h"
#include "integrator.h"
#include "custom.h"
using namespace std;

void ShowResult(TModel* Model)
{
	ofstream result_file("integrations_result.txt");
	TIntegrator* Integrator = new TDormandPrinceIntegrator();
	Integrator->setPrecision(1e-16);
	Integrator->Run(Model);
	TMatrix Result = Model->getResult();
	 for (int i=0; i<Result.rowCount(); i++)
        {
            for (int j=0; j<Result.colCount(); j++)
            {
				if (j >= Model->getOrder()+1) 
					break;
				if (j < Result.colCount()-2) result_file << Result(i,j) << "|";
				else result_file << Result(i, j);
            }
			result_file << endl;
		}
		result_file.close();
		delete Integrator;
		
}

int main(int argc, char **argv)
{
	//printf("hello world\n");
	//TModel* Model1 = new /*TRealPhisPendulumTS();*//*TLinearizeModel();*//*TRealMathPendulum();*/TArenstorfModel();
	//ShowResult(Model1);
	//delete Model1;
	
	TMatrix R(3,3), M(3,3);
	R(0,0) = 1;
	R(0,1) = 2;
	R(0,2) = 3;
	R(1,0) = 4;
	R(1,1) = 8;
	R(1,2) = 10;
	R(2,0) = 7;
	R(2,1) = 8;
	R(2,2) = 9;
	cout<<"     Исходная матрица: "<<endl<<endl;
	for (int i = 0; i < R.n; i++)
	{
		for(int j = 0; j < R.n; j++)
		{
			cout<<"     "<<R(i,j);
		}
		cout << endl;
	}
	cout<<endl;
	M = R;
	R.xhol(R);
	cout<<"     Разложение Холецкого: "<<endl<<endl;
	for (int i = 0; i < R.n; i++)
	{
		for(int j = 0; j < R.n; j++)
		{
			cout<<"     "<<R(i,j);
		}
		cout << endl;
	}
	cout<<endl;
	cout<<"Обращение методом Гаусса: "<<endl;
	M = !M;
	for (int i = 0; i < M.n; i++)
	{
		for(int j = 0; j < M.n; j++)
		{
			cout<<M(i,j)<<"|";
		}
		cout << endl;
	}
	cout<<"Перестановка строк: "<<endl;
	M.swapRows(1,2);
	for (int i = 0; i < M.n; i++)
	{
		for(int j = 0; j < M.n; j++)
		{
			cout<<M(i,j)<<"|";
		}
		cout << endl;
	}
	cout<<endl;
	cout<<"Определитель матрицы: "<<endl;
	TMatrix Q(3,3);
	Q(0,0) = 3;
	Q(0,1) = 0;
	Q(0,2) = 7;
	Q(1,0) = 1;
	Q(1,1) = 0;
	Q(1,2) = 9;
	Q(2,0) = 2;
	Q(2,1) = 0;
	Q(2,2) = 1;
	cout<<Q.det()<<endl;
	cout<<endl;
	cout<<"Разложение Холецкого: "<<endl;
	Q.xhol(Q);
	for (int i = 0; i < Q.n; i++)
	{
		for(int j = 0; j < Q.n; j++)
		{
			cout<<Q(i,j)<<"|";
		}
		cout << endl;
	}
	return 0;
}
