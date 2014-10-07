#pragma once

#include <vector>

#include "2DPoint.h"
#include "3DPoint.h"
#include "SegmentIndex.h"
#include "TriangleIndex.h"

/*
*  ласс-контейнер, который хранит информацию о трЄхмерном объекте, который будет отображатьс¤ в окне просмотра,
* или его двумерной проекции
*/
template < typename T >
class CModel
{
public:
	// note: ¤ намеренно вынес эти структуры как public, чтобы к ним можно было обратитьс¤
	// по итераторам дл¤ последующей модификации

	// ”злы трЄхмерной модели
	std::vector<T> Points;

	// »ндексы, определ¤ющие отрезки
	std::vector<CSegmentIndex> Segments;

	// »ндексы, определ¤ющие треугольники
	std::vector<CTriangleIndex> Triangles;

	CModel<T>() {};

	// ƒобавл¤ет узел модели в конец списка (чтобы не нарушить нумерацию)
	void AddPoint(T point)
	{
		Points.push_back(point);
	};

	// ƒобавл¤ет отрезок, соедин¤ющий две вершины
	void AddSegment(int firstIndex, int secondIndex);

	// ƒобавл¤ет треугольник, соедин¤ющий три вершины
	void AddTriangle(int firstIndex, int secondIndex, int thirdIndex);

	// ќчищает структуру
	void Clear()
	{
		Points.clear();
		Segments.clear();
		Triangles.clear();
	};

	// »сключение, которое происходит при попытке добавлени¤ отрезка или треугольника с несуществующими индексами
	class OutOfRange {
	};
};

//  онкретные классы дл¤ двухмерной и трЄхмерной модели соответственно
typedef CModel<C2DPoint> C2DModel;
typedef CModel<C3DPoint> C3DModel;