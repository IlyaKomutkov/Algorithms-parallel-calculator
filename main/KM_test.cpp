#include "Algorithm.hpp"
#include "KMeans.hpp"


void testManhattanDistAndRandomCentroindsInitializer()
{
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new RandomCentroindsInitializer())\
		.setMetrics(new ManhattanDist)\
		.setData({ "allUsers(1).csv" })\
		.setK(5)\
		.build();
	kmeans.start("testAllUsers.csv");
	std::cout << "end test 1" << std::endl;
}

void testChebyshevDistAndLargestCentroindsInitializer()
{
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new LargestCentroindsInitializer())\
		.setMetrics(new ChebyshevDist)\
		.setData({ "dataset2.csv" })\
		.setK(5)\
		.build();
	kmeans.start("testAllUsers.csv");
	std::cout << "end test 2" << std::endl;
}

void testMinkowskiDistAndKFirstCentroindsInitializer()
{
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new KFirstCentroindsInitializer())\
		.setMetrics(new MinkowskiDist(5))\
		.setData({ "dataset3.csv" })\
		.setK(3)\
		.build();
	kmeans.start("testAllUsers.csv");
	std::cout << "end test 3" << std::endl;
}

void testEuclidDistAndKFirstCentroindsInitializer()
{
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new KFirstCentroindsInitializer())\
		.setData({ "dataset4.csv" })\
		.setK(3)\
		.build();
	kmeans.start("testAllUsers.csv");
	std::cout << "end test 4" << std::endl;
}


int main()
{
	testManhattanDistAndRandomCentroindsInitializer();
}