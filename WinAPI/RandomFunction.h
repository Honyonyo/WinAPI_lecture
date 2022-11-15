#pragma once
#include "SingletonBase.h"

/*
����1.���콺�� ������ ���� ����ϱ�
���콺�� Ŭ���� ��ǥ�� ������ ������ ���
������ ũ��, ���, �������� ��� ������

������ ���� : �簢��, ��, (����) �ﰢ�� �� �ٰ���
�ٰ��� �� �ﰢ���� Polygon()���̿��Ѵ�.

����2. �� �� �׷�����
����!�� �̿��ؼ� �׷��´�.
���콺 Ŭ�� ��ǥ..���� �̿��ϸ� ��Ģ

����3. �� ƨ���.(���� 1���� 2�� �ȵ����� ���� ����~)
ū �簢�� �ȿ� ���� ���� �ִ�.
���� ���� ū �簢�� �ȿ��� ����� �Է��� ��� �簢�� �鿡 ƨ��鼭 �����δ�.
ū �簢���� Ű���� �Է��� ���� �� ������ ũ�⸦ ���� �� �ִ�.
ũ�Ⱑ �پ��� ���� ���� ������ �޴´�.
���콺 ���� Ŭ�� : �� �ӵ� ����
���콺������Ŭ�� : �� �ӵ� ����
���� : �������� �� �ڿ������� ������� ���� �����Ѵ�.
��Ʈ : WM_TIMER / SetTimer / KillTimer

�������� : GetAsyncKeyState

*/



class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction() {
		srand(GetTickCount());
		//	���� �õ� �ʱ�ȭ. GetTickCount():API�Լ���, os�� ���õ� ���� ��� �ð��� üũ�Ѵ�.
		// �и����������� üũ, ��ȯ�� �Ǳ� ������ �Ը� ũ�� ���� ������ ����.
	}
	~RandomFunction(){}

	inline int getInt(int num)	{		return rand() % num;	}
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }
	inline float getfloat(void) {		return (float)rand() / (float)RAND_MAX;}
	inline float getfloat(float num) { return (float)rand() / (float)RAND_MAX*num; }
	float getFromFloatTo(float fromNum, int toNum) {
		float rnd = (float)rand() / (float)RAND_MAX;
		return(rnd * (toNum = fromNum) + fromNum);
	}

private:

};