#include"FoePlaneMid.h"
#include"../GameConfig/GameConfig.h"
#include"../PlaneApp/PlaneApp.h"

CFoePlaneMid::CFoePlaneMid() {

}
CFoePlaneMid::~CFoePlaneMid() {

}

void CFoePlaneMid::InitFoe() {
	::loadimage(&m_imgFoe, "./res/foeplanemid.jpg");
	m_x = CPlaneApp::m_rand % (IMG_BACKGROUND_WIDTH - IMG_FOEMID_WIDTH);
	m_y = -IMG_FOEMID_HEIGHT;
	m_blood = DEF_FOEMID_BLOOD;
	m_showid = 3;
}
void CFoePlaneMid::ShowFoe() {
	::putimage(m_x, m_y, IMG_FOEMID_WIDTH, IMG_FOEMID_HEIGHT,
		&m_imgFoe, IMG_FOEMID_WIDTH, (3 - m_showid) * IMG_FOEMID_HEIGHT, SRCPAINT);  //œ»œ‘ æ∆¡±ŒÕº

	::putimage(m_x, m_y, IMG_FOEMID_WIDTH, IMG_FOEMID_HEIGHT,
		&m_imgFoe, 0, (3 - m_showid) * IMG_FOEMID_HEIGHT, SRCAND);
}
bool CFoePlaneMid::IsHitPlayer(CPlayerPlane& pPlayer) {
	int x = pPlayer.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOEMID_WIDTH && m_y <= pPlayer.m_y && pPlayer.m_y <= m_y + IMG_FOEMID_HEIGHT) {
		return true;
	}

	int y = pPlayer.m_y + IMG_PLAYER_HEIGHT * 2 / 3;
	if (m_x <= pPlayer.m_x && pPlayer.m_x <= m_x + IMG_FOEMID_WIDTH && m_y <= y && y <= m_y + IMG_FOEMID_HEIGHT) {
		return true;
	}

	int x1 = pPlayer.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOEMID_WIDTH && m_y <= y && y <= m_y + IMG_FOEMID_HEIGHT) {
		return true;
	}

	return false;
}
bool CFoePlaneMid::IsHitGunner(CGunner* pGun) {
	int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOEMID_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOEMID_HEIGHT) {
		return true;
	}
	return false;
}
