#pragma once

#include "3DPoint.h"
#include "Matrix44.h"
#include "3DObject.h"

/*
* ����� ������, ������� ��������� ��������� ������� ������������ ������� � ���������� ������� ��������� ���� ���������
*/
class CEngineCamera
{
public:
	CEngineCamera();
	void SetPosition(C3DPoint point);

	// ������ �������� �����, ������� ������������ ��������� ������
	void InitWithObject(const C3DObject& object);

	// ���������� ����� ��������� ����������, ��������������� � ������� ���������, ������� ���������� ���������� � ����
	void Render();

private:
	// ��������� ������ � ��������� ������������ � ������� ��������
	C3DPoint Position;
	CMatrix44 MovingMatrix;

	// ���� �������� ������ (� ��������) � �� �������� ������� ��������
	double AngleX, AngleY, AngleZ;
	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;

	// ��� ������� ����������� ���� ������ �����, ������� ��������� ��������������� �������� ������� �������� 
	void UpdateInverseRotateMatrixX(double angleX);
	void UpdateInverseRotateMatrixY(double angleY);
	void UpdateInverseRotateMatrixZ(double angleZ);

	// ����� ����������� ������� �������������� ��������� ���������� ������������ � ���������� ������
	CMatrix44 TransfromMatrix;

	// ��������� ��� ������� � ������ ��������� ��������� � �������� ������
	void UpdateTransformMatrix();

	// ���������� ������
	double ViewDistance;

	// ������� � ������� ��������� ��������� (���������� �� Z)
	double NearZ, FarZ;

	// ������ �������� (���������� ����, ���� ����� �������������� ��������)
	int ClientWidth, ClientHeight;
};

