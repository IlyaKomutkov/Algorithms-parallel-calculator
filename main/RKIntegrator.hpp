#pragma once

#include "linalg.hpp"
#include "RKMethod.hpp"


template<class ODE>
class RKIntegrator{
private:
    // contain certain method and certain ODE system
	RKMethod* RKmethod;
	ODE* ode;
public:
	inline RKIntegrator(ODE*, RKMethod*);
	// it allows to change methods or ode-system if it is required
	void inline setODE(ODE*);
	void inline setRKMethod(RKMethod*);
	// one-step of integration takes time t, vector-condition s0, step h and
	// choose type of calculation(with Bmain or Bsubs)
	// and return new vector-condition
	std::valarray<long double> inline oneStep(long double, std::valarray<long double>, 
											long double, bool bMain = 1);

    // n-steps of integration takes time t, vector-condition s0, step h, number of steps
    // n=(t - t0)/h and
    // choose type of calculation(with Bmain or Bsubs)
    // and return matrix consisted of vectors-condition
	Matrix<long double> inline nSteps(long double, std::valarray<long double>, 
											long double, size_t, bool bMain = 1);
};

#include "RKIntegrator.inl"
