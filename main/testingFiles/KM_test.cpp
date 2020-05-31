#include "Algorithm.hpp"
#include "KMeans.hpp"


void testManhattanDistAndRandomCentroindsInitializer() {
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new RandomCentroindsInitializer())\
		.setMetrics(new ManhattanDist)\
		.setData({ "KMeans/datasets/test2_without_norm.csv" })\
		.setK(5)\
		.build();
	kmeans.start("/test/testing2_without_norm.csv");
	std::cout << "end test 1" << std::endl;
}

void testChebyshevDistAndLargestCentroindsInitializer() {
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new LargestCentroindsInitializer())\
		.setMetrics(new ChebyshevDist)\
		.setData({ "KMeans/datasets/test1_norm.csv" })\
		.setK(4)\
		.build();
	kmeans.start("/test/testing1_norm.csv");
		
	std::cout << "end test 2" << std::endl;
}

void testMinkowskiDistAndKFirstCentroindsInitializer() {
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new KFirstCentroindsInitializer())\
		.setMetrics(new MinkowskiDist(5))\
		.setData({ "KMeans/datasets\test2_norm.csv" })\
		.setK(5)\
		.build();
	kmeans.start("/test/testing2_norm.csv");
	std::cout << "end test 3" << std::endl;
}

void testEuclidDistAndKFirstCentroindsInitializer() {
	KMeans kmeans = KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new KFirstCentroindsInitializer())\
		.setData({ "KMeans/datasets/test1_without_norm.csv" })\
		.setK(6)\
		.build();
	kmeans.start("/test/testing1_without_norm.csv");
	std::cout << "end test 4" << std::endl;
}

int main() {
	Matrix<long double> m({ "test1.csv" });
	std::cout << "end test " << std::endl;
}