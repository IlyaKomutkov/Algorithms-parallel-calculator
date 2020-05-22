#include "ODE.hpp"
#include "RK.hpp"


ThreeBodiesODE::ThreeBodiesODE(std::valarray<long double> GM) {gm = GM;}


std::valarray<long double> ThreeBodiesODE::operator()(long double t, std::valarray<long double> s0){

	std::valarray<long double> ds(s0.size());

	std::valarray<long double> p1 = s0[std::slice(0, 3, 1)];
	std::valarray<long double> v1 = s0[std::slice(3, 3, 3)];
	std::valarray<long double> p2 = s0[std::slice(6, 3, 1)];
	std::valarray<long double> v2 = s0[std::slice(9, 3, 1)];
	std::valarray<long double> p3 = s0[std::slice(12, 3, 1)];
	std::valarray<long double> v3 = s0[std::slice(15, 3, 1)];
	std::valarray<long double> p;

	p = p2 - p1;
	long double r12 = powl(normVec(p), 3);
	p = p3 - p1;
    long double r13 = powl(normVec(p), 3);
    p = p3 - p2;
    long double r23 = powl(normVec(p), 3);

    std::valarray<long double>  dp1 = v1;
    std::valarray<long double>  dp2 = v2;
    std::valarray<long double>  dp3 = v3;

    for (int i = 0; i < 3; ++i){ds[i] = dp1[i];}
    for (int i = 6; i < 9; ++i){ds[i] = dp2[i - 6];}
    for (int i = 12; i < 15; ++i){ds[i] = dp3[i - 12];}
	
    std::valarray<long double>  dv1 = gm[1] * (p2 - p1) / r12 + gm[2] * (p3 - p1) / r13;
  	std::valarray<long double>  dv2 = gm[0] * (p1 - p2) / r12 + gm[2] * (p3 - p2) / r23;
    std::valarray<long double>  dv3 = gm[0] * (p1 - p3) / r13 + gm[1] * (p2 - p3) / r23;

    for (int i = 3; i < 6; ++i){ds[i] = dv1[i - 3];}
    for (int i = 9; i < 12; ++i){ds[i] = dv2[i - 9];}
    for (int i = 15; i < 18; ++i){ds[i] = dv3[i - 15];}

   	return ds;
}

TwoBodiesODE::TwoBodiesODE(std::valarray<long double> GM) { gm = GM; }

std::valarray<long double> TwoBodiesODE::operator()(long double t, std::valarray<long double> s0) {

    std::valarray<long double> ds(s0.size());
    ds[0] = s0[3];//dx
    ds[1] = s0[4];//dy
    ds[2] = s0[5];//dz
    ds[3] = -gm[0] * s0[0] / pow(pow(s0[0], 2) + pow(s0[1], 2) + pow(s0[2], 2), 1.5);//dv_x
    ds[4] = -gm[0] * s0[1] / pow(pow(s0[0], 2) + pow(s0[1], 2) + pow(s0[2], 2), 1.5);//dv_y
    ds[5] = -gm[0] * s0[2] / pow(pow(s0[0], 2) + pow(s0[1], 2) + pow(s0[2], 2), 1.5);//dv_z
    return ds;
}