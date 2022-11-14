#include "stdafx.h"

//Utility
//  ��Math


#pragma region ������API
/*
* API (Application Programming Interface)
    (//���� ������������ win>>>>>>>>>mac�̶�.. winAPI���ַ� �Ϻ��ϴ°� ���强 ������)

    ��- �ü���� �������α׷� ������ ���� �����ϴ� �����ƾ �Ǵ� �Լ��� ����

    - ��ɾ��� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ���� ��� API���� ��ɾ� ȣ���� ����ȴ�.

    �ϵ����---------------�ü��(win)-------------�������α׷�
    (API�Լ�)              ...            
    �ڢ� �� ��
    - �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������, �׸��� ���������� ����.
    - �������� != ������ 
    - ��������� �����ϴ� �پ��� ���̺귯�� ���� ����
        Ŀ���� �߰� ���̺귯���� �߰��ؼ� �����÷������� ���� �ʰ� �������� �����ϰ� �ʿ信 ���� �پ��� ����� �߰��ϴ°ž�!

    �ڢ� �� ��
    - �÷��� ����ȭ (���� �� C�� ��������� �ֽ� �ϵ忡�� ���� ���� �� �ִ�. (gpu ���))
        �����̺귯�� �����ͼ� ����ϸ� �ذ� ����!��
    
    �� API����
    ��- ũ�� ������, �ڸ޼��� ����, ��Window Procedure�� ������.
        ���ν������� �޼����� �߻���Ű��,
        �ݺ����� ���� �������ش�.
        ���� > �ν��Ͻ� > ������ > Ȯ��(�����Ϸ��� �۾�) > ���ν��� �޼��� �ݺ��� �޼��������� ����, �޼��� get���� pick?������ ���� ��������� �����ϰų� ��Ӽ����ϰų�
            cpuŬ���� �ֱ�       â ���� ���� ����     ���ν����� �ۼ��� ���� �޼��� ���·� �о���δ�

*/
#pragma region

HINSTANCE _hInstance;                                // ���� �ν��Ͻ��Դϴ�.
HWND _hWnd;                                         //�������ڵ� : ������ â
POINT _ptMouse = { 0,0 };

// # �Լ� ���漱�� #


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

RECT _rc1, _rc2;

//�� �� �� ��! ��� 
int APIENTRY WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpszCmdParam,
                    int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    //�޸�
    wndClass.cbClsExtra = 0;                                                    //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                                    //������ ���� �޸�
    //ȭ��
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               //��׶���. ���̵� �ξƿ��� �� �� �ֵ��� ������ �� get stock object
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             //���콺Ŀ��. ������ �̹��� �⺻ȭ��ǥ �׳� ������
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           //������. �Ⱦ��ǵ�, �⺻�������� �׳� �����ص�.
    //������ ����, �Ӽ�
    wndClass.hInstance = hInstance;                                             //�����츦 �ҿ��� ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    //������ ���ν���(���� ������Ʈ���� �����)
    wndClass.lpszClassName = WIN_NAME;                                        //Ŭ���� �̸� (������ Ŭ���� �ĺ��� ����)
    
    wndClass.lpszMenuName = NULL;                                               //�޴� �̸�. ���� �Ⱦ�����~
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   //������ ��Ÿ�� (������ �ٽñ׸��� ����)

    //1-2. ������ Ŭ���� ���
    RegisterClass(&wndClass);

    //1-3. ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow    //����ϴ� ���� �����Ƿ� ģ������^^
    (
        WIN_NAME,     //������ Ŭ���� �ĺ���
        WIN_NAME,     //������ Ÿ��Ʋ �� �̸�
        WINSTYLE,    //������ ��Ÿ��
        WINSTART_X,            //������ ȭ�� X��ǥ. ���� ���� â�� �ߴ� ����� ȭ�� ��ġ
        WINSTART_Y,            //������ ȭ�� Y��ǥ. ���� ���� â�� �ߴ� ����� ȭ�� ��ġ
        WINSIZE_X,            //������ ȭ�� ����ũ��
        WINSIZE_Y,            //������ ȭ�� ����ũ��
        NULL,//�θ� ������ ���� ���� (������ NULL, ��ġ�������������� GetDesktopWindow())
        (HMENU)NULL,    //�޴� �ڵ�
        hInstance,      //�ν��Ͻ� ����
        NULL            //�������� �ڽ� �����츦 �����ϸ� �����ϰ� �ƴ϶�� NULL_�Ƹ� �޼���â..?���â/
                            //�ʿ信 ���ؼ� ���. ������ null
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    //1-4. ȭ�鿡 ������ â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);


    MSG message;
/*
���ӿ�~
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
    HDC hdc;        //�ڵ�dc_ GDI�ȿ��ִµ�. png�� �ȵǰ� bmp�� �޾���. GDI+������ϸ� PNG�� ����� �� �ִ�.
    PAINTSTRUCT ps; //����Ʈ����ü
    RECT rc;

    switch (imsg) {
    case WM_CREATE:
        hdc = BeginPaint(hwnd, &ps);
        _rc1 = RectMakeCenter(WINSIZE_X/2, WINSIZE_Y/2, 100,100);
        _rc2 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 400, 100);


        EndPaint(hwnd, &ps);
        break;

    case WM_PAINT:          //��¿� ���� ��� ���� ����Ѵ�(����,�׸�,���� ��� ȭ�鿡 ���̴� ��� ��)
        hdc = BeginPaint(hwnd, &ps);
        DrawRectMake(hdc, _rc1);
        wsprintf(strPT, "(%-10d, %-10d)", _ptMouse.x, _ptMouse.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        //�̰��� ��¿� ���� �ڵ��� �ϸ� �ȴ�.

        //�������
        //TextOut(hdc,x,y,���ڿ�, ���ڿ�����)
        //strlen�� �Ҵ���� �޸𸮿� ���ε��� ���ڿ����� NULL�� ������ ���ڿ� ���̸� ��ȯ����

        SetTextColor(hdc, RGB(255, 0, 0));

        MoveToEx(hdc, 400, 400, NULL);  //���۽�����
        LineTo(hdc, 200, 400);  //���۳���

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 200);

        EndPaint(hwnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lparam);
        _ptMouse.y = LOWORD(lparam);
        InvalidateRect(hwnd, NULL, false);

    case WM_LBUTTONDOWN:    //��Ŭ���߻�
        break;
        
    case WM_RBUTTONDOWN:    //��Ŭ�� �߻� 

        break;

    case WM_KEYDOWN:    //Ű������Ȳ���� �߻�
        switch (wparam) {
        case VK_LEFT:
        hdc=GetDC(hwnd);
            SetTextColor(hdc, RGB(0, 0, 255));
            
        ReleaseDC(hwnd, hdc);
            break;
        case VK_RIGHT:

            //������Ʈ�� ���
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
    //���� ������ ũ�� ����
    //AdjustWindowRect(��� ��ü, ����������콺Ÿ��, �޴� ����)
    AdjustWindowRect(&rc, WINSTYLE, false);

    //���� ��Ʈ������ ������ ������ ����
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        (SWP_NOZORDER | SWP_NOMOVE));
}
//zorder �����ִ� �ڿ��Ÿ� ��� ó������
