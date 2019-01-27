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
    ofstream result_file("/home/nikonikoni/LinearAlgebra/integrations_result.txt");
    cout<<result_file.is_open()<<endl;
	TIntegrator* Integrator = new TDormandPrinceIntegrator();
    Integrator->setPrecision(1e-10);
    cout<<"test1"<<endl;
	Integrator->Run(Model);
    cout<<"test2"<<endl;
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
    printf("hello world\n");
    cout<<"test3"<<endl;
    TModel* Model1 = new /*TRealPhisPendulumTS();*//*TLinearizeModel();*//*TRealMathPendulum();*/TArenstorfModel();
    cout<<"test4"<<endl;
    ShowResult(Model1);
    delete Model1;
	return 0;
}
