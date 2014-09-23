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
	C3DPoint Position;
	CMatrix44 MovingMatrix;

	// ���� �������� ������ (� ��������) � �� �������� ������� ��������
	double AngleX, AngleY, AngleZ;


	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;
	void updateInverseRotateMatrixX(double angleX);
	void updateInverseRotateMatrixY(double angleY);
	void updateInverseRotateMatrixZ(double angleZ);

	// ����� ����������� ������� �������������� ��������� ���������� ������������ � ���������� ������
	CMatrix44 TransfromMatrix;
	// ��������� ��� ������� � ������ ��������� ��������� � �������� ������
	void updateTransformMatrix();

	// ���������� ������
	double ViewDistance;

	// ������� � ������� ��������� ��������� (���������� �� Z)
	double NearZ, FarZ;

	// ������ �������� (���������� ����, ���� ����� �������������� ��������)
	int ClientWidth, ClientHeight;
};

