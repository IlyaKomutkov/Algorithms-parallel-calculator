#include "linalg.hpp"
#include "KMetrics.hpp"

long double ManhattanDist::distance(std::valarray<long double> v1, std::valarray<long double> v2)
{
	long double s = 0;
	for (size_t i{ 0 }; i < v1.size(); ++i)
		s += abs(v1[i] - v2[i]);
	return s;
}


long double ChebyshevDist::distance(std::valarray<long double> v1, std::valarray<long double> v2)
{
	long double s = 0;
	for (size_t i{ 0 }; i < v1.size(); ++i)
		s = std::max(s, abs(v1[i] - v2[i]));
	return s;
}

long double MinkowskiDist::distance(std::valarray<long double> v1, std::valarray<long double> v2)
{
	long double s = 0;
	for (size_t i{ 0 }; i < v1.size(); ++i)
		s += pow(pow(abs(v1[i] - v2[i]), power_), 1 / power_);
	return s;
}

long double EuclidDist::distance(std::valarray<long double> v1, std::valarray<long double> v2)
{
	long double s = 0;
	for (size_t i{ 0 }; i < v1.size(); ++i)
		s += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	return sqrt(s);
}
