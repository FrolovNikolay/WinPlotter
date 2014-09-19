#pragma once
#include "Windows.h"
#include "EngineDrawer.h"

// �����, ���������� �� �������� � ���������� ������� (� ������������ �����) ����������
class CWinPlotterWindow
{
public:
	CWinPlotterWindow();
	~CWinPlotterWindow();

	// ����������� ������ ����. ���������� true, ���� ����� ���� ������� ��������������� � ��, false � ��������� ������
	bool RegisterWindowClass();

	// �������� ���������� ����. ���������� true, ���� ���� ������� �������, ����� false.
	bool Create();

	// ���������� ����
	void Show(int nCmdShow);

	// ���������� ������ � ������ ������� ��� ��������� ������� � ��������
	int GetDrawingWidth();
	int GetDrawingHeight();

	// ���������� ���������� ����
	HWND GetHandle();

private:
	// ���������� ���� � �������
	HWND windowHandle;

	// ��������� �� ����� ������, ������� ����� ������������ ������
	CEngineDrawer* drawer; 

	// ���������� ������� ��� ����������
	static LRESULT CALLBACK windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	// �������� ������ ����
	static PWCHAR windowClassName;

	// ���������� �������
	void onCreate(); // ��� ����� ����������� ����� ����� ��������� �������� ���� 
	void onPaint(); // ...��� ����������� ����
};

