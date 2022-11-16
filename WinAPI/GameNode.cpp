#include "stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void) {
	//Ÿ�̸� �ʱ�ȭ
	//SetTimer() ������ �ֱ⸶�� ������ �Լ��� �����Ű�� �Լ�
	SetTimer(_hWnd, 1, 10, NULL);
    //Ű�Ŵ��� �ʱ�ȭ
    KEYMANAGER->init();
    RND->init();

		return S_OK;
		//�Լ��� ���������� ��������� �˸���
		//Success_OK
}

void GameNode::release(void)
{
    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
	KillTimer(_hWnd, 1);
	//Ÿ�̸Ӵ� ��� �޸𸮸� �����Ƿ�, ����� �ݵ�� �����ؾ��Ѵ�.
}

void GameNode::update(void) {
	//���۸�ó���� ���� Ÿ�̸Ӱ� ���⶧���� �⺻�Լ� ���

	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::render(HDC hdc) {
	//��ӹ����ʿ��� �׷��ִ°�..!
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;        //�ڵ�dc_ GDI�ȿ��ִµ�. png�� �ȵǰ� bmp�� �޾���. GDI+������ϸ� PNG�� ����� �� �ִ�.
    PAINTSTRUCT ps; //����Ʈ����ü
    POINT polyline[3] = { {60,50}, {50,40},{110,20} };
    switch (iMsg) {
    case WM_TIMER:
        this->update();
        break;

    case WM_PAINT:          //��¿� ���� ��� ���� ����Ѵ�(����,�׸�,���� ��� ȭ�鿡 ���̴� ��� ��)
        hdc = BeginPaint(hWnd, &ps);
        this->render(hdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:    //��Ŭ���߻�
        break;

    case WM_LBUTTONUP:
        break;

    case WM_RBUTTONDOWN:    //��Ŭ�� �߻� 

        break;

    case WM_KEYDOWN:    //Ű������Ȳ���� �߻�
        switch (wParam) {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMsg, wParam, lParam));

}
