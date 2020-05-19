#include "RKIntegrator_test.hpp"


void testMethodA(){
	
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

	Matrix<long double> res = rkIntegrator.nSteps(0, {1, 1}, h, n);
	res.toCsv("LVOde_solution_methodA_Bmain.csv");

	res = rkIntegrator.nSteps(0, {1, 1}, h, n, 0);
	res.toCsv("LVOde_solution_methodA_Bsubs.csv");
}

void testMethodB(){

	LVOde lvode(1, 1.5, 2, 1.5);// define L-V system

	// define  RK5(4)6 method
	RKMethod method(
		"matrixB.csv",
		{0, 0.2, 0.3, 0.6, 1, 0.875},
		{0.1021773727,0,0.3839079034,0.2445927373,0.01932198661,0.25},
		{0.1063218391,0,0.4025764895,0.2104377104,0,0.2891022021}
	);

	// define our Integrator for lvode and certain method
	RKIntegrator<LVOde> rkIntegrator(&lvode, &method);
	long double h = 0.005;// lenght of step
	size_t n = 10 / h;	 // number of steps

	Matrix<long double> res = rkIntegrator.nSteps(0, {1, 1}, h, n);
	res.toCsv("LVOde_solution_methodB_Bmain.csv");

	res = rkIntegrator.nSteps(0, {1, 1}, h, n, 0);
	res.toCsv("LVOde_solution_methodB_Bsubs.csv");
}

void mytestMethodA(){
	
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

	long double h = 0.001;// lenght of step
	size_t n = 50 / h;	 // number of steps

	Matrix<long double> res = rkIntegrator.nSteps(0, {1, 1}, h, n);
	res.toCsv("LVOde_mysolution_methodA_Bmain.csv");
}

void testMethodAForODE(){
		ODE ode({10, 10, 10}); // define g*m1, g*m2 and g*m3

		// build equal triangular
		std::valarray<long double> x {10, -5, -5};
		std::valarray<long double> y {0 ,  8.66025404, -8.66025404};

		// define RK6(5)8S method
		RKMethod method(
			"matrixA.csv", 
			{0, 0.25, 0.3, 0.8571428571, 0.6, 0.8, 1, 1},
			{0.08950617284, 0, 0.4612671279, -0.6650443178, -0.06430041152, 1.0416666667, 0.0119047619, 0.125},
			{0.09449074074, 0, 0.4262108262, -0.0513034188, 0.1018518519, 0.36875, 0.06, 0}
		);

		// define our Integrator with ode and method
		RKIntegrator<ODE> rkIntegrator(&ode, &method);
		long double h = 0.01;//step
		size_t n = 30 / h;   // number of steps

		// start condition
		std::valarray<long double> s0 {x[0], y[0], 0, 0,   0, 0,
               						x[1], y[1], 0, 0.5, 0, 0,   
               						x[2], y[2], 0, 0,   0, 0 };

		Matrix<long double> res = rkIntegrator.nSteps(0, s0, h, n);
		res.toCsv("ODE_solution_methodA_Bmain.csv");

		res = rkIntegrator.nSteps(0, s0, h, n, 0);
		res.toCsv("ODE_solution_methodA_Bsubs.csv");
}

void testMethodBForODE(){
		ODE ode({10, 10, 10});// define g*m1, g*m2 and g*m3

		// build equal triangular
		std::valarray<long double> x {10, -5, -5};
		std::valarray<long double> y {0 ,  8.66025404, -8.66025404};

		// define  RK5(4)6 method
		RKMethod method(
				"matrixB.csv",
				{0, 0.2, 0.3, 0.6, 1, 0.875},
				{0.1021773727,0,0.3839079034,0.2445927373,0.01932198661,0.25},
				{0.1063218391,0,0.4025764895,0.2104377104,0,0.2891022021}
			);

		// define our Integrator with ode and method
		RKIntegrator<ODE> rkIntegrator(&ode, &method);
		long double h = 0.01;// step
		size_t n = 30 / h;	 // number of steps
		std::valarray<long double> s0 {x[0], y[0], 0, 0,   0, 0,
               						x[1], y[1], 0, 0.5, 0, 0,   
               						x[2], y[2], 0, 0,   0, 0 };
               						
		Matrix<long double> res = rkIntegrator.nSteps(0, s0, h, n);
		res.toCsv("ODE_solution_methodB_Bmain.csv");

		res = rkIntegrator.nSteps(0, s0, h, n, 0);
		res.toCsv("ODE_solution_methodB_Bsubs.csv");
}

// calculate error matrix for method A
void calculateErrorA(){
	Matrix<long double> main("ODE_solution_methodA_Bmain.csv");
	Matrix<long double> subs("ODE_solution_methodA_Bsubs.csv");
	Matrix<long double> error = main - subs;
	error.toCsv("methodA_error.csv");
}

// calculate error matrix for method B
void calculateErrorB(){
	Matrix<long double> main("ODE_solution_methodB_Bmain.csv");
	Matrix<long double> subs("ODE_solution_methodB_Bsubs.csv");
	Matrix<long double> error = main - subs;
	error.toCsv("methodB_error.csv");
}

void testMethodCForTwoBodiesODE() {
	TwoBodiesODE ode;

	// define   RK5(4)7FC from Dormand and Prince method
	RKMethod method(
		"matrixC.csv",
		{ 0, 0.2, 0.3, 0.46153846153846153846, 0.66666666666666666666666667, 1, 1 },
		{ 0.08101851851851851, 0, 0.58407201264344, -0.3373133975812547, 0.5752840909090909, 0.0969387755102, 0 },
		{ 0.10185185185185, 0, 0.429464715179, 0.103788737717309, 0.46022727272727272727272727, 0.087244897959183673469, 0.025 }
	);

	// define our Integrator with TwoBodiesode and method
	RKIntegrator<TwoBodiesODE> rkIntegrator(&ode, &method);
	long double h = 100;// step
	size_t n = 1000;	 // number of steps
	std::valarray<long double> s0{ 6871, 0, 0, 0,
								(7.616556585247121 + 10.771437621438588) / 2, 0 };

	Matrix<long double> res = rkIntegrator.nSteps(0, s0, h, n);
	res.toCsv("TwoBodiesODE_solution_methodC_Bmain.csv");

	res = rkIntegrator.nSteps(0, s0, h, n, 0);
	res.toCsv("TwoBodiesODE_solution_methodC_Bsubs.csv");
}

void testMethodDForTwoBodiesODE() {
	TwoBodiesODE ode;

	// define   Fehlberg's RK5(6)8 method
	RKMethod method(
		"matrixD.csv",
		{ 0,0.166666666666666666666,0.26666666666666666,0.6666666666666666,0.8,1,0,1 },
		{ 0.08072916666666666,0,0.39950284090909094,0.28125,0.16276041666666666,0.07575757575757576,0,0 },
		{ 0.004971590909090909,0,0.39950284090909094,0.28125,0.16276041666666666,0,0.07575757575757576,0.07575757575757576 }
	);

	// define our Integrator with TwoBodiesode and method
	RKIntegrator<TwoBodiesODE> rkIntegrator(&ode, &method);
	long double h = 100;// step
	size_t n = 1000;	 // number of steps
	std::valarray<long double> s0{ 6871, 0, 0, 0,
								(7.616556585247121 + 10.771437621438588) / 2, 0 };

	Matrix<long double> res = rkIntegrator.nSteps(0, s0, h, n);
	res.toCsv("TwoBodiesODE_solution_methodD_Bmain.csv");

	res = rkIntegrator.nSteps(0, s0, h, n, 0);
	res.toCsv("TwoBodiesODE_solution_methodD_Bsubs.csv");
}