#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{
private:
	RECT rc = {};

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
};
