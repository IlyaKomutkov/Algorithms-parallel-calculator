#include "Algorithm.hpp"
#include "Controller.hpp"


int main(){

	// define RK methods for LVOde
	auto ode = LVOde(1, 1.5, 2, 1.5);

	RKMethod methodRK57FC(
		"RK/Butchers/RK5(4)7FC.csv",
		{ 0, 0.2, 0.3, 0.46153846153846153846, 0.66666666666666666666666667, 1, 1 },
		{ 0.08101851851851851, 0, 0.58407201264344, -0.3373133975812547, 0.5752840909090909, 0.0969387755102, 0 },
		{ 0.10185185185185, 0, 0.429464715179, 0.103788737717309, 0.46022727272727272727272727, 0.087244897959183673469, 0.025 }
	);
	RKMethod methodRK68S(
		"RK/Butchers/RK6(5)8S.csv", 
		{0, 0.25, 0.3, 0.8571428571, 0.6, 0.8, 1, 1},
		{0.08950617284, 0, 0.4612671279, -0.6650443178, -0.06430041152, 1.0416666667, 0.0119047619, 0.125},
		{0.09449074074, 0, 0.4262108262, -0.0513034188, 0.1018518519, 0.36875, 0.06, 0}
	);
	RKMethod methodRK56(
		"RK/Butchers/RK5(4)6.csv",
		{0, 0.2, 0.3, 0.6, 1, 0.875},
		{0.1021773727,0,0.3839079034,0.2445927373,0.01932198661,0.25},
		{0.1063218391,0,0.4025764895,0.2104377104,0,0.2891022021}
	);
	RKMethod methodRK58(
		"RK/Butchers/RK5(6)8.csv",
		{ 0, 0.166666666666666666666, 0.26666666666666666, 0.6666666666666666, 0.8, 1, 0, 1 },
		{ 0.08072916666666666, 0, 0.39950284090909094, 0.28125, 0.16276041666666666, 0.07575757575757576, 0, 0 },
		{ 0.004971590909090909, 0, 0.39950284090909094, 0.28125, 0.16276041666666666, 0,0.07575757575757576, 0.07575757575757576 }
	);


	RKIntegrator<ODE> rkIntegratorRK57FC(&ode, &methodRK57FC);
	RKIntegrator<ODE> rkIntegratorRK68S(&ode, &methodRK68S);
	RKIntegrator<ODE> rkIntegratorRK56(&ode, &methodRK56);
	RKIntegrator<ODE> rkIntegratorRK58(&ode, &methodRK58);


	 /* RKINtegrator algorithm */
 

	size_t n = 10000;	 // number of steps

	auto rkLVOdeRK57FC = RKAlgorithm<ODE>(rkIntegratorRK57FC, 0, {1, 1}, 0.005,	3 * n);
	auto rkLVOdeRK68S = RKAlgorithm<ODE>(rkIntegratorRK68S,   0, {1, 1}, 0.005, 10 * n);
	auto rkLVOdeRK56 = RKAlgorithm<ODE>(rkIntegratorRK56,     0, {1, 1}, 0.005, 5 * n);
	auto rkLVOdeRK58 = RKAlgorithm<ODE>(rkIntegratorRK58,     0, {1, 1}, 0.005, n);



	std::string resultDir = "RK/Results/";

	ThreadController<4, Algorithm*> controller;
 	controller\
 		.push(&rkLVOdeRK57FC, 	resultDir + "rkLVOdeRK57FC.csv")\
 		.push(&rkLVOdeRK68S, 	resultDir + "rkLVOdeRK68S.csv")\
 		.push(&rkLVOdeRK56, 	resultDir + "rkLVOdeRK56.csv")\
 		.push(&rkLVOdeRK58, 	resultDir + "rkLVOdeRK58.csv")\
 		.start();
}
