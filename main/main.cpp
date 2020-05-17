#include "Algorithm.hpp"
#include "LVOde.hpp"

#include <memory>
#include <cstring>

void runAlgorithm(std::shared_ptr<Algorithm> alg){
	alg->start("test.csv");
}

int main(){

	LVOde lvode(1, 1.5, 2, 1.5);// define L-V system

	// define RK6(5)8S method
	RKMethod method(
		"matrixA.csv", 
		{0, 0.25, 0.3, 0.8571428571, 0.6, 0.8, 1, 1},
		{0.08950617284, 0, 0.4612671279, -0.6650443178, -0.06430041152, 1.0416666667, 0.0119047619, 0.125},
		{0.09449074074, 0, 0.4262108262, -0.0513034188, 0.1018518519, 0.36875, 0.06, 0}
	);

	// define our Integrator for lvode and certain method
	RKIntegrator<LVOde> rkIntegrator(&lvode, &method);

	long double h = 0.005;// lenght of step
	size_t n = 10 / h;	 // number of steps

	auto algorithm1 = RKAlgorithm<LVOde>(rkIntegrator, 0, {1, 1}, h, n);
	auto algorithm2 = KNNAlgorithm();

	std::vector<Algorithm*> algorithms {&algorithm1, &algorithm2};

	int i = 0;
	for (const auto algorithm : algorithms) {
		algorithm->start("test" +  std::to_string(i) + ".csv");
	}


	return 0;
}