#include "Algorithm.hpp"
#include "Controller.hpp"


int main(){

	//
	//
	//

	// define RK methods for LVOde
	auto ode = LVOde(1, 1.5, 2, 1.5);

	RKMethod methodRK57FC(
		"RK/Butchers/RK5(4)7FC.csv",
		{ 0, 0.2, 0.3, 0.46153846153846153846, 0.66666666666666666666666667, 1, 1 },
		{ 0.08101851851851851, 0, 0.58407201264344, -0.3373133975812547, 0.5752840909090909, 0.0969387755102, 0 },
		{ 0.10185185185185, 0, 0.429464715179, 0.103788737717309, 0.46022727272727272727272727, 0.087244897959183673469, 0.025 }
	);

	RKIntegrator<ODE> rkIntegratorRK57FC(&ode, &methodRK57FC);


	 /* RKINtegrator algorithm */

	size_t n = 10000;	   // number of steps
	long double h = 0.005; // step's length

	auto rkLVOdeRK57FC = RKAlgorithm<ODE>(rkIntegratorRK57FC, 0, {1, 1}, h,	3 * n);

	//
	//
	//

	 /* KMeans algorithm */
	auto kmLargestEuclid = 	KMeansAlgorithm(
		KMeans::KMeansBuilder{}\
		.setCentroindsInitializer(new LargestCentroindsInitializer())\
		.setMetrics(new EuclidDist)\
		.setData({"KMeans/datasets/test.csv"})\
		.setK(8)\
		.build());


	ThreadController<2, Algorithm*> controller;

 	controller\
 		.push(&rkLVOdeRK57FC, 	"RK/Results/rkLVOdeRK57FC.csv")\
 		.push(&kmLargestEuclid, "KMeans/Results/kmLargestEuclid.csv")
 		.start();
}
