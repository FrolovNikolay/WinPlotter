#include "CWinPlotter.h"
#include <Windows.h>
#include "resource.h"

LRESULT __stdcall CWinPlotter::windowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg == WM_NCCREATE ) {
		SetWindowLong( hWnd, GWL_USERDATA, reinterpret_cast< LONG >( ( reinterpret_cast< CREATESTRUCT* >( lParam ) )->lpCreateParams ) );
	}
	CWinPlotter* wnd = reinterpret_cast< CWinPlotter* >( GetWindowLong( hWnd, GWL_USERDATA ) );
	switch( uMsg ) {
		case WM_SIZE:
			wnd->Invalidate();
			return 0;
		case WM_PAINT:
			wnd->PaintObject();
			return 0;
		case WM_DESTROY:
			wnd->OnDestroy();
			break;
	}
	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

bool CWinPlotter::registerClass( HINSTANCE hInstance )
{
	WNDCLASSEX windowClass;
	::ZeroMemory( &windowClass, sizeof( WNDCLASSEX ) );
	windowClass.cbSize = sizeof( WNDCLASSEX );
	windowClass.style = CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = CWinPlotter::windowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"CWinPlotter";

	ATOM res = ::RegisterClassEx( &windowClass );
	return ( res != 0 );
}

HWND CWinPlotter::create( HINSTANCE hInstance, HWND parent )
{
	handle = ::CreateWindowEx( 0, L"CWinPlotter", L"CWinPlotter", WS_CHILD | WS_BORDER | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, 200, 200, parent, 0, hInstance, this );
	RECT rect;
	GetClientRect( handle, &rect );
	return handle;
}

void CWinPlotter::show(int cmdShow)
{
	::ShowWindow( handle, cmdShow );
}

void CWinPlotter::OnDestroy()
{
	::PostQuitMessage( 0 );
}

void CWinPlotter::PaintObject()
{
	RECT rect;
	GetClientRect( handle, &rect );
	PAINTSTRUCT paintStruct;

	HDC currentDC = BeginPaint( handle, &paintStruct );

	HBITMAP currentBitmap;

	currentBitmap = CreateCompatibleBitmap( currentDC, rect.right - rect.left, rect.bottom - rect.top );
	PatBlt( currentDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, BLACKNESS );

	HBRUSH redBrush = ::CreateSolidBrush( red );
	HBRUSH blueBrush = ::CreateSolidBrush( blue );

	HBRUSH currentBrush = ( HBRUSH )::SelectObject( currentDC, redBrush );
	::Ellipse( currentDC, x - size, y - size, x + size, y + size );
	SelectObject( currentDC, currentBrush );
	DeleteObject( redBrush );

	currentBrush = ( HBRUSH )::SelectObject( currentDC, blueBrush );
	::Ellipse( currentDC, rx - 25, ry - 25, rx + 25, ry + 25 );
	SelectObject( currentDC, currentBrush );
	DeleteObject( blueBrush );

	DeleteObject( currentBitmap );
	DeleteDC( currentDC );

	EndPaint( handle, &paintStruct );
}

void CWinPlotter::Invalidate()
{
	RECT rect;
	GetClientRect( handle, &rect );
	InvalidateRect( handle, &rect, true );
}

void CWinPlotter::moveX( LONG times )
{
	x += times;
	Invalidate();
}

void CWinPlotter::moveY( LONG times )
{
	y += times;
	Invalidate();
}

void CWinPlotter::rotateX( LONG times )
{
	rx += times;
	Invalidate();
}

void CWinPlotter::rotateY( LONG times )
{
	ry += times;
	Invalidate();
}

void CWinPlotter::zoom( LONG times )
{
	size += times;
	Invalidate();
}

void CWinPlotter::clear()
{
	red = RGB( 0, 0, 0 );
	blue = RGB( 0, 0, 0 );
	Invalidate();
}