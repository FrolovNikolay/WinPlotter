#pragma once

/*
* Описывает узел трёхмерной модели (графика) в трёхмерном пространстве
*/
class C3DVertex
{
public:
	C3DVertex();
	C3DVertex(double _x, double _y, double _z);

	~C3DVertex();

private:
	// координаты
	double x, y, z;
};

