#include "WinPlotterWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CWinPlotterWindow mainWindow;

	if (!mainWindow.RegisterWindowClass()) {
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна WinPlotterWindow!", L"Ошибка", MB_OK);
		return 1;
	}

	if (!mainWindow.Create()) {
		MessageBox(NULL, L"Не удалось зарегистрировать класс окна WinPlotterWindow!", L"Ошибка", MB_OK);
		return 1;
	}

	mainWindow.Show(nCmdShow);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}