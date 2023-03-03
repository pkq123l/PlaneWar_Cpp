#pragma once
#include<easyx.h>
#include"../GunnerBox/Gunner.h"

class CPlayerPlane {
public:
	IMAGE m_imgPlayer;
	IMAGE m_imgPlayerMask;  //ÆÁ±ÎÍ¼£¬ºÚ°×
	int m_x;
	int m_y;
public:
	CPlayerPlane();
	~CPlayerPlane();
public:
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(int direct,int step);

	CGunner* SendGunner();
};