#pragma once

// Структура, задающая точку в трёхмерном пространстве (вектор-строка)
struct C3DPoint
{
public:
	double X, Y, Z;

	C3DPoint(double _x = 0, double _y = 0, double _z = 0);
};

