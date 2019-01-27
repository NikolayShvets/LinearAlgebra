#pragma once
#include "LinearAlgebra.h"
#include "model.h"
#include "WN.h"

class TModel;

class TIntegrator
{
protected:
	long double Eps;
public:
	TIntegrator():Eps(1e-16){}
	inline void setPrecision(long double Eps){this->Eps = Eps;}
	inline long double getPrecision()const {return Eps;}
	virtual long double Run(TModel* model) = 0;
};

class TDormandPrinceIntegrator: public TIntegrator
{
private:
	static const long double c[7], a[7][6], b1[7], b2[7];
	TVector K[7];
	long double u;
public:
	TDormandPrinceIntegrator();
	long double Run(TModel* model);
};
