#pragma once

#define SHAPETYPE_NUMBER	3
#define CIRCLE				0
#define BOX					1
#define POLY				2

#define BLACK			RGB(0,0,0)
#define WHITE			RGB(255,2552,255)
#define RED				RGB(230,100,100)
#define BLUE			RGB(0,100,255)
#define GREEN			RGB(0,225,0)

//Ÿ�� ������� 15���� 60����, 
class Target {
private:
	short shapeType;
	short size_base = 0;
	short size_now = 0;
	short speed = 0;
	short score = 0;
	POINT center = { 0,0 };

	POINT pt_start = { 0,0 };
	POINT pt_end = { 0,0 };
	float slop = 0;

	float time_gen = 0;
	float time_move = 0;

	bool targeted = false;
	bool gotShoot = false;
	bool goalEndPt = false;

public:
	void set(short shapeType,short size, short speed);
	void move();
	void draw(HDC hdc);
	void targetSetting(short a);
	bool isTargetted(POINT mousePt);
	bool isGotAShoot();
};

class Gun {
private:
	POINT _pt;
public:
	void drawAim(HDC hdc);
	void setPt(POINT pt) {	this->_pt = pt;	}
	POINT getPT() {	return this-> _pt;	}
};


class Game_ClayShooting
{
private:
	Target target[10];
	Gun gun;
	float playTime = 0;

	short timerTime[10];

	int myScore = 0;
	short level = 0; //(������ 0~5������ 6����, �ð������� 2�������� �ڵ�����. ���ھ ������ �� �ö󰣴�.
	//3000��, 6000��, 10000��)
	short level_time = 0;
	short level_adventige = 0;
	int activatingTimer = 3;

	//�׸��׸����
	HGDIOBJ original = NULL;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void throughTarget(short timer);

	void doGame();

	void drawScreen(HDC hdc);
};

