#include "KMeans.hpp"

#include <cmath>


long double distance(std::valarray<long double> v1, 
                           std::valarray<long double> v2){
	long double s = 0;
	for (int i = 0; i < v1.size(); ++i){
		s += (v1[i] - v2[i]) * (v1[i] - v2[i]);
	}

	return sqrtf(s);
}


KMeans::KMeans(int k, long double eps, Matrix<long double> data) :\
				k_(k), data_(data), eps_(eps){};


// https://algowiki-project.org/ru/Алгоритм_k_средних_(k-means)
void const KMeans::start(std::string PATH){
	int size = data_.getRows(); 			// data size
	std::vector<long double> result(size);	// result vector

	// centroids vector and cluster's size (number of vecs in cluster)
	std::vector<std::valarray<long double>> centroids(k_);

	// 1 //
	// random initialization (k-firsts)
	for (int i = 0; i < k_; ++i)
		centroids[i] = data_[i];


	bool condition = true;
	while (condition){

		std::vector<int> clusterSize(k_);
		// 2 // 
		// choose a cluster for each vector in data
		for (int i = 0; i < size; ++i){
			std::vector<long double> distances;

			// calculate the nearest centroid 
			for (auto centroid = centroids.begin(); centroid != centroids.end(); ++centroid)
				distances.push_back(distance(*centroid, data_[i]));
			result[i] = arg_min(distances);
			clusterSize[result[i]] += 1;
		}


		// 3 //
		// recalculate centroids
		std::vector<std::valarray<long double>> new_centroids(k_);

		for (int i = 0; i < k_; ++i)
			new_centroids[i] = std::valarray<long double>(data_.getCols());

		for (int i = 0; i < size; ++i)
			new_centroids[result[i]] += data_[i];


		for (int i = 0; i < k_; ++i){

			if (clusterSize[i] == 0)
				new_centroids[i] = centroids[i];
			else
				new_centroids[i] = new_centroids[i] / clusterSize[i];
		}

		condition = false;
		for (int i = 0; i < k_; ++i){
			long double diff = distance(centroids[i], new_centroids[i]);
			if (fabs(diff) > eps_)
				condition = true;
		}

		centroids = new_centroids;
	}
	
	vecToCsv(result, PATH);

}