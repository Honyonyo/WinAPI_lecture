#pragma once
#include "GameNode.h"
#include "�����ϱ�.h"
/*
include "�δ������.h"
*/


class MainGame : public GameNode
{
private:
	�����ϱ� pooFighter;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

};

