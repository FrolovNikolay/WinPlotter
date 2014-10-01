#pragma once

#include "3DPoint.h"
#include "Matrix44.h"
#include "3DObject.h"

/*
* Класс движка, который переводит трёхмерные объекты пространства графика в двухмерные объекты контекста окна отрисовки
*/
class CEngineCamera
{
public:
	CEngineCamera();
	void SetPosition(C3DPoint point);

	// Первый ключевой метод, который обрабатывает трёхмерный объект
	void InitWithObject(const C3DObject& object);

	// Возвращает набор двумерных примитивов, отсортированных в порядке отрисовки, которые необходимо отрисовать в окне
	void Render();

private:
	// Положение камеры в трёхмерном пространстве и матрица переноса
	C3DPoint Position;
	CMatrix44 MovingMatrix;

	// Углы поворота камеры (в радианах) и их обратные матрицы поворота
	double AngleX, AngleY, AngleZ;
	CMatrix44 inverseRotateMatrixX, inverseRotateMatrixY, inverseRotateMatrixZ;

	// Для каждого направления угла делаем метод, который обновляет соответствующую обратную матрицу поворота 
	void UpdateInverseRotateMatrixX(double angleX);
	void UpdateInverseRotateMatrixY(double angleY);
	void UpdateInverseRotateMatrixZ(double angleZ);

	// Общая вычисленная матрица преобразования координат трёхмерного пространства в координаты камеры
	CMatrix44 TransfromMatrix;

	// Обновляет эту матрицу в случае изменения положения и вращения камеры
	void UpdateTransformMatrix();

	// Расстояние обзора
	double ViewDistance;

	// Ближняя и дальная плоскости отсечения (координаты по Z)
	double NearZ, FarZ;

	// Размер проекции (разрешение окна, куда будет генерироваться картинка)
	int ClientWidth, ClientHeight;
};

