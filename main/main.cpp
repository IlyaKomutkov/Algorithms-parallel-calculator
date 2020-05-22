#include "Algorithm.hpp"
//тут был я еабный хуй науй сука
int main(){
	std::valarray<long double> v= { 398600.0 };
	//v = v / 4;
	//std::cout << v;
//     /* RKINtegrator algorithm */
	auto ode = TwoBodiesODE(v);
// 	// define   RK5(4)7FC from Dormand and Prince method
 	RKMethod method(
 		"RK/Butchers/matrixC.csv",
 		{ 0, 0.2, 0.3, 0.46153846153846153846, 0.66666666666666666666666667, 1, 1 },
 		{ 0.08101851851851851, 0, 0.58407201264344, -0.3373133975812547, 0.5752840909090909, 0.0969387755102, 0 },
 		{ 0.10185185185185, 0, 0.429464715179, 0.103788737717309, 0.46022727272727272727272727, 0.087244897959183673469, 0.025 }
 	);
// 	// define our Integrator with TwoBodiesode and method
 	RKIntegrator<TwoBodiesODE> rkIntegrator(&ode, &method);
	long double h = 100;			// step
 	size_t n = 1000;	 			// number of steps
 	std::valarray<long double> s0	// s0 vector-condition
	{ 6871, 0, 0, 0, (7.616556585247121 + 10.771437621438588) / 2, 0 };


 	auto algorithm1 = RKAlgorithm<TwoBodiesODE>(rkIntegrator, 0, s0, h, n);
// 	auto algorithm1 = RKAlgorithm<TwoBodiesODE>(rkIntegrator, 0, s0, h, n);
// 	auto algorithm1 = RKAlgorithm<TwoBodiesODE>(rkIntegrator, 0, s0, h, n);
// 	auto algorithm1 = RKAlgorithm<TwoBodiesODE>(rkIntegrator, 0, s0, h, n);


    algorithm1.start("otvalzhopi.csv");

// 	/* KMeans algorithm */

// 	KMeans km(3, 0.1, {"KMeans/datasets/allUsers.csv"});
// 	km.start("test/test0.csv");

// 	auto algorithm2 = KMeansAlgorithm(km);



// 	//	//														// //
// //			//												//			//
// 				//										//				//
// //					// //	//	//	//	//	//	//	//
// 	std::vector<Algorithm*> algorithms {&algorithm1, &algorithm2};
// 	int i = 0;
// 	for (const auto algorithm : algorithms) {
// 		algorithm->start("test/test" +  std::to_string(i++) + ".csv");
// 		}			//	//	//	//	//	//	//	//	//	
// //				//										//				//
// //			//												//			//
// 	//	//														// //


	return 0;
}