#pragma once
#include "stdafx.h"
//
#define 엉겅퀴		RGB(220,220,240) 
#define RAVENDER	RGB(230,230,250)
#define WHITE		RGB(255,255,255)
using namespace std;
class Face {
private:
	HGDIOBJ original = NULL;
	vector<POINT>::iterator iter;
	vector<POINT>::reverse_iterator riter;


	//프린트 순서 : 뒷머리->머리통 -> 머리통 그림자->얼굴->앞머리->손
#pragma region 머리통 좌표....
POINT head[45] = { {280,115},{319,107},{369,114},{405,128},{439,154},{463,185},{482,221},{495,261},{495,289},{490,303},
/*얼굴외곽선*/		{466,311},{490,300},{507,308},{513,330},{517,343},{515,361},{507,382},{502,402},{493,406},{481,413},
					{472,444},{455,475},{419,503},{387,537},{330,560},{274,565},{234,554},{208,518},{193,487},{185,474},
					{178,462},{172,448},{167,433},{163,424},{161,414},{159,403},{159,392},{156,381},{152,342},{147,289},
					{158,236},{175,185},{197,148},{218,131},{248,120} };

vector<POINT> lftShadow_1 = { {248,120},{253,164},{221,206},{191,189},{175,185}, {184,169}, {197,148},{218,131} };
vector<POINT> lftShadow_2 = { {147,289},{151,260}, {158,236}, {163,214}, {175,185},{191,189},{221,206},{223,238},{215,255},{187,270},{168,291} };
vector<POINT> lftShadow_3 = { {168,291},{186,284},{214,285},{242,292},{266,309},{266,330},{250,354},{222,369},{187,381},{170,382},{156,381},{154,359},{152,342},{150,325},{148,311}, {147,289} };
vector<POINT> lftShadow_4 = { {193,487},{178,462},{167,433},{161,414},{159,403},{156,381}, {170,382},{188,408},{202,431},{217,454},{255,465},{223,477},{212,481},{204,484} };
vector<POINT> lftShadow_5 = { {255,465},{276,502},{280,522},{279,541},{274,565},{250,561}, {234,554},{219,536}, {208,518},{199,505}, {193,487},{204,484}, {212,481},{223,477} };
vector<vector<POINT>> faceShadow= { lftShadow_1 ,lftShadow_2,lftShadow_3,lftShadow_4 ,lftShadow_5 };


vector<POINT> lftShadowEraser = { {255,465} ,{170,382},{173,398},{190,430},{222,455} };
vector<POINT> rightShadow1 = { {370,342},{340,347},{314,344},{300,332},{295,317},{293,293},{305,276},{330,265},{358,262},{399,264},{412,275}, {416,291} };
vector<POINT> rightShadowEraser = { {370,342}, {416,291},{406,307},{385,311},{374,323} };
vector<vector<POINT>> fShadowEraser = { lftShadowEraser };
#pragma endregion

#pragma region 머리카락 좌표
//뒤에 rightHairLine_2_1역순으로 붙여야함. 역방향이터레이터나 i--해야함
vector<POINT> vBackhair = {
		{279,105},{287,94},{306,85},{327,81}

,{344,82},{365,88},{379,91},{403,101},{428,115}
,{441,126},{453,137},{462,148},{468,156},{479,175}
,{483,185},{489,197},{498,220},{503,237},{505,248}
,{511,262},{514,271},{519,278},{525,287},{531,292}
,{538,302},{543,305},{554,306}
,{532,306}
,{528,324},{529,336},{530,360},{529,374},{525,388}
,{522,403},{514,421},{486,458},{463,476}
//rightHairLine_2_1역순으로 붙여야함. 역방향이터레이터나 i--해야함
};
vector<POINT> vFrontHair = {
{279,105},{287,94},{306,85},{327,81}

,{345,91},{361,92},{374,97},{391,103},{407,117},{415,129},{421,139},{426,150},{432,164},{437,179},{440,179},{441,213},{443,228},{446,243},{452,254},{460,266}
};	//rightHairLine3 + RightHairLine_4역방향 붙여야함

vector<POINT> rghtHairLine_1 = {
	//line2겹치는부분
	{279,105},{287,94},{306,85},{327,81}

,{344,82},{365,88},{379,91},{403,101},{428,115},{441,126},{453,137},{462,148},{468,156},{479,175},{483,185},{489,197},{498,220},{503,237},{505,248},{511,262},{514,271},{519,278},{525,287},{531,292},{538,302},{543,305},{554,306}
};
//2_1을 역순으로 backHair에 넣기위해서 분리함..
vector<POINT> rghtHairLine_2_1 = {
	//line1겹치는부분
{279,105},{287,94},{306,85},{327,81}

,{345,91},{361,92},{374,97},{391,103},{407,117},{415,129},{421,139},{426,150},{432,164},{437,179},{440,179},{441,213},{443,228},{446,243},{452,254},{460,266}
	
	//line3겹치는부분(시작점)
,{469,278}
};
vector<POINT> rightHairLine_2_2 = { {479,289},{486,295},{502,300},{515,303}

//line1과 연결하면 좋을..
,{532,306}

,{543,313},{556,317},{569,317} };
vector<POINT> rghtHairLine_3 = {
	{469,278},{474,294},{487,305},{500,316},{513,328},
	
	//line4와 연결됨
	{534,346},{539,353},{546,362}
};
vector<POINT> rghtHairLine_4 = {
	{283,152},{291,132},{306,125},{317,125},{329,132},{339,144},{348,157},{355,173},{358,194},{359,215},{361,233},{367,251},{368,263},{374,275},{384,287},{395,295},{411,304},{431,315},{445,324},{457,331},{470,335},{481,338},{494,341},{507,344},{521,343},{534,345}
};
vector<POINT> lftHairLine_1 = {
	{279,105},{268,95},{247,91},{231,91},{216,97},{201,105},{186,116},{176,131},{166,145},{157,159},{147,173},{140,186},{135,204},{129,220},{126,239},{124,257},{122,279},{126,295},{129,308},{131,324},{133,337},{134,355},{133,373},{136,389},{132,399},{116,411 }

};
vector<POINT> lftHairLine_2 = {};
vector<POINT> lftHairLine_3 = {};

#pragma endregion



	POINT face;
	POINT hand;

	//폴리곤에 넣을 배열들 (head는 위에 있음)
	POINT** fShadowPoly;
	POINT** fShadowErPoly;
	POINT* backHair;	//vBackHair + rightHairLine_2_1(역방향)
	POINT* frontHair;	//vFrontHair + rightHairLine_3 + RightHairLine_4(역방향) + leftHairLine_2+leftHairLine_1(역방향)

	

public:
	Face() {
	}
	//프린트 순서 : 뒷머리->머리통 -> 머리통 그림자->얼굴->앞머리->손
	void draw(HDC hdc) {
		drawBackHair(hdc);
		drawHead(hdc);
		drawFace(hdc);
		drawFrontHair(hdc);
		drawHand(hdc);
}
	void drawHead(HDC hdc) {
		Polygon(hdc, head, 45);
		drawShadow(hdc);
	}
	void drawShadow(HDC hdc) {
		original = SelectObject(hdc, GetStockObject(DC_PEN));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RAVENDER);	//면색
		SetDCPenColor(hdc, 엉겅퀴);	//펜색



		//얼굴그림자 좌표 벡터를 배열로 바꾸기
		POINT** fShadowPoly = new POINT * [faceShadow.size()];
		for (int i = 0; i < faceShadow.size(); i++) {
			fShadowPoly[i] = new POINT[faceShadow[i].size()];
			for (int j = 0; j < faceShadow[i].size(); j++) {
				fShadowPoly[i][j] = faceShadow[i][j];
			}
		}
		POINT** fShadowErPoly = new POINT * [fShadowEraser.size()];
		for (int i = 0; i < fShadowEraser.size(); i++) {
			fShadowErPoly[i] = new POINT[fShadowEraser[i].size()];
			for (int j = 0; j < fShadowEraser[i].size(); j++) {
				fShadowErPoly[i][j] = fShadowEraser[i][j];
			}
		}


		//얼굴 그림자 그리기
		for(int i = 0; i<faceShadow.size();i++)
		{
			Polygon(hdc, fShadowPoly[i], faceShadow[i].size());
			for(int j = 0; j< faceShadow[i].size()*5; j++)
			{
			int rand1 = RND->getInt(faceShadow[i].size());
			int rand2 = RND->getInt(faceShadow[i].size());
				LineMake(hdc, fShadowPoly[i][rand1].x, fShadowPoly[i][rand1].y, fShadowPoly[i][rand2].x, fShadowPoly[i][rand2].y);
				//char strPT[50];
				//wsprintf(strPT, "%d,%d에서 %d,%d로", fShadowPoly[i][rand1].x, fShadowPoly[i][rand1].y, fShadowPoly[i][rand2].x, fShadowPoly[i][rand2].y);
				//TextOut(hdc, i * 100, j * 20, strPT, strlen("strPT"));
			}//for j
		}//for i
		//얼굴 그림자 빈부분 지우기
		for(int i = 0; i< fShadowEraser.size(); i++)
		{
			SetDCBrushColor(hdc, WHITE);	//면색
			SetDCPenColor(hdc, WHITE);	//펜색
			Polygon(hdc, fShadowErPoly[i], fShadowEraser[i].size());
		LineMake(hdc, fShadowErPoly[i][0].x, fShadowErPoly[i][0].y, fShadowErPoly[0][1].x, fShadowErPoly[0][1].y);
		}

	}

	void drawBackHair(HDC hdc) {
		for (riter = rghtHairLine_2_1.rbegin(); riter < rghtHairLine_2_1.rend(); riter++) {
			vBackhair.push_back(*riter);
		}

		backHair = new POINT[vBackhair.size()];
		iter = vBackhair.begin();
		for (int i =0; iter < vBackhair.end(); iter++) {
			backHair[i] =*iter;
			i++;
		}
		char text[50];
		wsprintf(text, "시작점%d,%d %d,%d %d,%d", backHair[0].x, backHair[0].y, backHair[1].x, backHair[1].y, vBackhair[45].x, vBackhair[50].y);
		TextOut(hdc, 10, 10, text, strlen(text));

		Polygon(hdc, backHair, vBackhair.size());
	}

	void drawFrontHair(HDC hdc) {

	}

	void drawFace(HDC hdc) {

	}

	void drawHand(HDC hdc) {

	}

};
class Bye {

};