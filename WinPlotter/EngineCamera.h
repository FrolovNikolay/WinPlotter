#pragma once
#include "3DPoint.h"
#include "Matrix44.h"
#include "Model.h"

/*
* Класс движка, который переводит трёхмерные объекты пространства графика в двухмерные объекты контекста окна отрисовки
*/
class CEngineCamera
{
public:
	CEngineCamera(int clientWidth, int clientHeight);
	void SetPosition(C3DPoint point);

	// Ключевой метод, который обрабатывает трёхмерный объект. По ссылке renderedObject записывает двухмерные примитивы для
	// отрисовки в окне программы
	void Render(const C3DModel& object, C2DModel& renderedObject);

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

	// Структура, хранящая координаты модели в пространстве камеры
	C3DModel cameraModel;

	// Внутренний метод, который создаёт локальную версию объекта с координатами камеры
	void transform(const C3DModel& object);
	
	// Фильтрует узлы и элементы модели, которые не попадают в область обзора камеры
	void filter();

	// Проецирует точки внутренней структуры в двухмерную модель для отрисовки на экране
	void render(C2DModel& renderedObject);

	// Возвращает преобразованные координаты точки при помощи матрицы преобразований
	C3DPoint modifyPoint(C3DPoint originPoint) const;
};

