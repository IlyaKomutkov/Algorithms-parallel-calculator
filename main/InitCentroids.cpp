#include "InitCentroids.hpp"
#include "linalg.hpp"
#include "KMetrics.hpp"

#include <ctime>
#include <random>


bool RandomCentroindsInitializer::valarray_compare(std::valarray <long double> lhs, std::valarray <long double> rhs) {
	size_t compare = 0;
	for (size_t i{ 0 }; i < lhs.size(); ++i)
		if (lhs[i] == rhs[i])
			compare++;
	if (compare == lhs.size())
		return true;
	else
		return false;
}

void const RandomCentroindsInitializer::initCentroids(std::vector<std::valarray<long double>>& centroids, \
	Matrix<long double> data, Metrics* metric) {
	srand((unsigned)time(0));
	for (size_t i{ 0 }; i < centroids.size(); ++i)
	{
		centroids[i] = data[rand() % data.getRows()];
		if (i > 1)
			for (size_t j{ 0 }; j < i - 1; ++j)
				while (valarray_compare(centroids[j], centroids[i]) == true)
					centroids[i] = data[rand() % data.getRows()];
	}
}


bool LargestCentroindsInitializer::valarray_compare(std::valarray <long double> lhs, std::valarray <long double> rhs) {
	size_t compare = 0;
	for (size_t i{ 0 }; i < lhs.size(); ++i)
		if (lhs[i] == rhs[i])
			compare++;
	if (compare == lhs.size())
		return true;
	else
		return false;
}


long double LargestCentroindsInitializer::max_metric(std::vector<std::valarray<long double>> temp,\
										std::valarray<long double> tmp2, Metrics* metric, size_t n) {
	long double ret = 0.00;
	for (size_t i{ 0 }; i < n - 1; ++i)
		ret += metric->distance(temp[i], tmp2);
	return ret;
}


bool LargestCentroindsInitializer::coincidence(std::vector<std::valarray<long double>> temp,\
												std::valarray<long double> pam, size_t n) {
	for (size_t i{ 0 }; i < n - 1; ++i)
		if (valarray_compare(temp[i], pam)) // if valarrays are equal 
		{
			return true;
			break;
		}
	return false;
}

bool LargestCentroindsInitializer::usedDataCheck(std::vector <size_t> vec, size_t n) {
	for (size_t i{ 0 }; i < vec.size(); ++i)
		if (vec[i] == n) {
			return true;
			break;
		}
	return false;
}


void const LargestCentroindsInitializer::initCentroids(std::vector<std::valarray<long double>>& centroids, \
	Matrix<long double> data, Metrics* metric) {

	srand(time(0));
	std::vector<size_t> used_data(centroids.size(), data.getRows() + 1);
	used_data[0] = rand() % data.getRows();

	centroids[0] = data[used_data[0]]; // The first centre is selected as a random case from the dataset. 
	std::valarray<long double> tmp1;   // temporary valarray

	for (size_t i{ 1 }; i < centroids.size(); ++i) // running through an array of centroids
	{
		long double max_dist = -1.00;		     // because metrics > 0
		for (size_t j{ 0 }; j < data.getRows(); ++j)
		{
			tmp1 = data[j];
			if ((usedDataCheck(used_data, j) == false) && (max_dist < max_metric(centroids, tmp1, metric, i)))
				if (coincidence(centroids, tmp1, i) == false)
				{
					max_dist = max_metric(centroids, tmp1, metric, i);
					centroids[i] = tmp1;
					used_data[i] = j;
				}
		}
	}
}

void const KFirstCentroindsInitializer::initCentroids(std::vector<std::valarray<long double>>& centroids, \
	Matrix<long double> data, Metrics* metric) {
	for (size_t i{ 0 }; i < centroids.size(); ++i)
		centroids[i] = data[i];
}