#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <valarray>
#include <vector>
#include <cstdlib>

#include "vector.hpp"
#include "read_csv.hpp"


//	template class of matrix
//	my matrix is vector of valarrays

/*	
	as VECTOR here and therefore it is used STL VALARRAY 
	with modifications in "vector.hpp" 
*/

template<typename T>
class Matrix{
private:
	size_t n_cols;
	size_t n_rows;
	std::vector<std::valarray<T>> data;

public:
	template<typename value> 
	inline Matrix(size_t, size_t, value);	// create matrix rows x cols and fill with some value
	inline Matrix(size_t, size_t);			// create matrix rows x cols and fill with 0
	inline Matrix();						// create matrix 1 x 1 and fill with 0
	inline Matrix(const Matrix&);
	inline Matrix(std::string);				// read matrix from .csv(only)

	inline ~Matrix();						// destructor only clear matrix as STL containers clear themselves

	// simple "getters"
	const size_t getCols() const {return n_cols;}
	const size_t getRows() const {return n_rows;}
	const void printSize() const {std::cout << "(" << n_rows << ", " << n_cols << ")" << std::endl;}
	
	// basic operators for calculations with matrix and vectors(aka valarray)
	template <typename T1> friend Matrix<T1> const operator*(const Matrix<T1>& lhs, const std::valarray<T1>& rhs);
	template <typename T1> friend std::valarray<T1> const operator*(const std::valarray<T1>& lhs, const Matrix<T1>& rhs);
	template <typename T1> friend Matrix<T1> const operator-(const Matrix<T1>& lhs, const Matrix<T1>& rhs);
	template <typename T1> friend Matrix<T1> const operator+(const Matrix<T1>& lhs, const Matrix<T1>& rhs);
	template <typename T1> friend Matrix<T1> const operator*(const Matrix<T1>& lhs, const Matrix<T1>& rhs);
	template <typename T1> friend Matrix<T1> const operator/(const Matrix<T1>& lhs, const Matrix<T1>& rhs);
	template <typename T1, typename value> friend const Matrix<T1> operator*(const Matrix<T1>& lhs, const value& rhs);
	template <typename T1, typename value> friend const Matrix<T1> operator*(const value& lhs, const Matrix<T1>& rhs);
	std::valarray<T>& operator[](int index){return data[index];}
	const std::valarray<T>& operator[](int index) const{return data[index];}
	Matrix<T>& operator=(const Matrix<T>& rhs){
		n_cols = rhs.getCols();
		n_rows = rhs.getRows();
		data = std::vector<std::valarray<T>>(n_rows);
		for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(n_cols);}
		for (int i = 0; i < n_rows; ++i){
			for (int j = 0; j < n_cols; ++j){
				data[i][j] = rhs[i][j];
			}
		}
		return *this;
	}

	// matrix' methods for calculations
	static inline std::valarray<T> linspace(T, T, size_t);
	void inline transpose();
	Matrix<T> inline apply(T (*func)());
	void toCsv(std::string);

	
};


#include "matrix_methods.inl"// methods' implementation
#include "matrix.inl"		 // constructors', operators' implementation 