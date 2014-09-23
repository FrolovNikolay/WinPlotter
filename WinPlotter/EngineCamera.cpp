#include "EngineCamera.h"
#include <cmath>

CEngineCamera::CEngineCamera() :
AngleX(0), AngleY(0), AngleZ(1)
{
	Position = C3DPoint();
	updateInverseRotateMatrixX(0);
	updateInverseRotateMatrixY(0);
	updateInverseRotateMatrixZ(1);
	updateTransformMatrix();
}


CEngineCamera::~CEngineCamera()
{
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
void CEngineCamera::updateInverseRotateMatrixX(double angle) {
	inverseRotateMatrixX = CMatrix44(
		1, 0, 0, 0,
		0, cos(-angle), sin(-angle), 0,
		0, -sin(-angle), cos(-angle), 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::updateInverseRotateMatrixY(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), 0, -sin(-angle), 0,
		0, 1, 0, 0,
		sin(-angle), 0, cos(-angle), 0,
		0, 0, 0, 1
		);
}

void CEngineCamera::updateInverseRotateMatrixZ(double angle) {
	inverseRotateMatrixX = CMatrix44(
		cos(-angle), sin(-angle), 0, 0,
		-sin(-angle), cos(-angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

void CEngineCamera::updateTransformMatrix() {
	TransfromMatrix = CMatrix44();
	TransfromMatrix.multiplyAt(MovingMatrix);
	TransfromMatrix.multiplyAt(inverseRotateMatrixY);
	TransfromMatrix.multiplyAt(inverseRotateMatrixX);
	TransfromMatrix.multiplyAt(inverseRotateMatrixZ);
}