#pragma once

#include <vector>

#include "2DPoint.h"
#include "3DPoint.h"
#include "SegmentIndex.h"
#include "TriangleIndex.h"

/*
* �����-���������, ������� ������ ���������� � ��������� �������, ������� ����� ������������ � ���� ���������,
* ��� ��� ��������� ��������
*/
template < typename T >
class CModel
{
public:
	CModel<T>();

	// ��������� ���� ������ � ����� ������ (����� �� �������� ���������)
	void AddPoint(T);

	// ��������� �������, ����������� ��� �������
	void AddSegment(int firstIndex, int secondIndex);

	// ��������� �����������, ����������� ��� �������
	void AddTriangle(int firstIndex, int secondIndex, int thirdIndex);

	// ����������, ������� ���������� ��� ������� ���������� ������� ��� ������������ � ��������������� ���������
	class OutOfRange {
	};

private:
	// ���� ��������� ������
	std::vector<T> points;

	// �������, ������������ �������
	std::vector<CSegmentIndex> segments;

	// �������, ������������ ������������
	std::vector<CTriangleIndex> triangles;
};

// ���������� ������ ��� ���������� � ��������� ������ ��������������
typedef CModel<C2DPoint> C2DModel;
typedef CModel<C3DPoint> C3DModel;