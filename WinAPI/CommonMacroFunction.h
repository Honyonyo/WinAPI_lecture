#pragma once
#include "stdafx.h"//이게 들어가도 되는거 맞나?
inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//사각형만들기. 헤더산개를 막기위해 여기서 함수로 감싸준 것
inline RECT RectMake(int x, int y, int width, int height) {
	RECT rc = { x, y, width, height };
	return rc;
}

//사각형그리기
inline void DrawRectMake(HDC hdc, RECT rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//사각형 만들기(중심점과 길이를 이용)
inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형 그리기 (렉탱글 함수)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, width, height);
}

//타원 그리기 (일립스)
inline void EllipseMake(HDC hdc, int startX, int startY, int width, int height) {
	Ellipse(hdc, startX, startY, startX + width, startY + height);
}

//타원 그리기 (일립스, 중점과 반지름)
inline void EllipseMakeCenter(HDC hdc, int centerX, int centerY, int halfWidth, int halfHeight) {
	Ellipse(hdc, centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
}