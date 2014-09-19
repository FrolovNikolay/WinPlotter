#pragma once

/*
* Задаёт матрицу 4х4 для работы с преобразованиями 
*/
class CMatrix44
{
public:
	CMatrix44();
	CMatrix44(double initialElements[16]);
	CMatrix44(CMatrix44* otherMatrix);
	CMatrix44(
		double a11, double a12, double a13, double a14,
		double a21, double a22, double a23, double a24,
		double a31, double a32, double a33, double a34,
		double a41, double a42, double a43, double a44
	);


	// Домножает сущестующую матрицу на переданную справа
	void multiplyAt(CMatrix44& otherMatrix);

	~CMatrix44();

	static int GetPosition(int row, int column);
	double Get(int row, int column);
	void Set(int row, int column, double value);

private:
	static const int MATRIX_SIZE = 4;
	double elements[16];
};

