#pragma once


#include "linalg.hpp"

long double  distance(std::valarray<long double>, 
                           std::valarray<long double>);



class KMeans{
private:
    int k_;                     // clusters number
    long double eps_;           // accuracy
    Matrix<long double> data_;
public:
    KMeans(int, long double, Matrix<long double>);

    void const start(std::string PATH);

};