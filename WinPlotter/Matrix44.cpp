#include "Matrix44.h"


CMatrix44::CMatrix44()
{
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			elements[GetPosition(i, j)] = i == j ? 1 : 0;
		}
	}
}

CMatrix44::CMatrix44(double initialElements[16]) {
	for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
		elements[i] = initialElements[i];
	}
}

CMatrix44::CMatrix44(CMatrix44* otherMatrix) {
	for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
		elements[i] = otherMatrix->elements[i];
	}
}

CMatrix44::CMatrix44(
	double a11, double a12, double a13, double a14,
	double a21, double a22, double a23, double a24,
	double a31, double a32, double a33, double a34,
	double a41, double a42, double a43, double a44
) {
	elements[0] = a11;
	elements[1] = a12;
	elements[2] = a13;
	elements[3] = a14;
	elements[4] = a21;
	elements[5] = a22;
	elements[6] = a23;
	elements[7] = a24;
	elements[8] = a31;
	elements[9] = a32;
	elements[10] = a33;
	elements[11] = a34;
	elements[12] = a41;
	elements[13] = a42;
	elements[14] = a43;
	elements[15] = a44;
}

int CMatrix44::GetPosition(int row, int column) {
	return MATRIX_SIZE * row + column;
}

void CMatrix44::multiplyAt(CMatrix44& otherMatrix) {
	double result[16];
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			int p = GetPosition(i, j);
			result[p] = 0;
			for (int k = 0; k < MATRIX_SIZE; k++) {
				result[p] += elements[GetPosition(i, k)] * otherMatrix.Get(k, j);
			}
		}
	}
	for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
		elements[i] = result[i];
	}
}

double CMatrix44::Get(int row, int column) {
	return elements[GetPosition(row, column)];
}

void CMatrix44::Set(int row, int column, double value) {
	elements[GetPosition(row, column)] = value;
}


CMatrix44::~CMatrix44()
{
}
