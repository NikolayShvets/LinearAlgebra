#ifndef WN_H
#define WN_H
#include <random>
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>


class white_noise
{
public:
	white_noise();
	~white_noise();
	long double white_noise_nu;
	long double t_corr;
	long double w = 1000;
	long double get_nu(long double time);
	long double white_noise_generator();
	long double nu0 = 0;
	long double time_temp = 0;
	int temp = 0;
};

#endif // WN_H
