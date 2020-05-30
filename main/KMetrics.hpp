#pragma once


class Metrics {
public:
	Metrics() {}
	virtual ~Metrics() {}
	virtual long double distance(std::valarray<long double> v1, std::valarray<long double> v2) = 0;
};


// Manhattan distance
class ManhattanDist : public Metrics
{
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override;
};


// Chebyshev distance
class ChebyshevDist : public Metrics {
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override;
};


// Minkowski distance
class MinkowskiDist : public Metrics {
	long double power_ = 1;
public:
	MinkowskiDist(long double pow) : power_{ pow } { }
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override;
};


// Euclid distance
class EuclidDist : public Metrics {
public:
	long double distance(std::valarray<long double> v1, std::valarray<long double> v2) override;
};
