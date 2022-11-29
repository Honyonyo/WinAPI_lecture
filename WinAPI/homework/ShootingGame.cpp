#include "stdafx.h"
#include "ShootingGame.h"


HRESULT MainGame_18::init(void)
{

	_player.rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	_player.hp = 3;
	_player.die = false;

	_hpBar[3] = RectMake(60, 27, 230, 40);
	for (int i = 0; i < _player.hp; i++) {
		_hpBar[i] = RectMake(60, 27, (i + 1) * 110, 40);
	}

	for (int i = 0;i < ENEMY_MAX;i++)
	{
		_enemy[i].rc = RectMakeCenter(
			RND->getFromIntTo(20, WINSIZE_X - 20),
			RND->getFromIntTo(-20, WINSIZE_Y - 80), 20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;
	}

	return S_OK;
}

void MainGame_18::release(void)
{
}

void MainGame_18::update(void)
{
	//game.doGame();


	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _player.rc.right);
	{
		_player.rc.left += PLAYER_SPEED;
		_player.rc.right += PLAYER_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.rc.left > 0);
	{
		_player.rc.left -= PLAYER_SPEED;
		_player.rc.right -= PLAYER_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player.rc.right > 0);
	{
		_player.rc.top += PLAYER_SPEED;
		_player.rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _player.rc.right);
	{
		_player.rc.top -= PLAYER_SPEED;
		_player.rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
		fireBullet();
	}
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!_bullet[i].fire)continue;
		_bullet[i].rc.bottom += PLAYER_SPEED;
		_bullet[i].rc.top += PLAYER_SPEED;
	}

	for (int i = 0;i < ENEMY_MAX;i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;
	}

	for (int i = 0;i < ENEMY_MAX;i++)
	{
		if (_enemy[i].rc.top > WINSIZE_Y)
			_enemy[i].rc = RectMakeCenter(
				RND->getFromIntTo(20, WINSIZE_X - 20),
				RND->getFromIntTo(-20, WINSIZE_Y - 80), 20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;
	}

	for (int i = 0;i < ENEMY_MAX;i++) {
		for (int j = 0; j < BULLET_MAX; j++) {
			RECT temp;

			//rect���� �������� ���ϱ� ���� �Լ�
			// ù��° ���� : �� �簢���� �浹���� �� ����� �簢��
			// temp�� ũ�Ⱑ �����ϸ� �浹, �ƴ϶�� x
			// ���� 2, 3�� ��ġ�� ������ ���� 1�� �����Ѵ�.
			// �浹�� ������ nonzero, �浹�� ������ 0 ->if�� ���
			if (IntersectRect(&temp, &_enemy[i].rc, &_bullet[j].rc)) {
				_enemy[i].rc.left -= 1400;
				_enemy[i].rc.right -= 1400;
				_enemy[i].rc.top -= 1400;
				_enemy[i].rc.bottom -= 1400;

				_enemy[i].die = false;

				_bullet[j].rc.left += 1400;
				_bullet[j].rc.right += 1400;
				_bullet[j].rc.top += 1400;
				_bullet[j].rc.bottom += 1400;
			}
		}
	}


	//�÷��̾� �� �浹
	for (int i = 0;i < ENEMY_MAX;i++) {
		RECT temp;
		if (IntersectRect(&temp, &_enemy[i].rc, &_player.rc))
		{
			_enemy[i].rc.left -= 1400;
			_enemy[i].rc.right -= 1400;
			_enemy[i].rc.top -= 1400;
			_enemy[i].rc.bottom -= 1400;

			_enemy[i].die = false;

			if (_player.hp <= 0)
			{
				_player.hp = 0;
				_player.rc.left = 1000;
				_player.rc.right = 1000;
				_player.rc.top = 1000;
				_player.rc.bottom = 1000;
			}
			else _player.hp -= 1;
			_hpBar[_player.hp].left += 1000;
			_hpBar[_player.hp].right += 1000;
			_hpBar[_player.hp].top += 1000;
			_hpBar[_player.hp].bottom += 1000;
		}
	}


}


void MainGame_18::render(HDC hdc)
{

	DrawRectMake(hdc, _player.rc);
	for (int i = 0;i < ENEMY_MAX;i++)
	{
		DrawRectMake(hdc, _enemy[i].rc);
	}

	for (int i = 0; i < BULLET_MAX; i++) {
		if (!_bullet[i].fire)continue;
		Ellipse(hdc, _bullet[i].rc.left, _bullet[i].rc.top, _bullet[i].rc.right, _bullet[i].rc.bottom);
	}


	Rectangle(hdc, _hpBar[3].left, _hpBar[3].top, _hpBar[3].right, _hpBar[3].bottom);
	HBRUSH brushA = CreateSolidBrush(RGB(255, 0, 0));
	FillRect(hdc, &_hpBar[0], brushA);
	DeleteObject(brushA);
	HBRUSH brushB = CreateSolidBrush(RGB(255, 255, 0));
	FillRect(hdc, &_hpBar[1], brushA);
	DeleteObject(brushB);
	HBRUSH brushC = CreateSolidBrush(RGB(0, 255, 0));
	FillRect(hdc, &_hpBar[2], brushA);
	DeleteObject(brushC);

	/*
	sprintf_s() : char���, �ʼ����� ����, �����ڵ� X
		��CRT ���̺귯���� ����ϴ� �Լ�.
	wsprintf() : ���ڿ� �ռ� �Լ�, ���ۿ� �����
		��window�� w��;;�÷��� SDK���� �����ϴ� �Լ�, �Ǽ����� ����� �� ����.
	*/
	char strPosition[64];
	sprintf_s(strPosition, "HP: %d", _player.hp);
	TextOut(hdc, 10, 40, strPosition, strlen(strPosition));


	//game.render(hdc);
}



void MainGame_18::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (_bullet[i].fire)continue;
		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter(
			(_player.rc.left + _player.rc.right) / 2, (_player.rc.top + _player.rc.bottom) / 2, 50, 50
		);
		break;
	}
}

