#include "PlanePlane.h"
#include"../GameConfig/GameConfig.h"

CPlayerPlane::CPlayerPlane() {
	m_x = 0;
	m_y = 0;
}
CPlayerPlane::~CPlayerPlane() {

}


void CPlayerPlane::InitPlayer() {
	::loadimage(&m_imgPlayer, "./res/playerplane.jpg");
	::loadimage(&m_imgPlayerMask, "./res/playerplane-mask.jpg");
	m_x = (IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDTH) / 2;
	m_y = IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT;
}
void CPlayerPlane::ShowPlayer() {
	::putimage(m_x, m_y, &m_imgPlayerMask,SRCPAINT);  //屏蔽图和背景图做位或操作，SRCPAINT 位或
	::putimage(m_x, m_y, &m_imgPlayer,SRCAND);  //上一步的结果图图和玩家飞机原图做位与操作，SRCAND 位与
}
void CPlayerPlane::MovePlayer(int direct,int step) {
	switch (direct) {
	case VK_LEFT:
	{
		if (m_x - step >= 0) {
			m_x -= step;
		}
		else {
			m_x = 0;
		}
	}
	break;
	case VK_RIGHT:
	{
		if (m_x + step <= IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDTH) {
			m_x += step;
		}
		else {
			m_x = IMG_BACKGROUND_WIDTH - IMG_PLAYER_WIDTH;
		}
	}
	break;
	case VK_UP:
	{
		if (m_y - step >= 0) {
			m_y -= step;
		}
		else {
			m_y = 0;
		}
	}
	break;
	case VK_DOWN:
	{
		if (m_y + step <= IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT) {
			m_y += step;
		}
		else {
			m_y = IMG_BACKGROUND_HEIGHT - IMG_PLAYER_HEIGHT;
		}
	}
	break;

	}
}

CGunner* CPlayerPlane::SendGunner() {
	CGunner* pGun = new CGunner;

	int x = m_x + (IMG_PLAYER_WIDTH - IMG_GUNNER_WIDTH) / 2;
	int y = m_y - IMG_GUNNER_HEIGHT;
	pGun->InitGunner(x,y);

	return pGun;
}
