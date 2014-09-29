#include <windows.h>
#include "CWinMain.h"
#include "CWinPlotter.h"
#include "resource.h"

int __stdcall wWinMain( HINSTANCE hInstance, HINSTANCE previnstance, LPWSTR commandLine, int nCmdShow ) {
	CWinMain::registerClass(hInstance);
	CWinPlotter::registerClass(hInstance);
	CWinMain window;

	HWND hWnd = window.create( hInstance );

	if( hWnd == 0 ) {
		MessageBox( 0, L"WTF", L"WTF", MB_OK );
		return -1;
	}
	window.show( nCmdShow );

	MSG msg;
	while( ::GetMessage( &msg, 0, 0, 0 ) ) {
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}

	return 0;
}