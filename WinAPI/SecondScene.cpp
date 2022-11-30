#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("배경루프", "Resources/Images/Background/backgroundroop.bmp", 1570, WINSIZE_Y);
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
	IMAGEMANAGER->loopRender("배경루프", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);
	std::cout << "SecondScene render()" << std::endl;

	//SetBkMode : 투명하게 해주는 함수
	// - 글자 뒤로 배경이 보이게 한다.
	SetBkMode(getMemDC(), TRANSPARENT);

	char str[128];
	wsprintf(str, "기존폰트");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	HFONT font;
	HFONT oldFont;


	/*
	font = CreateFont
	(
	1. 문자 크기, 문자폭, 문자기울기, 문자방향, 문자굵기,
	기울기(true,false), 밑줄, 취소선,
	2. 문자세팅, 출력 정확도, 클리핑, 출력의 질, 자간, 3. 폰트
	)
	자주쓰는거 1, 2, 3
	*/
	font = CreateFont
	(70, 0,0,0, 600,
		0,0,1,
		HANGUL_CHARSET, 0,0,0,0, TEXT("휴먼굴림")
	);	//HANGUL_CHARSET : 멀티바이트  HANGEUL_CHARSET : 유니코드

	oldFont = (HFONT)(SelectObject(getMemDC(), font));

	wsprintf(str, "새로운 폰트");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

