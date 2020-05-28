#pragma once

#include "linalg.hpp"


class CentroindsInitializer{
public:
	virtual void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data, Metrics* metric) = 0;
};

//randomly selected points
//
class RandomCentroindsInitializer: public CentroindsInitializer
{
private:
	bool valarray_compare(std::valarray <long double> lhs, std::valarray <long double> rhs)
	{
		size_t compare = 0;
		for (size_t i{ 0 }; i < lhs.size(); ++i)
			if (lhs[i] == rhs[i])
				compare++;
		if (compare == lhs.size())
			return true;
		else
			return false;
	}
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data, Metrics* metric) override
	{
		std::cout << "RandomCentroindsInitializer" << std::endl;
		srand(time(0));
		for (size_t i{ 0 }; i < centroids.size(); ++i)
		{
			centroids[i] = data[rand() % centroids.size()];
			if (i != 0)
				for (size_t j{ 0 }; j < i - 1; ++j)
					if (valarray_compare(centroids[i], centroids[j])==true)
						centroids[i] = data[rand() % centroids.size()];
		}
	}
};



//farthest points(simple selection)
//The first centre is selected as a random case from the dataset. 
//The 2nd centre is selected as the case maximally distant from that centre. 
//The 3rd centre is selected as the case maximally distant from those two (from the nearest of the two), 
//- and so on.
class LargestCentroindsInitializer : public CentroindsInitializer
{
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data, Metrics* metric) override {
		std::cout << "LargestCentroindsInitializer" << std::endl;
		srand(time(0));
		centroids[0] = data[rand() % centroids.size()];
		std::valarray<long double> temp1;
		std::valarray<long double> temp2;
		for (size_t i{ 1 }; i < centroids.size(); ++i)
		{
			std::vector<long double> max_dist(centroids.size(), 0);
			for (size_t j{ 0 }; j < data.getRows(); ++j)
			{
				temp1 = data[j];
				for (size_t k{ 0 }; k < i; ++k)
				{
					if (metric->distance(centroids[i - 1], temp1) > max_dist[k])
					{
						max_dist[k] = metric->distance(centroids[i - 1], temp1);
						temp2 = data[j];
					}
				}
			}
			centroids[i] = temp2;
			max_dist.clear();
			max_dist.resize(centroids.size());
		}

	}
};


//random farthest points, or k-means++
//1.Randomly select the first centroid from the data points.
//2.For each data point compute its distance from the nearest, previously choosen centroid.
//3.Select the next centroid from the data points such that the probability of choosing a point as centroid is directly proportional to its distance from the nearest, previously chosen centroid. (i.e.the point having maximum distance from the nearest centroid is most likely to be selected next as a centroid)
//4.Repeat steps 2 and 3 untill k centroids have been sampled
/*class KMPPCentroindsInitializer: public CentroindsInitializer
{
private:
	long double nearest();
	//blank for implementation k-means++ method initial cluster centres
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data) override{
		std::cout << "KMPPCentroindsInitializer" << std::endl;
		

	}
};*/


class KFirstCentroindsInitializer: public CentroindsInitializer{
public:
	void const initCentroids(std::vector<std::valarray<long double>>& centroids, Matrix<long double> data, Metrics* metric) override{
		std::cout << "kFirstCentroindsInitializer" << std::endl;
		for (int i = 0; i < centroids.size(); ++i)
			centroids[i] = data[i];
	}
};