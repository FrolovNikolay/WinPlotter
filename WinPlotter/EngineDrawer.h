#pragma once
#include "Windows.h"

/*
* �����, ���������� ��������� �������� � ������ ����� � ���� ����������
*/
class CEngineDrawer
{
public:
	CEngineDrawer(HWND windowHandle);
	~CEngineDrawer();

	// ��������� ���� ��������� (�������� ������ GetDC)
	bool StartDraw();

	// ����������� ���� ��������� (�������� ������ ReleaseDC)
	void FinishDraw();

	// ������ ����� �������� ������
	void DrawPoint(int x, int y, COLORREF color);

	// ������ ������� �������� ������ ����� ����� �������
	void DrawLine(int xStart, int yStart, int xFinish, int yFinish, COLORREF color);

	// ��������� ��� ���������� ������� �������
	// void FillWithColor(COLORREF color);
	

private:
	bool isRunning;
	HDC hdc;
	HWND windowHandle;

	
};

