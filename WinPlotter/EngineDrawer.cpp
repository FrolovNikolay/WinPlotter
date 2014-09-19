#include "EngineDrawer.h"


CEngineDrawer::CEngineDrawer(HWND windowHandle):
hdc(NULL), isRunning(false)
{
	this->windowHandle = windowHandle;
}


CEngineDrawer::~CEngineDrawer()
{
}

bool CEngineDrawer::StartDraw() {
	hdc = GetDC(windowHandle);
	if (hdc) {
		isRunning = true;
		return true;
	}
	else {
		return false;
	}
}

void CEngineDrawer::FinishDraw() {
	isRunning = false;
	ReleaseDC(windowHandle, hdc);
}

void CEngineDrawer::DrawPoint(int x, int y, COLORREF color) {
	if (isRunning) {
		SetPixel(hdc, x, y, color);
	}
}

void CEngineDrawer::DrawLine(int xStart, int yStart, int xFinish, int yFinish, COLORREF color) {
	if (isRunning) {
		// Создаём перо для отрисовки и выбираем его в контексте
		HPEN linePen = CreatePen(PS_SOLID, 1, color);
		SelectObject(hdc, linePen);

		// Перемещаем внутренний курсор на начало и рисует до конечной точки
		MoveToEx(hdc, xStart, yStart, NULL);
		LineTo(hdc, xFinish, yFinish);

		// Удаляем перо
		DeleteObject(linePen);
	}
}