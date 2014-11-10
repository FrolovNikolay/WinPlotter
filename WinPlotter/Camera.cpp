#include "Camera.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <cmath>

CCamera::CCamera() : nearZ(1), farZ(100)
{
	SetFieldOfViewAngle( M_PI / 6 );
	updateFieldDistance();

	// ���������� ������ ������� ����� ��� Z
	position = C3DPoint( -10, 0, 0 );
	vectorN = C3DPoint( 0, 0, 1 );
	vectorV = C3DPoint( 0, 1, 0 );
	updateVectorU();
}

// ������������� ������ � �������� ����� ���������� ������������
void CCamera::SetPosition( const C3DPoint& positionPoint ) {
	position = positionPoint;

	// ��������� �������, ��� ��� �������� ��������� ������
	updateTransformationMatrix();
}

void CCamera::MoveForward( double speed ) {
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

void CCamera::SetWindowSize( int _widthInPixels, int _heightInPixels )
{
	assert( 0 < _widthInPixels, 0 < _heightInPixels );
	windowWidthInPixels = _widthInPixels;
	windowHeightInPixels = _heightInPixels;
	aspectRatio = windowWidthInPixels / windowHeightInPixels;

	// ����� ��������� �������� ���� ��������� ���������� ������ ������
	updateFieldDistance();
}

void CCamera::SetFieldOfViewAngle( double angle ) {
	assert( 0 < angle && angle < 2 * M_PI );
	fieldOfViewInRadians = angle;
	tanFieldOfView = tan( angle / 2 );

	updateFieldDistance();
}

void CCamera::SetZDistances( double _nearZ, double _farZ )
{
	// ������� ����� ���������� �� ��, ��� ����� ��� ������ ������.
	assert( 0 < _nearZ && _nearZ < _farZ );
	nearZ = _nearZ;
	farZ = _farZ;
}

void CCamera::TransformPoint( const C3DPoint& originPoint, C3DPoint& modifiedPoint ) const
{
	// ���������� �������� ��������������� �������
	transformationMatrix.TransformPoint( originPoint, modifiedPoint );
}

void CCamera::ProjectPoint( const C3DPoint& originPoint, C2DPoint& projectedPoint ) const
{
	projectedPoint.X = fieldDistance * originPoint.X / originPoint.Z + ( 0.5 * windowWidthInPixels - 0.5 );
	projectedPoint.Y = -fieldDistance * originPoint.Y * aspectRatio / originPoint.Z + ( 0.5 * windowHeightInPixels - 0.5 );
}

bool CCamera::IsPointInFieldOfView( const C3DPoint& point ) const
{
	// ��������� ��������� �� Z
	if ( !( nearZ <= point.Z  && point.Z <= farZ ) ) {
		return false;
	}
	// ����� ������� z = [+-]tg(FOV/2) * x
	else if ( !( abs(point.X) <= point.Z / tanFieldOfView ) ) {
		return false;
	}

	return true;
}

void CCamera::updateVectorU()
{
	// ��������� ������������ U = V x N
	vectorU = vectorV.cross( vectorN );
	updateTransformationMatrix();
}

void CCamera::updateVectorV()
{
	// ��������� ������������ V = N x U
	vectorV = vectorN.cross( vectorU );
	updateTransformationMatrix();
}

void CCamera::updateFieldDistance()
{
	fieldDistance = 0.5f * windowWidthInPixels * tanFieldOfView;
}