template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols){
	n_cols = cols;
	n_rows = rows;
	data = std::vector<std::valarray<T>>(rows);
	for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(cols);}
	for (int i = 0; i < n_rows; ++i){
		for (int j = 0; j < n_cols; ++j){
			data[i][j] = 0;
		}
	}
}


template<typename T>
template<typename value>
Matrix<T>::Matrix(size_t rows, size_t cols, value v){
	n_cols = cols;
	n_rows = rows;
	data = std::vector<std::valarray<T>>(rows);
	for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(cols);}
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			data[i][j] = v;
		}
	}
}


template<typename T>
Matrix<T>::Matrix(){Matrix(1, 1, 0);}


template<typename T>
Matrix<T>::Matrix(std::string path){
	CSVReader reader(path);
	std::vector<std::vector<std::string>> tmp = reader.getFullData();
	n_rows = tmp.size();
	n_cols = tmp[0].size();
	data = std::vector<std::valarray<T>>(n_rows);
	for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(n_cols);}
	for (int i = 0; i < n_rows; ++i){
		for (int j = 0; j < n_cols; ++j){
			data[i][j] = boost::lexical_cast<T>(tmp[i][j]);
		}
	}
}


template<typename T>
Matrix<T>::~Matrix(){data.clear();}


template<typename T>
Matrix<T>::Matrix(const Matrix& matrix){
	n_rows = matrix.getRows();
	n_cols = matrix.getCols();
	data = std::vector<std::valarray<T>>(n_rows);
	for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(n_cols);}
	for (int i = 0; i < n_rows; ++i){
		for (int j = 0; j < n_cols; ++j){
			data[i][j] = matrix[i][j];
		}
	}
}


template <typename T>  
std::valarray<T> const operator*(const std::valarray<T>& lhs, const Matrix<T>& rhs){
	assert(lhs.size() == rhs.getRows());
	T tmp = 0;
	std::valarray<T> newVec(rhs.getCols());
	for(int i = 0; i < rhs.getRows(); ++i){
		tmp = 0;
		for(int j = 0; j < rhs.getCols(); ++j){
			tmp += rhs[i][j] * lhs[j];
		}
		newVec[i] = tmp;
	}
	return newVec;
}


template<typename T, typename value>
Matrix<T> const operator*(const Matrix<T>& lhs, const value& rhs){
	Matrix<T> newMatrix(lhs.getRows(), lhs.getCols());
	for (int i = 0; i < lhs.getRows(); ++i){
		for (int j = 0; j < lhs.getCols(); ++j){
			newMatrix[i][j] = lhs[i][j] * rhs;
		}
	}
	return newMatrix;
}


template<typename T, typename value>
Matrix<T> const operator*(const value& lhs, const Matrix<T>& rhs){
	Matrix<T> newMatrix(rhs.getRows(), rhs.getCols());
	newMatrix = rhs * lhs;
	return newMatrix;
}


template<typename T>
Matrix<T> const operator+(const Matrix<T>& lhs, const Matrix<T>& rhs){
	assert(((lhs.getCols() == rhs.getCols()) && (lhs.getRows() == rhs.getRows())));
	Matrix<T> newMatrix(lhs.getRows(), lhs.getCols());
	for (int i = 0; i < lhs.getRows(); ++i){
		for (int j = 0; j < lhs.getCols(); ++j){
			newMatrix[i][j] = lhs[i][j] + rhs[i][j];
		}
	}
	return newMatrix;	
}


template<typename T>
Matrix<T> const operator-(const Matrix<T>& lhs, const Matrix<T>& rhs){
	assert(((lhs.getCols() == rhs.getCols()) && (lhs.getRows() == rhs.getRows())));
	Matrix<T> newMatrix(lhs.getRows(), lhs.getCols());
	for (int i = 0; i < lhs.getRows(); ++i){
		for (int j = 0; j < lhs.getCols(); ++j){
			newMatrix[i][j] = lhs[i][j] - rhs[i][j];
		}
	}
	return newMatrix;
}


template<typename T>
Matrix<T> const operator*(const Matrix<T>& lhs, const Matrix<T>& rhs){
	assert(rhs.getRows() == lhs.getCols());
	Matrix<T> newMatrix(lhs.getRows(), rhs.getCols());
	int N = lhs.getRows();
	int M2 = rhs.getCols();
	int M = lhs.getCols();
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M2; j++) { 
			newMatrix[i][j] = 0; 
			for(int k = 0; k < M; k++) 
				newMatrix[i][j] = newMatrix[i][j] + lhs[i][k] * rhs[k][j];
		}
	}
	return newMatrix;
}


template<typename T>
Matrix<T> const operator/(const Matrix<T>& lhs, const Matrix<T>& rhs){
	assert(((lhs.getCols() == rhs.getCols()) && (lhs.getRows() == rhs.getRows())));
	Matrix<T> newMatrix(lhs.getRows(), lhs.getCols());
	for (int i = 0; i < lhs.getRows(); ++i){
		for (int j = 0; j < lhs.getCols(); ++j){
			newMatrix[i][j] = lhs[i][j] / rhs[i][j];
		}
	}
	return newMatrix;
}


//	matrix to standard output
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>& m){
	if (stream){
 		for (int i = 0; i < m.getRows(); ++i){
			for (int j = 0; j < m.getCols(); ++j){
				std::cout << m[i][j] << "\t";
			}
			std::cout << std::endl;
		}
  }
  return stream; 
}

