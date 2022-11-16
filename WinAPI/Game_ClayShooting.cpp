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

//Ÿ�̸� 10������, 
//����Ÿ�� Ÿ�̸Ӹ� �����ϸ鼭 ����ü�� ������ ����ü�� ���ư��� ���� Ÿ�̸Ӱ� ���ƿ��� �� ����ü��ġ��.. ���ҰŰ���
}

void Game_ClayShooting::doGame()	//update�� �� �Լ�
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



	//���� ���߿� ��µǾ����
	gun.drawAim(hdc);
}


#pragma endregion

#pragma region Target
void Target::set(short shapeType, short size, short speed)
{
	this->size_base = size;
	this->speed = speed;

	//��� ����
	this->shapeType = shapeType;
	//���� ����
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
	//�������� ���� ����
	this->pt_start.x = RND->getInt(2) == 0 ? 0 : WINSIZE_X;
	this->pt_end.x = this->pt_start.x == 0 ? WINSIZE_X : 0;
	this->pt_start.y = RND->getInt(WINSIZE_Y);
	this->pt_end.y = RND->getInt(WINSIZE_Y);
	this->slop = ((float)pt_end.y - pt_start.y) / (pt_end.x - pt_start.y);

	this->center = this->pt_start;

	//������ �ʱ�ȭ
	this->targeted = false;
	this->gotShoot = false;
	this->goalEndPt = false;
	this->time_gen = GetTickCount64()/1000.0f;
}

void Target::move()
{
	time_move = (GetTickCount64() / 1000.0f) - time_gen;
	//�߽��� �̵�
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

	//ũ�� ��ȭ
}

void Target::draw(HDC hdc)
{
	if (0/*�ǰݵ��� ���*/) {}
	else//�ǰ� �ƴ� �Ϲݻ����ΰ��
	{
		if (0/*Ŀ���� �پ����� ���*/) {}
		else {/*���Ϻ����ǻ���*/
		};
	}
}

void Target::targetSetting(short a)
{
	if (a >= SHAPETYPE_NUMBER || a < 0) {
		HDC hdc = GetDC(_hWnd);
		TextOut(hdc, 0, 0, "Ÿ�� �ʱ�ȭ ����. ���� �ٱ��� Ÿ���� �����Ƿ� ��", strlen("Ÿ�� �ʱ�ȭ ����. ���� �ٱ��� Ÿ���� �����Ƿ� ��"));
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