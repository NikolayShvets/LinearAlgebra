#pragma once
class WhiteNoise
{
public:
	long double white_noise_nu;
	long double t_corr;
	long double w = 1000;
	long double get_white_noise_nu(long double time);
};