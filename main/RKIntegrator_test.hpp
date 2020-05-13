#pragma once

#include "LVOde.hpp"
#include "ODE.hpp"
#include "RK.hpp"

/* 
	calculate with 2 methods L-K Ode with 
	constatns 1, 1.5, 2, 1.5 between 0 and 10 seconds and start condition 1, 1
	after that save two .csv matrix matching b_main and b_subs calculation
*/
void testMethodA();
void testMethodB();
void mytestMethodA();


/* 
	calculate with 2 methods three body Ode with 
	constatns 10, 10, 10 between 0 and 30 seconds and start condition 
	after that save two .csv matrix matching b_main and b_subs calculation
*/
void testMethodAForODE();
void testMethodBForODE();


/* 
	calculate with 2 error matrixes for each method 
*/
void calculateErrorA();
void calculateErrorB();