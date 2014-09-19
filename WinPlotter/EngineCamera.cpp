#include "EngineCamera.h"
#include <cmath>

CEngineCamera::CEngineCamera() :
angleX(0), angleY(0), angleZ(1)
{
	position = C3DPoint(0, 0, 0);
	updateInverseRotateMatrixX(0);
	updateInverseRotateMatrixY(0);
	updateInverseRotateMatrixZ(1);
	updateTransformMatrix();
}


CEngineCamera::~CEngineCamera()
{
}

void CEngineCamera::SetPosition(C3DPoint point) {
	position = point;
	movingMatrix = CMatrix44(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-position.x, -position.y, -position.z, 1
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
	transfromMatrix = CMatrix44();
	transfromMatrix.multiplyAt(movingMatrix);
	transfromMatrix.multiplyAt(inverseRotateMatrixY);
	transfromMatrix.multiplyAt(inverseRotateMatrixX);
	transfromMatrix.multiplyAt(inverseRotateMatrixZ);
}