#pragma once

/*
* ��������� ���� ��������� ������ (�������) � ��������� ������������
*/
class C3DVertex
{
public:
	C3DVertex();
	C3DVertex(double _x, double _y, double _z);

	~C3DVertex();

private:
	// ����������
	double x, y, z;
};

