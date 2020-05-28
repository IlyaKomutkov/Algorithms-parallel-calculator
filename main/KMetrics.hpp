#pragma once

#include "linalg.hpp"


class Metrics {
public:
	Metrics() {}
	virtual ~Metrics() {}
	virtual long double distance(std::valarray<long double> v1, std::valarray<long double> v2) = 0;
};


//Manhattan distance
class ManhattanDist : public Metrics
{
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override {
		//std::cout << "ManhattanDist" << std::endl;
		long double s = 0;
		for (size_t i {0}; i < v1.size(); ++i)
		s += abs(v1[i] - v2[i]);
		return s;
	}
};


//Chebyshev distance
class ChebyshevDist : public Metrics {
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override {
		//std::cout << "ChebyshevDist" << std::endl;
		long double s = 0;
		for (size_t i{ 0 }; i < v1.size(); ++i)
			s = std::max(s, abs(v1[i] - v2[i]));
		return s;
	}
};


//Minkowski distance
class MinkowskiDist : public Metrics {
	long double power_ = 1;
public:
	MinkowskiDist(long double pow) : power_{ pow } { }
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override {
		//std::cout << "MinkowskiDist" << std::endl;
		long double s = 0;
		for (size_t i{ 0 }; i < v1.size(); ++i)
		 	s += pow(pow(abs(v1[i] - v2[i]), power_), 1 / power_);
		return s;
	}
};


//Euclid distance
class EuclidDist : public Metrics {
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override {
		long double s = 0;
		for (size_t i{ 0 }; i < v1.size(); ++i)
			s += (v1[i] - v2[i]) * (v1[i] - v2[i]);
		return sqrt(s);
	}
};
