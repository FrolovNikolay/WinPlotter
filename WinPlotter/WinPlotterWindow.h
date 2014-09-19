#pragma once
#include "Windows.h"
#include "EngineDrawer.h"

// Класс, отвечающий за создание и управление главным (и единственным окном) приложения
class CWinPlotterWindow
{
public:
	CWinPlotterWindow();
	~CWinPlotterWindow();

	// Регистрация класса окна. Возвращает true, если класс окна успешно зарегистрирован в ОС, false в противном случае
	bool RegisterWindowClass();

	// Создание экземпляра окна. Возвращает true, если окно успешно создано, иначе false.
	bool Create();

	// Отображает окно
	void Show(int nCmdShow);

	// Возвращает ширину и высоту области для рисования графика в пикселах
	int GetDrawingWidth();
	int GetDrawingHeight();

	// Возвращает дескриптор окна
	HWND GetHandle();

private:
	// Дескриптор окна в системе
	HWND windowHandle;

	// Указатель на часть движка, который будет отрисовывать фигуры
	CEngineDrawer* drawer; 

	// Обработчик событий для приложения
	static LRESULT CALLBACK windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	// Название класса окна
	static PWCHAR windowClassName;

	// Обработчик событий
	void onCreate(); // Что будет происходить сразу после успешного создания окна 
	void onPaint(); // ...при перерисовке окна
};

