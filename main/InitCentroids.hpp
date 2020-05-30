#pragma once


#include "linalg.hpp"
#include "KMetrics.hpp"


class CentroindsInitializer {
public:
	virtual void const initCentroids(std::vector<std::valarray<long double>>& centroids, \
		Matrix<long double> data, Metrics* metric) = 0;
};

// randomly selected points
//
class RandomCentroindsInitializer: public CentroindsInitializer {
private:
	bool valarray_compare(std::valarray <long double> lhs, std::valarray <long double> rhs);

public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, \
		Matrix<long double> data, Metrics* metric) override;
};



// farthest points(simple selection)
class LargestCentroindsInitializer : public CentroindsInitializer {
	// comparison two valarray because valarray operator== return valarray<bool>
	bool valarray_compare(std::valarray <long double> lhs, std::valarray <long double> rhs);

	// sum of the distances to a new point
	long double max_metric(std::vector<std::valarray<long double>> temp, \
		std::valarray<long double> tmp2, Metrics* metric, size_t n);

	// check for a match with a new item
	bool coincidence(std::vector<std::valarray<long double>> temp, std::valarray<long double> pam, size_t n);

	// check previously used values
	bool usedDataCheck(std::vector <size_t> vec, size_t n);
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, \
		Matrix<long double> data, Metrics* metric) override;
};


class KFirstCentroindsInitializer: public CentroindsInitializer {
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, \
		Matrix<long double> data, Metrics* metric) override;
};