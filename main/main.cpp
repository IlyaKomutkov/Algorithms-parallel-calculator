#include "Algorithm.hpp"
// #include "Controller.hpp"
// 
// #include "ThreadTesting.hpp"

int main(){

    /* RKINtegrator algorithm */

	TwoBodiesODE ode;
	// define   RK5(4)7FC from Dormand and Prince method
	RKMethod method(
		"Butchers/matrixC.csv",
		{ 0, 0.2, 0.3, 0.46153846153846153846, 0.66666666666666666666666667, 1, 1 },
		{ 0.08101851851851851, 0, 0.58407201264344, -0.3373133975812547, 0.5752840909090909, 0.0969387755102, 0 },
		{ 0.10185185185185, 0, 0.429464715179, 0.103788737717309, 0.46022727272727272727272727, 0.087244897959183673469, 0.025 }
	);
	// define our Integrator with TwoBodiesode and method
	RKIntegrator<TwoBodiesODE> rkIntegrator(&ode, &method);
	long double h = 100;			// step
	size_t n = 1000;	 			// number of steps
	std::valarray<long double> s0	// s0 vector-condition
	{ 6871, 0, 0, 0, (7.616556585247121 + 10.771437621438588) / 2, 0 };


	auto algorithm1 = RKAlgorithm<TwoBodiesODE>(rkIntegrator, 0, s0, h, n);



	/* KMeans algorithm */

	KMeans km(3, 0.1, {"datasets/allUsers.csv"});
	km.start("test0.csv");
	auto algorithm2 = KMeansAlgorithm(km);

	std::vector<Algorithm*> algorithms {&algorithm1, &algorithm2};

	// Controller<1, Algorithm*> controller;
	// // Controller<1, Algorithm*> controller{}\
	// // 			.push(&algorithm1, "test/testRK.csv")\
	// // 			.push(&algorithm2, "test/testKM.csv")\
	// // 			.start()\
	// // 			.wait_finished();

	// controller.push(&algorithm1, "test/testRK.csv");
	// controller.push(&algorithm2, "test/testKM.csv");
	// controller.start();
	// controller.wait_finished();

	return 0;
}