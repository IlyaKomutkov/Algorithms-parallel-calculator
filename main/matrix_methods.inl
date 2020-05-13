template<typename T>
void Matrix<T>::transpose(){
		Matrix<T> newMatrix(*this);
		size_t tmp = 0;
		tmp = n_cols;
		n_cols = n_rows;
		n_rows = tmp;
		data = std::vector<std::valarray<T>>(n_rows);
		for (int i = 0; i < n_rows; ++i) {data[i] = std::valarray<T>(n_cols);}
		for (int i = 0; i < n_rows; ++i){
			for (int j = 0; j < n_cols; ++j){
				data[i][j] = newMatrix[j][i];
			}
		}
}


template<typename T>
std::valarray<T> Matrix<T>::linspace(T a, T b, size_t n){
	T h = (b - a) / static_cast<T>(n-1);
	std::valarray<T> vec(n);
	T val = a;
	for(int i = 0; i < n; ++i, val += h){
		vec[i] = val;
	}
	return vec;
}


template<typename T>
void Matrix<T>::toCsv(std::string path){
	std::ofstream file(path);
	for (int i = 0; i < n_rows; ++i){
		for (int j = 0; j < n_cols; ++j){
			file << data[i][j];
			if (j != n_cols - 1){file << ",";}
		}
	file << std::endl;
	}
	file.close();
}


template<typename T>
Matrix<T> Matrix<T>::apply(T (*func)()){
	Matrix<T> newMatrix(*this);
	for (int i = 0; i < n_rows; ++i){
		data[i].apply(func);
		newMatrix[i] = data[i];
	}
	return newMatrix;
}