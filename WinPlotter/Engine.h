// Copyright (�) ABBYY (BIT Software), 1993 - 2014. All rights reserved. 
// �����: ������ ������, ����, ������ 196
// ��������: ���������� ������, ������� ����� ������������ ��������� ������� � ���������� �� ���������� ����������
#pragma once
#include "Camera.h"
#include "Model.h"

class CEngine
{
public:
	// ������ ������, ������� �������� �������� ��� ���� � ��������� ���������
	CEngine();
	CEngine(int windowWidthInPixels, int windowHeightInPixels);
	// ���������� ������ �� ��������� � ������ ������� ������
	CCamera& getCamera();
	// �������� �����, ������� ������������ ��������� ������. �� ������ renderedObject ���������� ���������� ��������� ��� ��������� � ���� ���������
	void Render( const C3DModel& object, C2DModel& renderedObject );

private:
	// ��������� ������, ������������ ������� ����� ����������� ������
	CCamera camera;
	// ���������, �������� ���������� ������ � ������������ ������
	C3DModel cameraModel;

	// ���������� �����, ������� ������ ��������� ������ ������� � ������������ ������
	void transform( const C3DModel& object );
	// ��������� ���� � �������� ������, ������� �� �������� � ������� ������ ������
	void filter();
	// ���������� ����� ���������� ��������� � ���������� ������ ��� ��������� �� ������
	void render( C2DModel& renderedObject );
};

