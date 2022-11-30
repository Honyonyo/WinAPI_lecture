#pragma once
#include "GameNode.h"
#include "StartScene.h"
#include "SecondScene.h"


/*
* README
*/

class MainGame : public GameNode
{
private:
	StartScene* _start;
	SecondScene* _second;

	GameNode* _currentScene;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	
	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}
};
/*
��ó������ܰ�

1. �ε�

2. ���α׷�����

*/
