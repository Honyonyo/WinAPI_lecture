#include "stdafx.h"
#include "Game_ClayShooting.h"

#pragma region Game_ClayShooting
HRESULT Game_ClayShooting::init(void)
{
    return S_OK;
}

void Game_ClayShooting::release(void)
{
}

void Game_ClayShooting::update(void)
{
	doGame();
}

void Game_ClayShooting::render(HDC hdc)
{
    EllipseMakeCenter(hdc, 500, 200, 105, 105);
	drawScreen(hdc);
}

void Game_ClayShooting::throughTarget(short timer)
{
		short speed = 1;
		short size;
	switch (this->level) {
	case 0:
  size = RND->getFromIntTo(30,70);
 
case 1:
  size = RND->getFromIntTo(30, 70);
case 2:
  size = RND->getFromIntTo(20, 60);
case 3:
  size = RND->getFromIntTo(15, 60);
case 4:
  size = RND->getFromIntTo(15, 60);
case 5:
	size = RND->getFromIntTo(13, 50);
	}
	target[timer].set(RND->getInt(3),size, speed);

//타이머 10개정도, 
//랜덤타임 타이머를 유지하면서 투사체를 던지면 투사체가 날아가는 도중 타이머가 돌아왔을 때 투사체위치가.. 망할거같아
}

void Game_ClayShooting::doGame()	//update에 들어갈 함수
{
	this->playTime = GetTickCount() / 1000;
	if (this->playTime > 40) level_time = 2;
	else if (this->playTime > 20)level_time = 2;
	gun.setPt(_ptMouse);

	if (KEYMANAGER->isStayKeyDown(WM_LBUTTONDOWN)) {
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
	}
}

void Game_ClayShooting::drawScreen(HDC hdc)
{
	char strPt[20];
	wsprintf(strPt, "X:%-5dY:%-5d", _ptMouse.x, _ptMouse.y);
	TextOut(hdc, 5, 0, strPt, strlen(strPt));

	original = SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));



	//제일 나중에 출력되어야함
	gun.drawAim(hdc);
}


#pragma endregion

#pragma region Target
void Target::set(short shapeType, short size, short speed)
{
	this->size_base = size;
	this->speed = speed;

	//모양 설정
	this->shapeType = shapeType;
	//점수 설정
	switch (shapeType) {
	case CIRCLE:
		score = -100;
		break;
	case BOX:
		score = 50;
		break;
	case POLY:
		score = 100;
		break;
	}
	//시작점과 끝점 설정
	this->pt_start.x = RND->getInt(2) == 0 ? 0 : WINSIZE_X;
	this->pt_end.x = this->pt_start.x == 0 ? WINSIZE_X : 0;
	this->pt_start.y = RND->getInt(WINSIZE_Y);
	this->pt_end.y = RND->getInt(WINSIZE_Y);
	this->slop = ((float)pt_end.y - pt_start.y) / (pt_end.x - pt_start.y);

	this->center = this->pt_start;

	//나머지 초기화
	this->targeted = false;
	this->gotShoot = false;
	this->goalEndPt = false;
	this->time_gen = GetTickCount64()/1000.0f;
}

void Target::move()
{
	time_move = (GetTickCount64() / 1000.0f) - time_gen;
	//중심점 이동
	if (pt_start.x == 0) {
		center.x = time_move / slop;
		if (center.x == WINSIZE_X) goalEndPt = true;
		center.y = slop * center.x + pt_start.y;
	}
	else {
		center.x = WINSIZE_X - (time_move / slop);
		if (center.x == 0) goalEndPt = true;
		center.y = slop * center.x + pt_end.y;
	}
	if (center.x == pt_end.x) {
		goalEndPt = true;
	}

	//크기 변화
}

void Target::draw(HDC hdc)
{
	if (0/*피격됐을 경우*/) {}
	else//피격 아닌 일반상태인경우
	{
		if (0/*커서가 붙어있을 경우*/) {}
		else {/*제일보통의상태*/
		};
	}
}

void Target::targetSetting(short a)
{
	if (a >= SHAPETYPE_NUMBER || a < 0) {
		HDC hdc = GetDC(_hWnd);
		TextOut(hdc, 0, 0, "타겟 초기화 오류. 범위 바깥의 타겟이 생성되려 함", strlen("타겟 초기화 오류. 범위 바깥의 타겟이 생성되려 함"));
	}
	else shapeType = a;

}

bool Target::isTargetted(POINT mousePt)
{
	switch (this->shapeType) {
	case CIRCLE:

		break;
	case BOX:
		break;

	}
	return targeted;
}

bool Target::isGotAShoot()
{
	if (targeted) gotShoot = true;
	return gotShoot;
}

#pragma endregion

void Gun::drawAim(HDC hdc) {
	SetDCPenColor(hdc, BLACK);
	SetDCBrushColor(hdc, GREEN);
	EllipseMakeCenter(hdc, _ptMouse.x, _ptMouse.y, 7, 7);
	SetDCBrushColor(hdc, WHITE);
	EllipseMakeCenter(hdc, _ptMouse.x, _ptMouse.y, 3, 3);
	LineMake(hdc, _ptMouse.x, _ptMouse.y + 15, _ptMouse.x, _ptMouse.y - 15);
	LineMake(hdc, _ptMouse.x + 15, _ptMouse.y, _ptMouse.x - 15, _ptMouse.y);
	LineMake(hdc, _ptMouse.x + 15, _ptMouse.y + 5, _ptMouse.x + 15, _ptMouse.y - 5);
	LineMake(hdc, _ptMouse.x - 15, _ptMouse.y + 5, _ptMouse.x - 15, _ptMouse.y - 5);
	LineMake(hdc, _ptMouse.x + 5, _ptMouse.y + 15, _ptMouse.x - 5, _ptMouse.y +15);	
	LineMake(hdc, _ptMouse.x + 5, _ptMouse.y - 15, _ptMouse.x - 5, _ptMouse.y - 15);
}