// Copyright (С) ABBYY (BIT Software), 1993 - 2014. All rights reserved. 
// Автор: Кирилл Яныкин, МФТИ, группа 196
// Описание: Реализация движка, который будет обрабатывать трёхмерные объекты и возвращать их двухмерную реализацию
#pragma once
#include "Camera.h"
#include "Model.h"

class CEngine
{
public:
	// Создаёт движок, который рендерит картинку для окна с заданными размерами
	CEngine();
	CEngine(int windowWidthInPixels, int windowHeightInPixels);
	// Возвращает ссылку на связанную с данным движком камеру
	CCamera& getCamera();
	// Ключевой метод, который обрабатывает трёхмерный объект. По ссылке renderedObject записывает двухмерные примитивы для отрисовки в окне программы
	void Render( const C3DModel& object, C2DModel& renderedObject );

private:
	// Экземпляр камеры, относительно которой будет выполняться рендер
	CCamera camera;
	// Структура, хранящая координаты модели в пространстве камеры
	C3DModel cameraModel;

	// Внутренний метод, который создаёт локальную версию объекта с координатами камеры
	void transform( const C3DModel& object );
	// Фильтрует узлы и элементы модели, которые не попадают в область обзора камеры
	void filter();
	// Проецирует точки внутренней структуры в двухмерную модель для отрисовки на экране
	void render( C2DModel& renderedObject );
};

