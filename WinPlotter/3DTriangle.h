#pragma once
#include "3DVertex.h"
/*
* ��������� ����������� �� ��� ����� � ��������� ������������  
*/

class C3DTriangle
{
public:
	C3DTriangle() : first(nullptr), second(nullptr), third(nullptr) {};
	C3DTriangle(C3DVertex* _first, C3DVertex* _second, C3DVertex* _third) :
		first(_first), second(_second), third(_third) {};
	~C3DTriangle();

private:
	// �������, �� ������� ������� ����������� (����� �� ������� �������)
	C3DVertex* first;
	C3DVertex* second;
	C3DVertex* third;
};

