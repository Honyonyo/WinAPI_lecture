#include "stdafx.h"
#include "MainGame.h"


HRESULT MainGame::init(void)
{
	GameNode::init();
	pooFighter.init();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	pooFighter.release();
}

void MainGame::update(void)
{
	
	//game.doGame();



	GameNode::update();
	pooFighter.update();

}


void MainGame::render(HDC hdc)
{
	pooFighter.render(hdc);
	//game.render(hdc);

}
