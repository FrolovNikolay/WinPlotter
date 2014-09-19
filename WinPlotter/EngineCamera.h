#pragma once

#include "3DPoint.h"
#include "Matrix44.h"

/*
* Задаёт положение, угол зрения и другие параметры камеры в трёхмерном пространстве графика
*/
class CEngineCamera
{
public:
	CEngineCamera();
	~CEngineCamera();

	void SetPosition(C3DPoint point);

private:
	// Положение камеры в трёхмерном пространстве и матрица переноса
	C3DPoint position;
	CMatrix44 movingMatrix;

	// Углы поворота камеры (в радианах) и их обратные матрицы поворота
	double angleX, angleY, angleZ;


	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;
	void updateInverseRotateMatrixX(double angleX);
	void updateInverseRotateMatrixY(double angleY);
	void updateInverseRotateMatrixZ(double angleZ);

	// Общая вычисленная матрица преобразования координат трёхмерного пространства в координаты камеры
	CMatrix44 transfromMatrix;
	// Обновляет эту матрицу в случае изменения положения и вращения камеры
	void updateTransformMatrix();

	// Расстояние обзора
	double viewDistance;

	// Ближняя и дальная плоскости отсечения (координаты по Z)
	double nearZ, farZ;

	// Размер проекции (разрешение окна, куда будет генерироваться картинка)
	int clientWidth, clientHeight;
};

