#pragma once
#include "3DVertex.h"
/*
* Описывает треугольник из трёх узлов в трёхмерном пространстве  
*/

class C3DTriangle
{
public:
	C3DTriangle() : first(nullptr), second(nullptr), third(nullptr) {};
	C3DTriangle(C3DVertex* _first, C3DVertex* _second, C3DVertex* _third) :
		first(_first), second(_second), third(_third) {};
	~C3DTriangle();

private:
	// Вершины, из которых состоит треугольник (обход по часовой стрелке)
	C3DVertex* first;
	C3DVertex* second;
	C3DVertex* third;
};

