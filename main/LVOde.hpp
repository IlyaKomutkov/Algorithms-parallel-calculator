#pragma once


#include "linalg.hpp"


class ODE {
public:
	virtual std::valarray<long double> operator()(long double t, std::valarray<long double> s) = 0;
};



class LVOde:public ODE{
private:
	long double a, b, c, d;	// L-V constants
public:
	LVOde() : a(0), b(0), c(0), d(0){};
	LVOde(long double A, long double B, long double C, long double D) : a(A), b(B), c(C), d(D){};
	// take time and vector-condition s0
	// and return new vector-condition ds
	std::valarray<long double> operator()(long double t, std::valarray<long double> s){
		std::valarray<long double> ds(s.size());
		ds[0] = (a - b * s[1]) * s[0];
		ds[1] = (-c + d * s[0]) * s[1];
		return ds;
	}
};
