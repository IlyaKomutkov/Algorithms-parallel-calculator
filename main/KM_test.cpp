#include "Algorithm.hpp"
#include "KMeans.hpp"


int main(){

	KMeans kmeans = KMeans::KMeansBuilder{}\
										.setCentroindsInitializer(new LargestCentroindsInitializer())\
										.setData({"allUsers.csv"})\
										.setK(3)\
										.build();

	kmeans.start("testAllUsers.csv");
	std::cout << "end" << std::endl;
	return 0;
}