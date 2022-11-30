#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("�������ϰ�", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�������", "Resources/Images/Object/appleTree.bmp", 800, 800);


	_start = new StartScene;
	_start->init();
	_second = new SecondScene;
	_second->init();

	//�ٽ�
	_currentScene = _start;
	//<->  Ȥ�� <!-!>�� ���¸� �̿�
	assert(_currentScene != nullptr);
	//static_assert

	/*
	��assert
	-"�������"���� �����ϴ¿�������� �Լ�
	�������忡���� �������� �ʴ´�.

	- assert�� �ɸ��� �Ǹ� ���� �߻� ��ġ�� �ݽ���, �׸��� ������ ���� �߸��� �������� �� �� �ִ�. (���α׷��Ӱ� ����ó���� ���� ���)
	- ���� ������� ���ؼ� ����ó���� if�� �Ÿ���, �ٽ���Ʈ���� ����Ѵ�.

	���۹��
	Expression -> false ->assert error
	 ! ������ �� �ߵ� !
	 ��κ��� ������ true�� �� �����ϰ� �Ǿ�������,
	 assert�� false�� �� �����Ѵ�.
	  �� �Ͼ�� �ϴ� ������ ����ϸ�
	  �� �Ͼ���ϴ� ����� �Ͼ�� ���� �� assert�� ���.

	���� ) assert(A !=NULL)
		A�� NULL�� �ƴϸ� true�̹Ƿ� pass
		A�� NULL�̸� false�̹Ƿ� �ߵ�

	assert() : [C] ������Ÿ���� ���� ���α׷��� �����Ű��, ������ �ľ�(��Ÿ��) 
		����â �˾�
	static_assert : [C++] �������߿� ������ �ľ� (������Ÿ��) -> (������ Ÿ��->���)
		�ϴ� ��¹����� ��µ�
	*/
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_start);
	SAFE_DELETE(_second);

}

void MainGame::update(void)
{
	GameNode::update();
	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _currentScene = _second;
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON)) _currentScene = _start;
}

void MainGame::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);


	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}
