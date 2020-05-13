#include "linalg.hpp"
#include "LVOde.hpp"
#include "ODE.hpp"
#include "RK.hpp"

#include "testing.hpp"
#include "RKIntegrator_test.hpp"

#define TEST_MODE   0	// define True to test library "linalg.hpp"  
#define SOLVE_LVODE 0	// define True to find LVOde solutions with RK-methods  
#define SOLVE_ODE   0	// define True to find Three-body ODE solutios with RK-methods


int main(){

	#if TEST_MODE 

		TestingSystem testingSystem;
		testingSystem.testVector();
		testingSystem.testMatrix();

	#elif SOLVE_LVODE

		testMethodA();
		testMethodB();
		mytestMethodA();

	#elif SOLVE_ODE 

		testMethodAForODE();
		testMethodBForODE();
		calculateErrorA();
		calculateErrorB();

	#endif

		LVOde lvode(1, 1.5, 2, 3);
		// define RK6(5)8S method
		RKMethod method(
			"matrixA.csv", 
			{0, 0.25, 0.3, 0.8571428571, 0.6, 0.8, 1, 1},
			{0.08950617284, 0, 0.4612671279, -0.6650443178, -0.06430041152, 1.0416666667, 0.0119047619, 0.125},
			{0.09449074074, 0, 0.4262108262, -0.0513034188, 0.1018518519, 0.36875, 0.06, 0}
		);

		RKIntegrator<LVOde> integrator(&lvode, &method);
		long double h = 0.001;
		size_t n = 10000 / h;

		Matrix<long double> res = integrator.nSteps(0, {1, 1}, h, n);
		res.toCsv("resMatrix.csv");

		std::cout << "The end of the program!" << std::endl;
		return 0;
}