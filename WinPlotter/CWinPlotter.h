#pragma once
#include "Windows.h"

class CWinPlotter {
public:
	static bool registerClass( HINSTANCE hInstance );
	HWND create( HINSTANCE hInctance, HWND parent );
	void show( int cmdShow );

	void moveX( LONG times = 1 );
	void moveY( LONG times = 1 );
	void rotateX( LONG times = 1 );
	void rotateY( LONG times = 1 );
	void zoom( LONG times = 1 );
	void clear();

	COLORREF red = RGB( 255, 0, 0 );
	COLORREF blue = RGB( 0, 0, 255 );
protected:
	void OnDestroy();
	void Invalidate();
	void PaintObject();

private:
	HWND handle;
	int x = 25, y = 25;
	int rx = 75, ry = 25;
	int size = 25;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};