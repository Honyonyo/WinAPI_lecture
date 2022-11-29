#pragma once
#include "SingletonBase.h"

//���Ű ����ؼ� �˳��� ����� Ű����
#define KEY_MAX 256

class KeyManager :public SingletonBase <KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];
	//true false�� �̱��濡�� �ӽñ�ӽñ� ������ ��ĥ ���ֱ� ������ ��Ʈ������ ��Ʈ�� �ɰ� �ӽñ�ӽñ⸦ ����ϱ�� �Ͽ���.

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);

	//Ű�� �ѹ� ���ȴ���
	bool isOnceKeyDown(int key);
	//�ѹ� ������ �������
	bool isOnceKeyUp(int key);
	//Ű�� ��� �����ִ���
	bool isStayKeyDown(int key);
	//���Ű - ������ ���°� �����Ǵ�
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();
};

