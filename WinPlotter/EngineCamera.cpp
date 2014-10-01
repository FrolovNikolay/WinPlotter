#include "EngineCamera.h"
#include <cmath>

CEngineCamera::CEngineCamera(int clientWidth, int clientHeight) :
AngleX(0), AngleY(0), AngleZ(1), ViewDistance(1), ClientHeight(clientHeight), ClientWidth(clientWidth)
{
	Position = C3DPoint(10, 10, 10);
	UpdateInverseRotateMatrixX(0);
	UpdateInverseRotateMatrixY(0);
	UpdateInverseRotateMatrixZ(1);
	UpdateTransformMatrix();
}

void CEngineCamera::Render(const C3DModel& object, C2DModel& renderedObject) {
	transform(object);
	filter();
	render(renderedObject);
}

void CEngineCamera::transform(const C3DModel& object) {
	// Копируем исходный объект
	cameraModel = C3DModel(object);

	// Пробегаемся по всем его точкам и модифицируем при помощи матрицы преобразований
	for (auto point = cameraModel.Points.begin(); point != cameraModel.Points.end(); point++) {
		*point = modifyPoint(*point);
	}
}

void CEngineCamera::filter() {
	// TODO: удаление (и модификация) элементов внутренней структуры
}

void CEngineCamera::render(C2DModel& renderedObject) {
	// TODO: преобразование трёхмерных координат точек в контексте камеры в двухмерные координаты в контексте окна
}

C3DPoint CEngineCamera::modifyPoint(C3DPoint originPoint) const {
	return TransfromMatrix.ProjectPoint(originPoint);
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