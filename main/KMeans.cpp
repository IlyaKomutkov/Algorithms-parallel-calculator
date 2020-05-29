#include "KMeans.hpp"
#include <algorithm>
#include <cmath>




KMeans::KMeans(size_t k, long double eps, Matrix<long double> data, Metrics* metrics,\
				CentroindsInitializer* centroindsInitializer)\
				:k_(k), eps_(eps), data_(data), metrics_(metrics), centroindsInitializer_(centroindsInitializer){}

// https://algowiki-project.org/ru/Алгоритм_k_средних_(k-means)
void const KMeans::start(std::string PATH){
	size_t size = data_.getRows(); 			// data size
	std::vector<long double> result(size);	// result vector


	// centroids vector and cluster's size (number of vecs in cluster)
	std::vector<std::valarray<long double>> centroids(k_);

	// 1 //
	centroindsInitializer_->initCentroids(centroids, data_, metrics_);

	bool condition = true;
	while (condition){

		std::vector<int> clusterSize(k_);
		// 2 // 
		// choose a cluster for each vector in data
		for (size_t i{ 0 }; i < size; ++i) {
			std::vector<long double> distances;

			// calculate the nearest centroid 
			for (auto centroid = centroids.begin(); centroid != centroids.end(); ++centroid)
				distances.push_back(metrics_->distance(*centroid, data_[i]));
			result[i] = arg_min(distances);
			clusterSize[result[i]] += 1;
		}

		// 3 //
		// recalculate centroids
		std::vector<std::valarray<long double>> new_centroids(k_);

		for (size_t i{ 0 }; i < k_; ++i)
			new_centroids[i] = std::valarray<long double>(data_.getCols());

		for (size_t i{ 0 }; i < size; ++i)
			new_centroids[result[i]] += data_[i];


		for (size_t i{ 0 }; i < k_; ++i) {

			if (clusterSize[i] == 0)
				new_centroids[i] = centroids[i];
			else
				new_centroids[i] = new_centroids[i] / clusterSize[i];
		}

		// 4 //
		condition = false;
		for (size_t i{ 0 }; i < k_; ++i) {
			long double diff = metrics_->distance(centroids[i], new_centroids[i]);
			if (fabs(diff) > eps_)
				condition = true;
		}

		centroids = new_centroids;
	}
	
	vecToCsv(result, PATH);
}
