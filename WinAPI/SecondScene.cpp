#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("������", "Resources/Images/Background/backgroundroop.bmp", 1570, WINSIZE_Y);
	_offsetX = _offsetY = 0;
	_bgSpeed = 0;
	std::cout << "SecondScene init()" << std::endl;
	return S_OK;
}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
	_bgSpeed += 3;
}


void SecondScene::render(void)
{
	IMAGEMANAGER->loopRender("������", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);
	std::cout << "SecondScene render()" << std::endl;

	//SetBkMode : �����ϰ� ���ִ� �Լ�
	// - ���� �ڷ� ����� ���̰� �Ѵ�.
	SetBkMode(getMemDC(), TRANSPARENT);

	char str[128];
	wsprintf(str, "������Ʈ");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	HFONT font;
	HFONT oldFont;


	/*
	font = CreateFont
	(
	1. ���� ũ��, ������, ���ڱ���, ���ڹ���, ���ڱ���,
	����(true,false), ����, ��Ҽ�,
	2. ���ڼ���, ��� ��Ȯ��, Ŭ����, ����� ��, �ڰ�, 3. ��Ʈ
	)
	���־��°� 1, 2, 3
	*/
	font = CreateFont
	(70, 0,0,0, 600,
		0,0,1,
		HANGUL_CHARSET, 0,0,0,0, TEXT("�޸ձ���")
	);	//HANGUL_CHARSET : ��Ƽ����Ʈ  HANGEUL_CHARSET : �����ڵ�

	oldFont = (HFONT)(SelectObject(getMemDC(), font));

	wsprintf(str, "���ο� ��Ʈ");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

