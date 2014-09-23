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
	C3DPoint Position;
	CMatrix44 MovingMatrix;

	// Углы поворота камеры (в радианах) и их обратные матрицы поворота
	double AngleX, AngleY, AngleZ;


	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;
	void updateInverseRotateMatrixX(double angleX);
	void updateInverseRotateMatrixY(double angleY);
	void updateInverseRotateMatrixZ(double angleZ);

	// Общая вычисленная матрица преобразования координат трёхмерного пространства в координаты камеры
	CMatrix44 TransfromMatrix;
	// Обновляет эту матрицу в случае изменения положения и вращения камеры
	void updateTransformMatrix();

	// Расстояние обзора
	double ViewDistance;

	// Ближняя и дальная плоскости отсечения (координаты по Z)
	double NearZ, FarZ;

	// Размер проекции (разрешение окна, куда будет генерироваться картинка)
	int ClientWidth, ClientHeight;
};

