#include "stdafx.h"
#include "MainGame.h"

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

HINSTANCE _hinstance;                               // ���� �ν��Ͻ��Դϴ�.
HWND _hWnd;                                         //�������ڵ� : ������ â
POINT _ptMouse = { 0,0 };
MainGame* _mg;

// # �Լ� ���漱�� #


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

RECT _rc1, _rc2;

int centerX;
int centerY;

//�� �� �� ��! ��� 
int APIENTRY WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpszCmdParam,
                    int       nCmdShow)
{
    _mg = new MainGame;
    _hinstance = hInstance;

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

    //���ΰ��� Ŭ���� �ʱ�ȭ ���н� ����
    if(FAILED(_mg->init()))
    {
        return 0;
    }
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

    _mg->release();
    //������ Ŭ���� ��� ����
    UnregisterClass(WIN_NAME, hInstance);

    return (int)message.wParam;
}

char strPT[400];


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

    return _mg->MainProc(hWnd, iMsg, wParam, lParam);
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
