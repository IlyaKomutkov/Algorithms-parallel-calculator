#pragma once 

#include "LVOde.hpp"


class ThreeBodiesODE :public ODE {
private:
	std::valarray<long double> gm; // three body constants g*m1, g*m2 and g*m3
public:
	ThreeBodiesODE(std::valarray<long double>);
	// take time and vector-condition s0
	// and return new vector-condition ds
	std::valarray<long double> operator()(long double, std::valarray<long double>);
};

class TwoBodiesODE :public ODE {
private:
	std::valarray<long double> gm ;
public:
	TwoBodiesODE(std::valarray<long double>);
	std::valarray<long double> operator()(long double, std::valarray<long double>);
};