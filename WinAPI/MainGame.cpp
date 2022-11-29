
#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	_alphaA = 0;
	_isAlphaIncrease = false;

	_offsetX, _offSetY = 0;
	_bgSpeed = 0;

	GameNode::init(true);

	IMAGEMANAGER->addImage("���彺���̽�", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�������ϰ�", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("��� ����", "Resources/Images/Background/backgroundroop.bmp",
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
	//�޸𸮵�ÿ��� hdc�� �Ѿ���� ������ ������ �ִ°���, 
//memdc�κ��� getHDC�� �����ϸ� ��� �� �ȴ�.. 
	GameNode::render();

	//����� ���´�.
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	//IMAGEMANAGER->render("�������ϰ�", getMemDC(), 0, 0);
	IMAGEMANAGER->loopRender("��� ����", getMemDC(),
		&RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);


	this->getBackBuffer()->render(getHDC());
}
