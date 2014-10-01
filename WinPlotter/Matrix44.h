#pragma once
#include "3DPoint.h"

/*
* ����� ������� 4�4 ��� ������ � ���������������� 
*/
class CMatrix44
{
public:
	CMatrix44();
	CMatrix44(const double initialElements[4][4]);
	CMatrix44(const CMatrix44& otherMatrix);
	CMatrix44(
		double a11, double a12, double a13, double a14,
		double a21, double a22, double a23, double a24,
		double a31, double a32, double a33, double a34,
		double a41, double a42, double a43, double a44
		);

	// ��������� ����������� ������� �� ���������� ������
	void MultiplyRight(const CMatrix44& otherMatrix);

	// �������� ������� �� ������-������ ����� (�������� ���������� ��������� ��������)
	C3DPoint ProjectPoint(const C3DPoint originPoint) const;

	// �������� ������� M[row][column]
	double Get(int row, int column) const;

	// ����������� ������� M[row][column] = value
	void Set(int row, int column, double value);

	// ������ �������
	static const int MatrixSize = 4;

	// ����� ���������� ��� ���������� �������� ��� ��������
	class OutOfRange {

	};

private:
	// ���������� �������� �������
	double elements[4][4];
};

