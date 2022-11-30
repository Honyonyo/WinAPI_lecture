#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	IMAGEMANAGER->addImage("빙산의일각", "Resources/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("사과나무", "Resources/Images/Object/appleTree.bmp", 800, 800);


	_start = new StartScene;
	_start->init();
	_second = new SecondScene;
	_second->init();

	//핵심
	_currentScene = _start;
	//<->  혹은 <!-!>의 형태를 이용
	assert(_currentScene != nullptr);
	//static_assert

	/*
	▶assert
	-"디버깅모드"에서 동작하는오류검출용 함수
	릴리즈모드에서는 동작하지 않는다.

	- assert가 걸리게 되면 버그 발생 위치와 콜스택, 그리고 변수에 대한 잘못된 참조값을 볼 수 있다. (프로그래머가 예외처리를 했을 경우)
	- 편리한 디버깅을 위해서 예외처리는 if로 거르고, 핵심파트에만 사용한다.

	동작방식
	Expression -> false ->assert error
	 ! 거짓일 때 발동 !
	 대부분의 문법은 true일 때 동작하게 되어있지만,
	 assert는 false일 때 동작한다.
	  꼭 일어나야 하는 동작을 명시하면
	  꼭 일어나야하는 사건이 일어나지 않을 때 assert가 뜬다.

	예시 ) assert(A !=NULL)
		A가 NULL이 아니면 true이므로 pass
		A가 NULL이면 false이므로 발동

	assert() : [C] 컴파일타임을 지나 프로그램을 실행시키고, 문제를 파악(런타임) 
		에러창 팝업
	static_assert : [C++] 컴파일중에 문제를 파악 (컴파일타임) -> (컴파일 타임->상수)
		하단 출력문구에 출력됨
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
