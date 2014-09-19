#include "WinPlotterWindow.h"

PWCHAR CWinPlotterWindow::windowClassName = L"WinPlotterWindow";

LRESULT CALLBACK CWinPlotterWindow::windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {

	// Получаем доступ к экземпляру окна внутри главного цикла
	CWinPlotterWindow* window = NULL;
	if (message == WM_CREATE) {

		CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<CWinPlotterWindow*>(createStruct->lpCreateParams);
		SetWindowLong(handle, GWL_USERDATA, reinterpret_cast<LONG>(window));
		window->windowHandle = handle;

		// Инициализация
		window->onCreate();
	}
	else
	{
		window = reinterpret_cast<CWinPlotterWindow*>(GetWindowLong(handle, GWL_USERDATA));
	}

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		// Перерисовываем окно
		window->onPaint();
		return 0;
	default:
		return DefWindowProc(handle, message, wParam, lParam);
	}

	return 0;
}

CWinPlotterWindow::CWinPlotterWindow():
	windowHandle(NULL), drawer(NULL)
{
}


CWinPlotterWindow::~CWinPlotterWindow()
{
	delete drawer;
}

bool CWinPlotterWindow::RegisterWindowClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = CWinPlotterWindow::windowProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(0);
	// wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CWinPlotterWindow::windowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		return false;
	}
	else {
		return true;
	}
}

bool CWinPlotterWindow::Create()
{
	windowHandle = CreateWindowEx(
		NULL,
		CWinPlotterWindow::windowClassName,
		L"WinPlotter",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 300,
		NULL,
		NULL,
		GetModuleHandle(0),
		this
	);

	return windowHandle != NULL;
}

void CWinPlotterWindow::Show(int nCmdShow) {
	ShowWindow(windowHandle, nCmdShow);
	UpdateWindow(windowHandle);
}

int CWinPlotterWindow::GetDrawingWidth() {
	RECT clientRectangle;
	GetClientRect(windowHandle, &clientRectangle);
	return clientRectangle.right - clientRectangle.left;
}

int CWinPlotterWindow::GetDrawingHeight() {
	RECT clientRectangle;
	GetClientRect(windowHandle, &clientRectangle);
	return clientRectangle.bottom - clientRectangle.top;
}

HWND CWinPlotterWindow::GetHandle() {
	return windowHandle;
}

void CWinPlotterWindow::onCreate() {
	drawer = new CEngineDrawer(windowHandle);
}

void CWinPlotterWindow::onPaint() {
	int width = GetDrawingWidth();
	int height = GetDrawingHeight();

	drawer->StartDraw();

	drawer->DrawLine(10, 10, width - 10, height - 10, RGB(255, 0, 0));
	drawer->DrawLine(width - 10, 10, 10, height - 10, RGB(255, 255, 0));

	drawer->FinishDraw();
}