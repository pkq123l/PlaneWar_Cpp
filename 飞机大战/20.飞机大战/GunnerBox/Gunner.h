#pragma once
#include <easyx.h>

class CGunner {
public:
	IMAGE m_imgGun;
	int m_x;
	int m_y;
public:
	CGunner();
	~CGunner();
public:
	void InitGunner(int x, int y);
	void ShowGunner();
	void MoveGunner(int step);

};