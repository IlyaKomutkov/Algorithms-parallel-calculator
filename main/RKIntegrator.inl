template<class ODE>
RKIntegrator<ODE>::RKIntegrator(ODE* odeToSolve, \
				RKMethod* RKMethodToUse){
	ode = odeToSolve;
	RKmethod = RKMethodToUse;
}


template<class ODE> void RKIntegrator<ODE>::setODE(ODE* newOde){ode = newOde;}
template<class ODE> void RKIntegrator<ODE>::setRKMethod(RKMethod* newRKmethod){RKmethod = newRKmethod;}


template<class ODE>
std::valarray<long double> RKIntegrator<ODE>::oneStep(long double t, std::valarray<long double> s0, long double h, bool bMain){
	std::valarray<long double> c = RKmethod->getC();
	std::valarray<long double> b_main = bMain ? RKmethod->getB_main() : RKmethod->getB_subs();
	Matrix<long double> A = RKmethod->getA();

	int s = b_main.size();
	int n = s0.size();
	Matrix<long double> K(s, n, 0);

	for (int i = 0; i < s; ++i){
		std::valarray<long double> addVec(n);
		for (int j = 0; j < s; ++j){
			addVec += A[i][j] * K[i];
		}

		K[i] = ode->operator()(t + h * c[i], s0 + h * addVec); 
	}
	std::valarray<long double> res(n);
	std::valarray<long double> sumKB(n);
	for (int i = 0; i < s; ++i){sumKB += b_main[i] * K[i];}
	res = s0 + h * sumKB;
	return res;
}


template<class ODE>
Matrix<long double> RKIntegrator<ODE>::nSteps(long double t0, std::valarray<long double> s0, long double h, size_t n, bool bMain){
	long double t = t0;
	Matrix<long double> resMatrix(n, s0.size(), 0);
	std::valarray<long double> s = s0;
	std::valarray<long double> res;
	for (int i = 0; i < n; ++i){
		res = this->oneStep(t, s, h, bMain);
		t += h;
		s = res;
		resMatrix[i] = res;
	}
	return resMatrix;
}