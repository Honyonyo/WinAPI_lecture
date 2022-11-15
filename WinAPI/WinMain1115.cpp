#include "stdafx.h"
#include "RandomPolygon.h"
HINSTANCE _hinstance;
HWND _hWnd;
LPSTR lpszClass = TEXT("�ٰ��� �׸�����");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
/*
[READE ME]
���۹�
: ��Ŭ���� �ϸ� ����1�� �ش��ϴ� ���� ������ ��µ˴ϴ�.
  ��Ŭ���� �ϸ� ����2�� �ش��ϴ� �ι��׸��� ��µ˴ϴ�.
  �����̽��ٸ� ������ ȭ���� �Ͼ�� �������ϴ�.
  ESC�� ������ ����˴ϴ�.

====================================================

����1.
���׶��, �׸�, ���� �� 3������ ������ ����մϴ�.
Ŭ���� ������ ���콺��ǥ�� �߽����� ������ �����ؼ� ����մϴ�.
�ﰢ���� ���, ���� ������ �ﰢ���� ������ ��,
�ﰢ���� �����߽��� ���콺������ ��ġ�� �Ű���ϴ�.
�ű�鼭 ȭ�� �ٱ����� �������� ���� ȭ�� ������ �Ű��־����ϴ�.
Ȥ�ö� �� ���� ������ ��ġ�� ��츦 �����
������ ������� ���, ������ ���� ���� ������ �� �� ��ǥ�� ���Ӱ� ����� �ڵ带

*/
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	_hinstance = hinstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wndClass.hInstance = hinstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		lpszClass, lpszClass, WINSTYLE,
		WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y,
		NULL, (HMENU)NULL, hinstance, NULL
	);

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	ShowWindow(_hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	POINT _ptMouse;
	RndPoly rolypoly;



	switch (iMsg) {
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_LBUTTONDOWN:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, false);
		hdc = GetDC(hWnd);
		rolypoly.draw(hdc,_ptMouse);				
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:

			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}

void setWindowSize(int x, int y, int width, int height) {
	RECT rc = { 0,0,width,height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		(SWP_NOZORDER | SWP_NOMOVE));
}