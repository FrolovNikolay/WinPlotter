#include "EngineCamera.h"
#include <cmath>

CEngineCamera::CEngineCamera() :
AngleX(0), AngleY(0), AngleZ(1), ViewDistance(1), ClientHeight(0), ClientWidth(0)
{
	Position = C3DPoint(10, 10, 10);
	UpdateInverseRotateMatrixX(0);
	UpdateInverseRotateMatrixY(0);
	UpdateInverseRotateMatrixZ(1);
	UpdateTransformMatrix();
}

void CEngineCamera::SetPosition(C3DPoint point) {
	Position = point;
	MovingMatrix = CMatrix44(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-Position.X, -Position.Y, -Position.Z, 1
	);
}

// Обновления матриц преобразования
void CEngineCamera::UpdateInverseRotateMatrixX(double angle) {
	inverseRotateMatrixX = CMatrix44(
		1, 0, 0, 0,
		0, cos(-angle), sin(-angle), 0,
		0, -sin(-angle), cos(-angle), 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::UpdateInverseRotateMatrixY(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), 0, -sin(-angle), 0,
		0, 1, 0, 0,
		sin(-angle), 0, cos(-angle), 0,
		0, 0, 0, 1
		);
}

void CEngineCamera::UpdateInverseRotateMatrixZ(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), sin(-angle), 0, 0,
		-sin(-angle), cos(-angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::UpdateTransformMatrix() {
	TransfromMatrix = CMatrix44();
	TransfromMatrix.MultiplyRight(MovingMatrix);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixY);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixX);
	TransfromMatrix.MultiplyRight(inverseRotateMatrixZ);
}