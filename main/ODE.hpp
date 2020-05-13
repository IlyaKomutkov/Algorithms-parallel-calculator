#pragma once 

#include "linalg.hpp"



class ODE{
private:
	std::valarray<long double> gm; // three body constants g*m1, g*m2 and g*m3
public:
	ODE(std::valarray<long double>);
	// take time and vector-condition s0
	// and return new vector-condition ds
	std::valarray<long double> operator()(long double, std::valarray<long double>);
};
