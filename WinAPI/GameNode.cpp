#include "stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void) {
	//타이머 초기화
	//SetTimer() 일정한 주기마다 정해진 함수를 실행시키는 함수
	SetTimer(_hWnd, 1, 10, NULL);
    //키매니저 초기화
    KEYMANAGER->init();
    RND->init();

		return S_OK;
		//함수가 성공적으로 실행됐음을 알리기
		//Success_OK
}

void GameNode::release(void)
{
    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
	KillTimer(_hWnd, 1);
	//타이머는 계속 메모리를 먹으므로, 사용후 반드시 삭제해야한다.
}

void GameNode::update(void) {
	//버퍼링처리와 고성능 타이머가 없기때문에 기본함수 사용

	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::render(HDC hdc) {
	//상속받은쪽에서 그려주는거..!
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;        //핸들dc_ GDI안에있는데. png는 안되고 bmp만 받아줌. GDI+를사용하면 PNG를 사용할 수 있다.
    PAINTSTRUCT ps; //페인트구조체
    POINT polyline[3] = { {60,50}, {50,40},{110,20} };
    switch (iMsg) {
    case WM_TIMER:
        this->update();
        break;

    case WM_PAINT:          //출력에 관한 모든 것을 담당한다(문자,그림,도형 등등 화면에 보이는 모든 것)
        hdc = BeginPaint(hWnd, &ps);
        this->render(hdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:    //좌클릭발생
        break;

    case WM_LBUTTONUP:
        break;

    case WM_RBUTTONDOWN:    //우클릭 발생 

        break;

    case WM_KEYDOWN:    //키눌린상황에서 발생
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
