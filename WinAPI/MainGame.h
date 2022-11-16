#pragma once
#include "GameNode.h"
#include "Game_ClayShooting.h"

class MainGame : public GameNode
{
private:
	RECT rc = {};

	Game_ClayShooting game;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
};

