#pragma once


#include "linalg.hpp"

#include "KMetrics.hpp"
#include "InitCentroids.hpp"

class KMeans{
private:
    size_t k_;                     // clusters number
    long double eps_;  			//accuracy
    Matrix<long double> data_;

    Metrics* metrics_;
    CentroindsInitializer* centroindsInitializer_;
public:
	class KMeansBuilder;
    KMeans(size_t, long double, Matrix<long double>, Metrics*, CentroindsInitializer*);
    void const start(std::string PATH);
    
};


class KMeans::KMeansBuilder {
private:
    size_t k_ = 1;                 // clusters number
    long double eps_ = 0.1;  			//accuracy
    Matrix<long double> data_ = Matrix<long double>(2, 2);

    Metrics* metrics_ = new EuclidDist();
    CentroindsInitializer* centroindsInitializer_ = new RandomCentroindsInitializer();

public:
    KMeansBuilder() {}
    ~KMeansBuilder() {}

    KMeans build(){
    	return KMeans {k_, eps_, data_, metrics_, centroindsInitializer_};
    } 	

    KMeansBuilder&  setMetrics(Metrics* metrics) { 
    	metrics_ = metrics; 
    	return *this;
    }

    KMeansBuilder&  setCentroindsInitializer(CentroindsInitializer* centroindsInitializer) { 
    	centroindsInitializer_ = centroindsInitializer; 
    	return *this;
    }

    KMeansBuilder& setCentroindsInitializer(CentroindsInitializer* centroindsInitializer, Metrics* metrics) {
        centroindsInitializer_ = centroindsInitializer;
        return *this;
    }

    KMeansBuilder&  setK(int k){
    	k_ = k;
    	return *this;
    }

    KMeansBuilder& setAccuracy(long double eps){
    	eps_ = eps;
    	return *this;
    }

    KMeansBuilder&  setData(Matrix<long double> data){
    	data_ = data;
    	return *this;
    }
};
