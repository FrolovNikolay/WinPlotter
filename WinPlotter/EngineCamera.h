#pragma once

#include "3DPoint.h"
#include "Matrix44.h"

/*
* ����� ���������, ���� ������ � ������ ��������� ������ � ��������� ������������ �������
*/
class CEngineCamera
{
public:
	CEngineCamera();
	~CEngineCamera();

	void SetPosition(C3DPoint point);

private:
	// ��������� ������ � ��������� ������������ � ������� ��������
	C3DPoint position;
	CMatrix44 movingMatrix;

	// ���� �������� ������ (� ��������) � �� �������� ������� ��������
	double angleX, angleY, angleZ;


	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;
	void updateInverseRotateMatrixX(double angleX);
	void updateInverseRotateMatrixY(double angleY);
	void updateInverseRotateMatrixZ(double angleZ);

	// ����� ����������� ������� �������������� ��������� ���������� ������������ � ���������� ������
	CMatrix44 transfromMatrix;
	// ��������� ��� ������� � ������ ��������� ��������� � �������� ������
	void updateTransformMatrix();

	// ���������� ������
	double viewDistance;

	// ������� � ������� ��������� ��������� (���������� �� Z)
	double nearZ, farZ;

	// ������ �������� (���������� ����, ���� ����� �������������� ��������)
	int clientWidth, clientHeight;
};

