#pragma once
#include "3DPoint.h"
#include "Matrix44.h"
#include "Model.h"

/*
* ����� ������, ������� ��������� ��������� ������� ������������ ������� � ���������� ������� ��������� ���� ���������
*/
class CEngineCamera
{
public:
	CEngineCamera(int clientWidth, int clientHeight);
	void SetPosition(C3DPoint point);

	// �������� �����, ������� ������������ ��������� ������. �� ������ renderedObject ���������� ���������� ��������� ���
	// ��������� � ���� ���������
	void Render(const C3DModel& object, C2DModel& renderedObject);

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

	// ���������, �������� ���������� ������ � ������������ ������
	C3DModel cameraModel;

	// ���������� �����, ������� ������ ��������� ������ ������� � ������������ ������
	void transform(const C3DModel& object);
	
	// ��������� ���� � �������� ������, ������� �� �������� � ������� ������ ������
	void filter();

	// ���������� ����� ���������� ��������� � ���������� ������ ��� ��������� �� ������
	void render(C2DModel& renderedObject);

	// ���������� ��������������� ���������� ����� ��� ������ ������� ��������������
	C3DPoint modifyPoint(C3DPoint originPoint) const;
};

