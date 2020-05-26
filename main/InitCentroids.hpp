#pragma once

#include "linalg.hpp"


class CentroindsInitializer{
public:
	virtual void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data) = 0;
};


class RandomCentroindsInitializer: public CentroindsInitializer{
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data) override{
		std::cout << "RandomCentroindsInitializer" << std::endl;
	}
};


class LargestCentroindsInitializer: public CentroindsInitializer{
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data) override{
		std::cout << "LargestCentroindsInitializer" << std::endl;
	}
};


class KFirstCentroindsInitializer: public CentroindsInitializer{
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data) override{
		std::cout << "kFirstCentroindsInitializer" << std::endl;
		for (int i = 0; i < centroids.size(); ++i)
			centroids[i] = data[i];
	}
};