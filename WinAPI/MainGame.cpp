
#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	_alphaA = 0;
	_isAlphaIncrease = false;

	_offsetX, _offSetY = 0;
	_bgSpeed = 0;

	GameNode::init(true);

	IMAGEMANAGER->addImage("데드스페이스", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("빙산의일각", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/Background/backgroundroop.bmp",
		1570, WINSIZE_Y);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

}

void MainGame::update(void)
{
	GameNode::update();
	_bgSpeed += 1;
}

void MainGame::render(void)
{
	//메모리디시에서 hdc로 넘어오는 과정에 문제가 있는건지, 
//memdc부분을 getHDC로 변경하면 출력 잘 된다.. 
	GameNode::render();

	//백버퍼 얻어온다.
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	//IMAGEMANAGER->render("빙산의일각", getMemDC(), 0, 0);
	IMAGEMANAGER->loopRender("배경 루프", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);


	this->getBackBuffer()->render(getHDC());
}
