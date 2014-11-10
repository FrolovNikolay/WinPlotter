// Copyright (С) ABBYY (BIT Software), 1993 - 2014. All rights reserved. 
// Автор: Кирилл Яныкин, МФТИ, группа 196
// Описание: Класс, реализующий модель UVN-камеры для представления в трёхмерном пространстве
#pragma once
#include "2DPoint.h"
#include "3DPoint.h"
#include "Matrix44.h"

class CCamera {

public:
	// Конструктор по умолчанию
	CCamera();
	// Преобразует координаты исходной точки originPoint в координаты системы камеры и записывает их в modifiedPoint
	void TransformPoint( const C3DPoint& originPoint, C3DPoint& modifiedPoint ) const;
	// Проверяет, находится ли точка point в области видимости камеры
	bool IsPointInFieldOfView( const C3DPoint& point ) const;
	// Проецирует точку в трёхмерных координатах камеры в двумерные аксонометрические координаты проекции камеры.
	void ProjectPoint( const C3DPoint& originPoint, C2DPoint& projectedPoint ) const;
	// Устанавливает камеру в заданную точку трёхмерного пространства
	void SetPosition( const C3DPoint& positionPoint );
	// Перемещает камеру вперёд (при положительном значении speed) и назад (при отрицательном)
	void MoveForward( double speed = 1.0f );
	// Перемещает камеру вверх (при положительном значении speed) и вниз (при отрицательном)
	void MoveUp( double speed = 1.0f );
	// Перемещает камеру вправо (при положительном значении speed) и влево (при отрицательном)
	void MoveSide( double speed = 1.0f );
	// Устанавливает разрешение окна, для которого будет производиться преобразование координат
	void SetWindowSize( int widthInPixels, int heightInPixels );
	// Устанавливает ближнюю и дальнюю плоскости отсечения (0 < nearZ < farZ)
	void SetZDistances( double nearZ, double farZ );
	// Устанавливает угол обзора камеры в радианах
	void SetFieldOfViewAngle( double angle );


private:
	C3DPoint position; // Положение камеры в трёхмерном пространстве	
	C3DPoint vectorN; // Вектор, куда "смотрит" камера (N в аббревиатуре UVN)
	C3DPoint vectorV; // Вектор "вверх" у камеры (V в аббревиатуре UVN)
	C3DPoint vectorU; // Вектор "вправо" (есть векторное произведение N x V) (N в аббревиатуре UVN)
	CMatrix44 transformationMatrix; // Матрица преобразования данной камеры

	double fieldOfViewInRadians; // Угол обзора камеры в радианах
	double tanFieldOfView; // Тангенс половины этого угла, так как он используется очень часто
	double fieldDistance; // Расстояние от камеры до плоскости проекции
	int windowWidthInPixels; // Ширина окна в пикселях, для которого будет выполняться преобразование
	int windowHeightInPixels; // Высота окна в пикселях, для которого будет выполняться преобразование
	double aspectRatio; // Соотношение ширины к высоте

	double nearZ; // Ближняя плоскость отсечения камеры
	double farZ; // Дальняя плоскость отсечения камеры

	void updateVectorU(); // Обновляет вектор U при изменении любого из векторов N или V (так как это является векторным произведением)
	void updateVectorV(); // Аналогичная операция для вектора V
	void updateTransformationMatrix(); // Обновляет матрицу преобразования при изменении одного из компонент
	void updateFieldDistance(); // Обновляет значение расстояния от камеры до плоскости проекции при изменении некоторых параметров
};

