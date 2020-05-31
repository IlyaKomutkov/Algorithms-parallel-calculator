#include "testing.hpp"

using namespace std;


void TestingSystem::testVector(){

	valarray<double> v1 {1, 1, 1};
	valarray<double> v2 {2, 2, 2};
	valarray<double> v3;
	valarray<double> v4 {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix<double> m1("matrix1.csv");

	std::cout << "\t***VECTOR TEST***\t" << std::endl;

	cout << "v1 : " << v1;
	cout << "v2 : " << v2;
	cout << "v3 : " << v4;

	valarray<double> v5 = v4[slice(1, 4 ,2)];
	cout << "v3[1:5:2] : " << v5;

	v3 = v4.apply([](double x)->double {return (x+1);});
	cout << "to v3 apply +1 : " << v3;

	long double c = normVec(v1);
	cout << "norm(v1) : " << c << std::endl;

	v3 = 5 + v1;
	cout << "5 + v1 : " << v3;

	v3 = 5 * v1;
	cout << "5v1 : " << v3;

	v3 = v1 / 5;
	cout << "0.5v1 : " << v3;

	v3 = v1 + v2;
	cout << "v1 + v2 : " << v3;

	v3 = v1 / v2;
	cout << "v1 / v2 : " << v3;

	v3 = v1 * v2;
	cout << "v1 * v2 : " << v3;

	v3 = v1 - v2;
	cout << "v1 - v2 : " << v3;

	v3 = Dot(v1, v2);
	cout << "v1.v2 : " << v3;

	v3 =  Matrix<double>::linspace(0, 10, 7);
	cout << "linspace(0, 10, 7) : " << v3;

	cout << "m1 : \n" << m1;
	v3 = v1 * m1;
	cout << "v1 * m1 : " << v3;

	vecToCsv(v3, "vec3.csv");
}

void TestingSystem::testMatrix(){

	Matrix<double> m1("matrix1.csv");
	Matrix<double> m2("matrix2.csv");
	Matrix<double> m3("matrix3.csv");
	Matrix<double> m4(3, 3, 1);
	Matrix<double> m5;

	std::cout << "\t***MATRIX TEST***\t" << std::endl;

	cout << "m1 : \n" << m1;
	cout << "m2 : \n" << m2;
	cout << "m3 : \n" << m3;
	cout << "m4 : \n" << m4;

	cout << "The size of m4 is ";
	m4.printSize();

	m5 = m2 - m4;
	cout << "m2 - m4 :\n" << m5;

	m5 = m2 + m4;
	cout << "m2 + m4 :\n" << m5;

	m5 = m2 / m4;
	cout << "m2 / m4 :\n" << m5;

	m5 = m2 - m4;
	cout << "m2 - m4 :\n" << m5;

	m5 = 5 * m4;
	cout << "5 * m4 :\n" << m5;

	cout << "The size of m3 is ";
	m3.printSize();
	m3.transpose();
	cout << "After transpose the size of m3 is ";
	m3.printSize();

	m5 = m2 * m1;
	cout << "m2 * m1:\n" << m5;

	m5.toCsv("matrix5.csv");
}