/*
author: Timur Khusaenov
class: CWinMain
description:
	����� ��������� ���������, ����������� � ���������� WinPlotter.
	��� ���������� ������ ������ ���������� �������� CWinPlotter, ������� ��������� ��������� �������
*/

#pragma once

#include "Windows.h"
#include <vector>

#include "CWinPlotter.h"


class CWinMain
{
public:
	static bool registerClass( HINSTANCE hInstance );	// ���������������� ����� ����
	HWND create( HINSTANCE hInctance );					// ������� ��������� ����
	void show( int cmdShow );							// �������� ����
	friend HWND createButton( LPCWSTR title, int X, int Y, HWND parent, HMENU id );	// ������� ������ �  ������������������� defButtonPorc
	friend void setButtonPos( HWND hWnd, int X, int Y );							// �������� ������� ������
	static const int Size = 25;							// ����� ������
	static const int MouseWheelSens = 25;				// ���������������� �������� ����

protected:
	void OnDestroy();									// ���������� ����
	void OnCreate( HWND hWnd );							// �������� ��� �������� ����
	LRESULT OnCommand( WPARAM wParam, LPARAM lParam );	// ��������� WM_COMMAND
	LRESULT OnFormCommand( WPARAM wParam, LPARAM lParam );	// ��������� ������� � ���� �������
	void ShowFormulaForm();								// ���������� ������ ����� �������
	void ResizeChildrens();								// ����� ��������� � �������� �������� ����
	void Move();										// ����������� �� ������� (����� �������������� ������� � WinPlotter)
	void IdentifyCommand( HWND hWnd );					// ������������� ����� ������ ���� ������ � ����������� �������� � ����������� �� �����
	void TakeFormula();									// ������� �������
	LRESULT OnKeyDown( WPARAM wParam, LPARAM lParam );	// ��������� ������� ������ (������� ��� ����������� �� �������)
	LRESULT OnKeyUp( WPARAM wParam, LPARAM lParam );	// ��������� ������� ������

private:
	enum TDirection { D_None, D_Top, D_Bot, D_Right, D_Left };
	enum TZoom { Z_None, Z_Minus, Z_Plus };

	POINT curPos, oldCurPos;							// ��������� �������
	bool curMove = false;								// ��������� ��������
	TDirection moveDirection = D_None;					// ����������� ��������
	TDirection rotateDirection = D_None;				// ����������� ��������
	TZoom zoom = Z_None;								// ���
	static WNDPROC defButtonProc;						// ��������� ���������� ������-���������
	static WNDPROC defMouseProc;						// ��������� ���������� ����� ���������
	HWND handle;										// ����� ����
	HWND hChild;										// ����� �������
	HWND hFormulaForm;									// ����� �������
	CWinPlotter winPlotter;								// ����� ��� ������ ��������� �������
	UINT_PTR timer;										// ������

	// ������ ������
	HWND hButtonMoveTop, hButtonMoveBot, hButtonMoveLeft, hButtonMoveRight;
	HWND hButtonRotateUp, hButtonRotateDown, hButtonRotateLeft, hButtonRotateRight;
	HWND hButtonZoomPlus, hButtonZoomMinus;

	// ����������� ���������
	static LRESULT __stdcall windowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static LRESULT __stdcall buttonProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static LRESULT __stdcall mouseProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static BOOL __stdcall formulaDialogProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};