#include "WhiteNoise.h"
#include <random>
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>

long double WhiteNoise::get_white_noise_nu(long double time)
{
	// construct a trivial random generator engine from a time-based seed:
	t_corr = 2*3.14159/w;
	long double D = 1/t_corr;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::normal_distribution<double> distribution (0.0,1.0);
	long double temp = distribution(generator)*powl(D,0.5);
	return temp;
}