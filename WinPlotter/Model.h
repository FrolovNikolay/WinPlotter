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
	// note: � ��������� ����� ��� ��������� ��� public, ����� � ��� ����� ���� ����������
	// �� ���������� ��� ����������� �����������

	// ���� ��������� ������
	std::vector<T> Points;

	// �������, ������������ �������
	std::vector<CSegmentIndex> Segments;

	// �������, ������������ ������������
	std::vector<CTriangleIndex> Triangles;

	CModel<T>() {};

	// ��������� ���� ������ � ����� ������ (����� �� �������� ���������)
	void AddPoint(T point)
	{
		Points.push_back(point);
	};

	// ��������� �������, ����������� ��� �������
	void AddSegment(int firstIndex, int secondIndex);

	// ��������� �����������, ����������� ��� �������
	void AddTriangle(int firstIndex, int secondIndex, int thirdIndex);

	// ������� ���������
	void Clear()
	{
		Points.clear();
		Segments.clear();
		Triangles.clear();
	};

	// ����������, ������� ���������� ��� ������� ���������� ������� ��� ������������ � ��������������� ���������
	class OutOfRange {
	};
};

// ���������� ������ ��� ���������� � ��������� ������ ��������������
typedef CModel<C2DPoint> C2DModel;
typedef CModel<C3DPoint> C3DModel;