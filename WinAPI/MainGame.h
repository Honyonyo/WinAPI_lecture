#pragma once
#include "GameNode.h"
/*
* README
*/

class MainGame : public GameNode
{
private:

	int _alphaA;
	bool _isAlphaIncrease;

	int _offsetX, _offSetY;
	float _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	bool mouseInMe();
	void clickMoveMe();
	void impact();

	MainGame() {}
	~MainGame() {}
};

