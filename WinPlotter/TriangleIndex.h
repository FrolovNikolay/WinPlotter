#pragma once

// ���������, �������� ������� ����� ��� ������������ � ��������� ������������
struct CTriangleIndex
{
	int First, Second, Third;
	CTriangleIndex(int first, int second, int third);

	// ����������, �����������, ����� �� ����� ������� ����������� � ����������� ��� �������������� ���������
	class IncorrectIndex
	{
	};
};

