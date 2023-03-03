#pragma once
#include"../GameFrame/GameFrame.h"
#include"../BackGround/BackGround.h"
#include"../PlayerPlane/PlanePlane.h"
#include "../GunnerBox/GunnerBox.h"
#include "../FoePlaneBox/FoePlaneBox.h"

class CPlaneApp :public CGameFrame {
public:
	CBackGround m_back;;
	CPlayerPlane m_player;
	CGunnerBox m_gunBox;
	CFoePlaneBox m_foeBox;
	static int m_rand;
	IMAGE m_scoreBoard;
	int m_score;
public:
	CPlaneApp();
	~CPlaneApp();
public:
	virtual void On_Init();
	virtual void On_Paint();
	virtual void On_Close();

	virtual void On_WM_TIMER(WPARAM wParam, LPARAM lParam);
	virtual void On_WM_KEYDOWN(WPARAM wparam);
public:
	void SetTimer();
	void GameOver();
	void ShowScore();

};