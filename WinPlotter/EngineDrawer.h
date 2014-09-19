#pragma once
#include "Windows.h"

/*
* Класс, облегающий рисование объектов и прочих фигур в окне приложения
*/
class CEngineDrawer
{
public:
	CEngineDrawer(HWND windowHandle);
	~CEngineDrawer();

	// Запускает цикл отрисовки (вызывает внутри GetDC)
	bool StartDraw();

	// Заканчивает цикл отрисовки (вызывает внутри ReleaseDC)
	void FinishDraw();

	// Рисует точку заданным цветом
	void DrawPoint(int x, int y, COLORREF color);

	// Рисует отрезок заданным цветом между двумя точками
	void DrawLine(int xStart, int yStart, int xFinish, int yFinish, COLORREF color);

	// Заполняет всю клиентскую область краской
	// void FillWithColor(COLORREF color);
	

private:
	bool isRunning;
	HDC hdc;
	HWND windowHandle;

	
};

