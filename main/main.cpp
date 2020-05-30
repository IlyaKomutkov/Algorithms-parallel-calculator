#include "Algorithm.hpp"
#include "Controller.hpp"
#include "testingFiles/ThreadTesting.hpp"


int main(){

	ThreadController<8, Algorithm*> controller;
  	controller\
  		.push(
		  	{ 
				new KMeansAlgorithm( KMeans::KMeansBuilder{}\
									.setCentroindsInitializer(new RandomCentroindsInitializer())\
									.setMetrics(new EuclidDist)\
									.setData({"KMeans/datasets/test.csv"})\
									.setK(8)\
									.build()),
				new KMeansAlgorithm( KMeans::KMeansBuilder{}\
									.setCentroindsInitializer(new RandomCentroindsInitializer())\
									.setMetrics(new ManhattanDist)\
									.setData({"KMeans/datasets/test.csv"})\
									.setK(8)\
									.build()), 
				new KMeansAlgorithm( KMeans::KMeansBuilder{}\
									.setCentroindsInitializer(new RandomCentroindsInitializer())\
									.setMetrics(new ChebyshevDist)\
									.setData({"KMeans/datasets/test.csv"})\
									.setK(8)\
									.build()), 
				new KMeansAlgorithm( KMeans::KMeansBuilder{}\
									.setCentroindsInitializer(new RandomCentroindsInitializer())\
									.setMetrics(new MinkowskiDist(4))\
									.setData({"KMeans/datasets/test.csv"})\
									.setK(8)\
									.build())
			}, 
  			{ 
  				"kmRandomEuclid.csv", 	"kmRandomManhattan.csv", "kmRandomChebyshev.csv", "kmRandomMinkowski.csv" 
  			}
  		).start();

	return 0;
}
