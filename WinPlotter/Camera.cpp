#include "Camera.h"

CCamera::CCamera()
{
}

// ������������� ������ � �������� ����� ���������� ������������
void CCamera::SetPosition(const C3DPoint& positionPoint) {
	position = positionPoint;

	// ��������� �������, ��� ��� �������� ��������� ������
	updateTransformationMatrix();
}

void CCamera::MoveForward(double speed) {
	// ���������� ����������
	position += vectorN * speed;

	// ��������� ������� ��������������
	updateTransformationMatrix();
}

void CCamera::MoveUp( double speed )
{
	// ���������� ����������
	position += vectorV * speed;

	// ��������� ������� ��������������
	updateTransformationMatrix();
}

void CCamera::MoveSide( double speed )
{
	// ���������� ����������
	position += vectorU * speed;

	// ��������� ������� ��������������
	updateTransformationMatrix();
}

// ��������� ������� �������������� ��� ��������� ������ �� ���������
void CCamera::updateTransformationMatrix()
{
	// ������ ������
	transformationMatrix.Set( 0, 0, vectorU.X );
	transformationMatrix.Set( 0, 1, vectorV.X );
	transformationMatrix.Set( 0, 2, vectorN.X );
	transformationMatrix.Set( 0, 3, 0 );

	// ������ ������
	transformationMatrix.Set( 1, 0, vectorU.Y );
	transformationMatrix.Set( 1, 1, vectorV.Y );
	transformationMatrix.Set( 1, 2, vectorN.Y );
	transformationMatrix.Set( 1, 3, 0 );

	// ������ ������
	transformationMatrix.Set( 2, 0, vectorU.Z );
	transformationMatrix.Set( 2, 1, vectorV.Z );
	transformationMatrix.Set( 2, 2, vectorN.Z );
	transformationMatrix.Set( 2, 3, 0 );

	// �������� ������
	transformationMatrix.Set( 3, 0, -position.dot( vectorU ) );
	transformationMatrix.Set( 3, 1, -position.dot( vectorV ) );
	transformationMatrix.Set( 3, 2, -position.dot( vectorN ) );
	transformationMatrix.Set( 3, 3, 1 );
}

void CCamera::updateVectorU()
{
	// ��������� ������������ U = V x N
	vectorU = vectorV.cross( vectorN );
}

void CCamera::updateVectorV()
{
	// ��������� ������������ V = N x U
	vectorV = vectorN.cross( vectorU );
}