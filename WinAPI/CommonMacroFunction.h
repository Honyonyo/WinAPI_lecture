#pragma once
#include "stdafx.h"//�̰� ���� �Ǵ°� �³�?
inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//�簢�������. ����갳�� �������� ���⼭ �Լ��� ������ ��
inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, width, height };
	return rc;
}

//�簢���׸���
inline void DrawRectMake(HDC hdc, RECT rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//�簢�� �����(�߽����� ���̸� �̿�)
inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//�簢�� �׸��� (���ʱ� �Լ�)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, width, height);
}

//Ÿ�� �׸��� (�ϸ���)
inline void EllipseMake(HDC hdc, int startX, int startY, int width, int height) {
	Ellipse(hdc, startX, startY, startX + width, startY + height);
}

//Ÿ�� �׸��� (�ϸ���, ������ ������)
inline void EllipseMakeCenter(HDC hdc, int centerX, int centerY, int halfWidth, int halfHeight) {
	Ellipse(hdc, centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
}