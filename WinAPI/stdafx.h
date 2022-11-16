#pragma once
//PreCompiledHeader PCH

//4005 : DXGI�� �׷��� �������̽����� ��ũ�� �����Ͽ� ���� ��µǴ� ���
//������Ʈ �Ӽ� ��޿��� ���� ����
#pragma warning(disable : 4005)

//���α׷����� ������ OS�� ���� Windows����̼� �ڵ忡 ���Ե� �Լ�, ������� �����ϴµ� ����� �ȴ�.
#include <SDKDDKVer.h>

//���� ������� �ʴ� ������ Windows������� ����
#define WIN32_LEAN_AND_MEAN
//GDI+�� ����Ϸ��� ������� �����;��Ѵ�.
//<ole2.h>

//!Windows�������
#include <Windows.h>

//!C ��Ÿ�� �������
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>	//�޸������Լ�
#include <tchar.h>	//���ڼ��� �������ִ� �ڷ�޸�
#include <time.h>

/*
MBCS(Multi Byte Character Set)
	��Ƽ����Ʈ
	: ������ ����ϴ� ���ڿ�.
	  �ƽ�Ű�ڵ忡 ���ԵǴ� ���ڴ� 1����Ʈ,
	  ���Ե��� �ʴ� ���ڴ� 2����Ʈ�� �����Ѵ�.

WBCS(Wide Byte Character Set)
	�����ڵ�
	: ��� ���ڸ� 2����Ʈ�� ó���Ѵ�.

VS������ ����ǥ��
	MBCS/WBCS�� ������� ����� ������ ���������Ѵ�.
	��Ƽ����Ʈ : ���ڿ��� ""�� ���Ѵ�.
	�����ڵ� : ���ڿ��� ""�� ���ΰ� L�� ���δ�.

	�����ڵ�<->��Ƽ����Ʈ �̽��� ���ؼ��� ���ڿ� ǥ������� �� ����������ϱ� ������
	�߰���ũ������ _T�� ����Ѵ�.


*/

//!C++��Ÿ�� �������
#include <iostream>
/*
c++ 11���� �߰��� �ð� ���� ���̺귯��
���� c��Ÿ�ӿ��� �����ϴ� time�Լ����� �� �پ��ϰ� Ȯ��� ��� ����
(tiome �ʾ���
os�� ���������� ����
*/
#include <chrono>
#include <random>	//�޸���Ʈ������ ����
#include <vector>	//�����迭
#include <map>		//�����Ʈ���� ������� Ű�� ����� ������ �ڷ���
/*
unordered_map : Hash�ڷᱸ��
�ߺ��� �����͸� ������� �ʴ´�.
�� ���� �����Ͱ� ������ (key)�ؽ��浹�� �߼��� ��������
*/

#include <unordered_map>	//
#include <string>	//���ڿ� ���̺귯��
//bitset : ��Ʈ������ �� �� ���� �������ִ� �Լ��� �����Ѵ�. (STL)
//	�� reset(), set() flip(), all(), any(), size()����� ��Ʈ���꿡 ���� �����ϰ��ִ�.
#include <bitset>	//������ namespace std; �ϸ� ���� �տ� std�װűװ��ϴϱ�... 

using std::vector;
using std::bitset;

//#include <cassert>	//���� �������ּ���


/*
//! D2D, D3D �������
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>		//3d11������ ���̴� �Ƚᵵ �����
#include <dinput.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dinput8.lib")	//�Է°���
#pragma comment(lib,"dxguid.lib")	//���̺귯����ũ

//png������ ������ d2d���丮�� �߰��ؼ� �߸ŷ� ����ϱ� �԰���
ID2D1Factory*			_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*	_ID2DRenderTarget = nullptr;
*/



/*����� ���� �������*/
//��ȣ���԰���� �Ŵ��ϰ� �����ֱ� ������ ����ٰ� include �� �� ���̴��� comm~�� windows.h�� include�ȰͰ� ���� ȿ���� ��
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

// # �� �� �� #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()

// # ��ũ�� # ������ â �ʱ�ȭ
#define WIN_NAME	(LPSTR)(TEXT("WindowsAPI"))
#define WINSTART_X	400
#define WINSTART_Y	100
#define WINSIZE_X	800
#define WINSIZE_Y	800
// WS_CAPTION Ÿ��Ʋ�ٸ� ������ ���� �ɼ�
// WS_SYSMENU ����ǥ���ٿ� ��Ʈ�Ѹ޴�����â�� ����� �ɼ�( _ �� X )

#define WINSTYLE	WS_CAPTION | WS_SYSMENU

// # ��ũ�� �Լ� #
#define SAFE_DELETE(p)	{if(p){delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)		{if(p){(p)->release();(p)=nullptr;}}

// # ���� ���� #
// extern : �ٸ� ���, Ȥ�� cpp���� ������ �����ϱ� ���� ����Ѵ�.
// ���������� Ű���带 �����ص� �⺻���� externȭ �Ǵ� ��쵵 �ִ�(vs������ ���� �ٸ�)
extern HINSTANCE	_hinstance;
extern HWND			_hWnd;

//int x, int y���� POINT.x, POINT.y
extern POINT		_ptMouse;

