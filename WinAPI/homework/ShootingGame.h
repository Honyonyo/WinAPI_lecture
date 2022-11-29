#pragma once

#define BULLET_MAX			80
#define PLAYER_SPEED		5
#define ENEMY_MAX			10

//����ü�� Ȯ�强�� ���
struct tagBullet
{//�Ѿ��� �÷��̾�� �ͼӵȴ�.
	//�浹����,��Ȱ���� ���� rect, bool

	RECT rc;
	bool fire;
};

struct tagEnemy
{
	RECT rc;
	int speed;
	bool die;
};

struct tagPlayer {
	RECT rc;
	int hp;
	bool die;
};

class MainGame_18
{
private:
	tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];
	tagPlayer _player;

	RECT _hpBar[4];

	//Homework game;
public:
	void fireBullet(void);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);



}