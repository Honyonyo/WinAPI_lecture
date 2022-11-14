#include "stdafx.h"

//Utility
//  ㄴMath


#pragma region 윈도우API
/*
* API (Application Programming Interface)
    (//게임 시장점유율이 win>>>>>>>>>mac이라서.. winAPI위주로 겅부하는게 시장성 높음음)

    ★- 운영체제가 응용프로그램 개발을 위해 제공하는 서브루틴 또는 함수의 집합

    - 명령어의 집합으로 어플리케이션 프로그램에서 오퍼레이팅 시스템의 기본적인 기능을 사용할 필요가 있을 경우 API에서 명령어 호출이 진행된다.

    하드웨어---------------운영체제(win)-------------응용프로그램
    (API함수)              ...            
    ★▶ 장 점
    - 운영체제가 같으면 같은 기능의 집합을 사용하기에 확장성 및 연동성, 그리고 유지보수가 편리함.
    - 윈도우즈 != 리눅스 
    - 윈도우즈에서 지원하는 다양한 라이브러리 지원 가능
        커스텀 추가 라이브러리를 추가해서 단일플랫폼으로 쓰지 않고 부족한점 보완하고 필요에 따라 다양한 기능을 추가하는거야!

    ★▶ 단 점
    - 플랫폼 고착화 (오래 전 C로 만들어져서 최신 하드에는 맞지 않을 수 있다. (gpu 등등))
        └라이브러리 가져와서 사용하면 해결 빠밤!┘
    
    ▶ API구조
    ★- 크게 진입점, ★메세지 루프, ★Window Procedure로 나뉜다.
        프로시저에서 메세지를 발생시키고,
        반복문을 통해 전달해준다.
        실행 > 인스턴스 > 진입점 > 확인(컴파일러가 작업) > 프로시저 메세지 반복문 메세지루프로 전달, 메세지 get인지 pick?인지에 따라 윈도우즈로 전달하거나 계속소통하거나
            cpu클럭에 넣기       창 띄우기 위한 세팅     프로시저에 작성된 문을 메세지 형태로 읽어들인다

*/
#pragma region

HINSTANCE _hInstance;                                // 현재 인스턴스입니다.
HWND _hWnd;                                         //윈도우핸들 : 윈도우 창
POINT _ptMouse = { 0,0 };

// # 함수 전방선언 #


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

RECT _rc1, _rc2;

//메 인 함 수! 듀듕 
int APIENTRY WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpszCmdParam,
                    int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    //메모리
    wndClass.cbClsExtra = 0;                                                    //클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                    //윈도우 여분 메모리
    //화면
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               //백그라운드. 페이드 인아웃이 들어갈 수 있도록 여지를 준 get stock object
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             //마우스커서. 아이콘 이미지 기본화살표 그냥 쓸꺼양
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //아이콘. 안쓸건데, 기본지원으로 그냥 세팅해둬.
    //윈도우 정보, 속성
    wndClass.hInstance = hInstance;                                             //윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    //윈도우 프로시져(현재 프로젝트에서 사용할)
    wndClass.lpszClassName = WIN_NAME;                                        //클래스 이름 (윈도우 클래스 식별자 정보)
    
    wndClass.lpszMenuName = NULL;                                               //메뉴 이름. 지금 안쓸꺼야~
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   //윈도우 스타일 (윈도우 다시그리기 정보)

    //1-2. 윈도우 클래스 등록
    RegisterClass(&wndClass);

    //1-3. 화면에 보여줄 윈도우 창 생성
    _hWnd = CreateWindow    //사용하는 일이 많으므로 친구하자^^
    (
        WIN_NAME,     //윈도우 클래스 식별자
        WIN_NAME,     //윈도우 타이틀 바 이름
        WINSTYLE,    //윈도우 스타일
        WINSTART_X,            //윈도우 화면 X좌표. 내가 만든 창이 뜨는 모니터 화면 위치
        WINSTART_Y,            //윈도우 화면 Y좌표. 내가 만든 창이 뜨는 모니터 화면 위치
        WINSIZE_X,            //윈도우 화면 가로크기
        WINSIZE_Y,            //윈도우 화면 세로크기
        NULL,//부모 윈도우 지정 여부 (없으면 NULL, 그치만안정성높은건 GetDesktopWindow())
        (HMENU)NULL,    //메뉴 핸들
        hInstance,      //인스턴스 지정
        NULL            //윈도우의 자식 윈도우를 생성하면 지정하고 아니라면 NULL_아마 메세지창..?경고창/
                            //필요에 의해서 사용. 지금은 null
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    //1-4. 화면에 윈도우 창 보여주기
    ShowWindow(_hWnd, nCmdShow);


    MSG message;
/*
게임용~
    while (true) {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT)break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
*/

    while (GetMessage(&message, 0, 0, 0))
    {
            TranslateMessage(&message);
            DispatchMessage(&message);
    }

    return (int)message.wParam;
}

char strPT[400];


LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wparam, LPARAM lparam) {
    HDC hdc;        //핸들dc_ GDI안에있는데. png는 안되고 bmp만 받아줌. GDI+를사용하면 PNG를 사용할 수 있다.
    PAINTSTRUCT ps; //페인트구조체
    RECT rc;

    switch (imsg) {
    case WM_CREATE:
        hdc = BeginPaint(hwnd, &ps);
        _rc1 = RectMakeCenter(WINSIZE_X/2, WINSIZE_Y/2, 100,100);
        _rc2 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 400, 100);


        EndPaint(hwnd, &ps);
        break;

    case WM_PAINT:          //출력에 관한 모든 것을 담당한다(문자,그림,도형 등등 화면에 보이는 모든 것)
        hdc = BeginPaint(hwnd, &ps);
        DrawRectMake(hdc, _rc1);
        wsprintf(strPT, "(%-10d, %-10d)", _ptMouse.x, _ptMouse.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        //이곳에 출력에 관한 코딩을 하면 된다.

        //문자출력
        //TextOut(hdc,x,y,문자열, 문자열길이)
        //strlen는 할당받은 메모리에 바인딩된 문자열에서 NULL을 제외한 문자열 길이를 반환해줌

        SetTextColor(hdc, RGB(255, 0, 0));

        MoveToEx(hdc, 400, 400, NULL);  //동작시작점
        LineTo(hdc, 200, 400);  //동작끝점

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 200);

        EndPaint(hwnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lparam);
        _ptMouse.y = LOWORD(lparam);
        InvalidateRect(hwnd, NULL, false);

    case WM_LBUTTONDOWN:    //좌클릭발생
        break;
        
    case WM_RBUTTONDOWN:    //우클릭 발생 

        break;

    case WM_KEYDOWN:    //키눌린상황에서 발생
        switch (wparam) {
        case VK_LEFT:
        hdc=GetDC(hwnd);
            SetTextColor(hdc, RGB(0, 0, 255));
            
        ReleaseDC(hwnd, hdc);
            break;
        case VK_RIGHT:

            //지오메트리 대시
            break;
        case VK_ESCAPE:
            PostMessage(hwnd, WM_DESTROY, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hwnd, imsg, wparam, lparam));
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width, height };
    //실제 윈도우 크기 조정
    //AdjustWindowRect(대상 객체, 사용할윈도우스타일, 메뉴 여부)
    AdjustWindowRect(&rc, WINSTYLE, false);

    //얻어온 렉트정보로 윈도우 사이즈 셋팅
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        (SWP_NOZORDER | SWP_NOMOVE));
}
//zorder 겹쳐있는 뒤에거를 어떻게 처리할지
