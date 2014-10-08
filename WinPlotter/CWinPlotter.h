#pragma once
#include "Windows.h"
#include "EngineCamera.h"
#include "Model.h"

class CWinPlotter {
public:
	CWinPlotter() {};
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
	void OnCreate();
	void OnDestroy();
	void OnSize();
	void Invalidate();
	void PaintObject();

	// Обновляет размеры проекции для движка
	void UpdateScreenSize();

private:
	HWND handle;
	int x = 25, y = 25;
	int rx = 75, ry = 25;
	int size = 25;

	// Экземпляр движка, который будет заниматься рендером объекта
	CEngineCamera engine; 

	// TODO: заменить заглушку на реальный объект
	// Трёхмерный примитив, который будет рисоваться на экране
	C3DModel testObject;

	// Структура двухмерного объекта, который будет непосредственно переводиться в вызовы WinAPI
	C2DModel renderedObject;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};