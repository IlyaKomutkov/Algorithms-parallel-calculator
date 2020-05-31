#pragma once


#include "RK.hpp"
#include "KMeans.hpp"


// use this interface to adjust new algorithm
class Algorithm {
public:
	virtual const void start(std::string resultPATH) = 0;
	virtual ~Algorithm() = default;
};


template<class ODE>
class RKAlgorithm : public Algorithm {
private:
	RKIntegrator<ODE> rkIntegrator_;

	// parametrs for starting algoritm
	long double t0_, h_;
	std::valarray<long double> s0_;
	size_t n_;
	bool bMain_;
public:
	RKAlgorithm(RKIntegrator<ODE> rkIntegrator,\
				long double t0, std::valarray<long double> s0,\
				long double h, size_t n, bool bMain = 1) : 
	rkIntegrator_(rkIntegrator), t0_(t0), s0_(s0), h_(h), n_(n), bMain_(bMain) {};

	void const start(std::string resultPATH)  override{
		Matrix<long double> result = rkIntegrator_.nSteps(t0_, s0_, h_, n_);
		result.toCsv(resultPATH);
	}
};


class KMeansAlgorithm : public Algorithm{
private:
	KMeans kmalg_;
public:
	KMeansAlgorithm(KMeans kmalg) : kmalg_(kmalg){};
	void const start(std::string resultPATH) override{
		kmalg_.start(resultPATH);
	}
};



