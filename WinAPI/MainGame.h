#pragma once
#include "GameNode.h"
#include "똥피하기.h"
/*
include "두더지잡기.h"
*/


class MainGame : public GameNode
{
private:
	똥피하기 pooFighter;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

};

