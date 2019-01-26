#pragma once
#include "model.h"
#include <fstream>
#include "WN.h"

class TArenstorfModel:public TModel
{
protected:
	static const long double m;
	//long double D1, D2;
public:
	TArenstorfModel();
	void getRight(const TVector& X, long double t, TVector& Y);
	/////////////////////////////////////
	void do_thing(const TVector& X, long double t);
};

class TRealMathPendulum:public TModel
{
protected:
	long double m = 1;
	long double g = 9.81;
	long double l = 1;
	long double dE = 0.8;
public:
	TRealMathPendulum();
	void getRight(const TVector& X, long double t, TVector& Y);
	////////////////////////////
	void do_thing(const TVector& X, long double t);
};

class TRealPhisPendulumTS: public TModel
{
protected:
	long double mu = 0.015;
	long double k = 1;
	long double m = 1;
	long double g = 9.81;
public:
	TRealPhisPendulumTS();
	void getRight(const TVector& X, long double t, TVector& Y);
	/////////////////////////
	void do_thing(const TVector& X, long double t);
};

class TArenstorfModel2: public TArenstorfModel
{
public:
	TArenstorfModel2();
	/////////////////////////
	void do_thing(const TVector& X, long double t);
};


class TLinearizeModel : public TModel
{
protected:
	double s_1 = 2; double z = 0.05/*0.5*/;
	double s_2 = 2; double z_2 = 0.01;/*0.5*/;
	double K1 = 1; double K2 = 1;
	double K3 = 1; double K4 = 1;
	double K5 = 0.2; double K6 = 1; double K7 = 1;
 	double T3 = 5; double T4 = 0.01; double T5 = 0.02;
	double xi4 = 0.1;
	double Kff = 0.09999210524 ; double Tff = 0.009999210525; double xiff = 0.9999210525;
	double Klin_1 = 0.647494; double Klin_2 = 0.999999;
	long double derivat; long double argprev = 0; long double nu;
	long double t_corr;
	long double w = 1000;
	long double X_buf = 0;
	bool flag = false;
	double temp;
	int counter = 0;
public:
	TLinearizeModel();
	white_noise wn;
	//white_noise wn;
	void getRight(const TVector& X, long double t, TVector& Y);
	long double func_1(long double arg); //первая нелинейность
	long double func_2(long double arg);//вторая нелинейность 
	long double calc_f1(int c, long double arg);
	long double calc_f2(int c, long double arg);
	/////////////////////////////
	void do_thing(const TVector& X, long double t);
};