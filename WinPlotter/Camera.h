// Copyright (�) ABBYY (BIT Software), 1993 - 2014. All rights reserved. 
// �����: ������ ������, ����, ������ 196
// ��������: �����, ����������� ������ UVN-������ ��� ������������� � ��������� ������������
#pragma once
#include "2DPoint.h"
#include "3DPoint.h"
#include "Matrix44.h"

class CCamera {

public:
	// ����������� �� ���������
	CCamera();
	// ����������� ���������� �������� ����� originPoint � ���������� ������� ������ � ���������� �� � modifiedPoint
	void TransformPoint( const C3DPoint& originPoint, C3DPoint& modifiedPoint ) const;
	// ���������, ��������� �� ����� point � ������� ��������� ������
	bool IsPointInFieldOfView( const C3DPoint& point ) const;
	// ���������� ����� � ��������� ����������� ������ � ��������� ����������������� ���������� �������� ������.
	void ProjectPoint( const C3DPoint& originPoint, C2DPoint& projectedPoint ) const;
	// ������������� ������ � �������� ����� ���������� ������������
	void SetPosition( const C3DPoint& positionPoint );
	// ���������� ������ ����� (��� ������������� �������� speed) � ����� (��� �������������)
	void MoveForward( double speed = 1.0f );
	// ���������� ������ ����� (��� ������������� �������� speed) � ���� (��� �������������)
	void MoveUp( double speed = 1.0f );
	// ���������� ������ ������ (��� ������������� �������� speed) � ����� (��� �������������)
	void MoveSide( double speed = 1.0f );
	// ������������� ���������� ����, ��� �������� ����� ������������� �������������� ���������
	void SetWindowSize( int widthInPixels, int heightInPixels );
	// ������������� ������� � ������� ��������� ��������� (0 < nearZ < farZ)
	void SetZDistances( double nearZ, double farZ );
	// ������������� ���� ������ ������ � ��������
	void SetFieldOfViewAngle( double angle );


private:
	C3DPoint position; // ��������� ������ � ��������� ������������	
	C3DPoint vectorN; // ������, ���� "�������" ������ (N � ������������ UVN)
	C3DPoint vectorV; // ������ "�����" � ������ (V � ������������ UVN)
	C3DPoint vectorU; // ������ "������" (���� ��������� ������������ N x V) (N � ������������ UVN)
	CMatrix44 transformationMatrix; // ������� �������������� ������ ������

	double fieldOfViewInRadians; // ���� ������ ������ � ��������
	double tanFieldOfView; // ������� �������� ����� ����, ��� ��� �� ������������ ����� �����
	double fieldDistance; // ���������� �� ������ �� ��������� ��������
	int windowWidthInPixels; // ������ ���� � ��������, ��� �������� ����� ����������� ��������������
	int windowHeightInPixels; // ������ ���� � ��������, ��� �������� ����� ����������� ��������������
	double aspectRatio; // ����������� ������ � ������

	double nearZ; // ������� ��������� ��������� ������
	double farZ; // ������� ��������� ��������� ������

	void updateVectorU(); // ��������� ������ U ��� ��������� ������ �� �������� N ��� V (��� ��� ��� �������� ��������� �������������)
	void updateVectorV(); // ����������� �������� ��� ������� V
	void updateTransformationMatrix(); // ��������� ������� �������������� ��� ��������� ������ �� ���������
	void updateFieldDistance(); // ��������� �������� ���������� �� ������ �� ��������� �������� ��� ��������� ��������� ����������
};

