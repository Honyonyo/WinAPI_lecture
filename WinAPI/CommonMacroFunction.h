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

//사각형 만들기(중심점과 길이를 이용)
inline RECT RectMakeCenter(int x, int y, int width, int height) {
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형그리기
inline void DrawRectMake(HDC hdc, RECT rc) {
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//사각형 그리기 (렉탱글 함수)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height) {
	Rectangle(hdc, x, y, x+width, x+height);
}

//타원 그리기 (일립스)
inline void EllipseMake(HDC hdc, int startX, int startY, int width, int height) {
	Ellipse(hdc, startX, startY, startX + width, startY + height);
}

//타원 그리기 (일립스, 중점과 반지름)
inline void EllipseMakeCenter(HDC hdc, int centerX, int centerY, int halfWidth, int halfHeight) {
	Ellipse(hdc, centerX - halfWidth, centerY - halfHeight, centerX + halfWidth, centerY + halfHeight);
}



// 
// # 내가 추가한 것 #
// 

//포인트 2개 거리비교
inline void PointDistance(POINT pt1, POINT pt2) {

}

//큰 RECT 안에 작은 RECT가 있는가
inline bool RectInRect(RECT BIGrc, RECT SMALLrc) {
	if ((BIGrc.left < SMALLrc.left) && (BIGrc.right > SMALLrc.right) && (BIGrc.top < SMALLrc.top) && (BIGrc.bottom > SMALLrc.bottom))
		return true;
	else return false;
}

//1네모 안에 2네모가 포함관계인가(시작점과 길이)
inline bool RectInRect(int x, int y, int width, int height,
	int x2, int y2, int width2, int height2)
{
	if (x < x2 && (x2 + width2) < (x + width) && y < y2 && (y2 + height) < (y + height)) return true;
	else return false;
}

//포인트가 rect구조체 안에 있는지
inline bool PointInRect( POINT pt, RECT rc ) {
	if ((rc.left < pt.x) && (pt.x < rc.right) && (rc.top < pt.y) && (pt.y < rc.bottom))	return true;
	else return false;
}

//포인트가 rectangle선 안에 있는지
inline bool PointInRect(POINT pt,int boxStartX, int boxStartY, int width, int height) {
	if ((boxStartX < pt.x) && (pt.x < boxStartX+width) && (boxStartY < pt.y) && (pt.y < boxStartX+height))	return true;
	else return false;
}

 //포인트가 시작점+길이로 만들어진 rectangle 선 안에 있는지
inline bool PointInRect_point(POINT pt, POINT boxStart, int width, int height) {
	if ((boxStart.x < pt.x) && (pt.x < boxStart.x + width) && (boxStart.y < pt.y) && (pt.y < boxStart.y + height))	return true;
	else return false;
}