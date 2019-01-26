#include "WN.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;


white_noise::white_noise()
{
	t_corr = 2*3.14159/w;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


long double white_noise::get_nu(long double time)
{
	
	ifstream WNFile("/home/nikonikoni/Документы/clprojects/oprs/LAB_2/lab__2/WhiteNoise/Debug/WNFile.txt");
	string str;
	getline(WNFile, str);
	vector<string> nu_time = split(str, '|');
	int number = (int)(time/t_corr)*2+1;
	double res = stod(nu_time[number]);
	//cout<<res<<endl;
	return res;
}



long double white_noise::white_noise_generator()
{
	long double D = 1/t_corr;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<double> distribution(/*mean=*/0.0, /*stddev=*/1.0);
	nu0 = distribution(generator)*powl(D,0.5);
	return nu0;
}

white_noise::~white_noise()
{
	
}