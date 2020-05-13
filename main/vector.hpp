/*
	modifications for STL vector and
	my "vector" - STL valarray
*/

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <valarray>
#include <cassert>
#include <cmath>

// calculate scalar product of 2 "vectors"
template <typename T>
long double Dot(std::valarray<T> lhs, std::valarray<T> rhs){
	double scalar = 0;
	 assert(lhs.size() == rhs.size());
		for(int i = 0; i < rhs.size(); ++i){
			scalar += lhs[i] * rhs[i];
		}
	return scalar;
}


// calculate Euclid-norm of "vector"
template <typename T>
long double normVec(std::valarray<T> v){
	long double sum = 0;
	for (int i = 0; i < v.size(); ++i){sum += v[i] * v[i];}
	return sqrtl(sum);
}


// for valarray
template <typename T>
void vecToCsv(std::valarray<T> vec, std::string path){
	std::ofstream file(path);
	for (int i = 0; i < vec.size(); ++i){
		file << vec[i];
		if (i != vec.size() - 1){file << ",";}
	}
	file.close();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::valarray<T>& vec){
	if (stream){
		stream << "(";
 		for (int i = 0; i < vec.size(); ++i){
			stream << vec[i];
			if (i != vec.size() - 1){stream << ", ";}
		}
		stream << ")" << std::endl;
  	}
  	return stream; 
}



// for STL vector
template <typename T>
void vecToCsv(std::vector<T> vec, std::string path){
	std::ofstream file(path);
	for (int i = 0; i < vec.size(); ++i){
		file << vec[i];
		if (i != vec.size() - 1){file << ",";}
	}
	file.close();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec){
	if (stream){
		stream << "(";
 		for (int i = 0; i < vec.size(); ++i){
			stream << vec[i];
			if (i != vec.size() - 1){stream << ", ";}
		}
		stream << ")" << std::endl;
  	}
  	return stream; 
}

