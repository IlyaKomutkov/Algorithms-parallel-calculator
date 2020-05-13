#pragma once

#include "linalg.hpp"

class RKMethod{
private:
	// contain constats for certain RK method
	Matrix<long double> A;
	std::valarray<long double> c;
	std::valarray<long double> b_main;
	std::valarray<long double> b_subs;
public:
	// take constants from Butcher-table
	RKMethod(std::string path, std::valarray<long double> vecC, 
			 std::valarray<long double> vecB_main, std::valarray<long double> vecB_subs) : 
	A(path), c(vecC), b_main(vecB_main), b_subs(vecB_subs){};

	// simple "getters"
	Matrix<long double> 	   getA()	   const{return A;}
	std::valarray<long double> getC() 	   const{return c;}
	std::valarray<long double> getB_main() const{return b_main;}
	std::valarray<long double> getB_subs() const{return b_subs;}
};
