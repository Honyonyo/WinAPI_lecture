#include "stdafx.h"
#include "Rect_.h"
//�̿ϼ�����. �̻���!
HINSTANCE _hInstance;                      
HWND _hWnd;                                        
POINT _ptMouse = { 0,0 };
short _mouseMoveX;
short _mouseMoveY;
Rect_ rc1_;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

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

char strPT[100];
short count=0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wparam, LPARAM lparam) {
    HDC hdc;        //�ڵ�dc_ GDI�ȿ��ִµ�. png�� �ȵǰ� bmp�� �޾���. GDI+������ϸ� PNG�� ����� �� �ִ�.
    PAINTSTRUCT ps; //����Ʈ����ü

    switch (imsg) {
    case WM_CREATE:
        hdc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        break;

    case WM_PAINT:         
        hdc = BeginPaint(hwnd, &ps);
        wsprintf(strPT, "(%-10d, %-10d)", _ptMouse.x, _ptMouse.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        rc1_.draw(hdc);

        EndPaint(hwnd, &ps);
        break;

    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lparam);
        _ptMouse.y = HIWORD(lparam);
        wsprintf(strPT, "(%-10d, %-10d) %d", _ptMouse.x, _ptMouse.y);
        hdc = GetDC(hwnd);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        rc1_.draw(hdc);
        break;

    case WM_LBUTTONDOWN:    //��Ŭ���߻�        
        //rc1_.click(_ptMouse,hdc);
        InvalidateRect(hwnd, NULL, true);
        hdc = BeginPaint(hwnd, &ps);
        rc1_.drag(_ptMouse, hdc);
        //wsprintf(strPT, "(%-10d, %-10d) %d", rc1_.getPoint().x, rc1_.getPoint().y, count++);
        //TextOut(hdc, 10, 40, strPT, strlen(strPT));
        //rc1_.draw(hdc);

        rc1_.draw(hdc);
        wsprintf(strPT, "(%-10d, %-10d) %d", rc1_.getPoint().x, rc1_.getPoint().y, rc1_.getClicked());
        TextOut(hdc, 10, 40, strPT, strlen(strPT));

        EndPaint(hwnd, &ps); 
        break;

    case WM_LBUTTONUP:
        rc1_.drop();
        break;

    case WM_RBUTTONDOWN:    //��Ŭ�� �߻� 

        break;

    case WM_KEYDOWN:    //Ű������Ȳ���� �߻�
        switch (wparam) {
        case VK_LEFT:
            hdc = GetDC(hwnd);
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
