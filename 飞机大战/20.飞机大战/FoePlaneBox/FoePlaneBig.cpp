#include"FoePlaneBig.h"
#include"../GameConfig/GameConfig.h"
#include"../PlaneApp/PlaneApp.h"

CFoePlaneBig::CFoePlaneBig() {

}
CFoePlaneBig::~CFoePlaneBig() {

}

void CFoePlaneBig::InitFoe() {
	::loadimage(&m_imgFoe, "./res/foeplanebig.jpg");
	m_x = CPlaneApp::m_rand % (IMG_BACKGROUND_WIDTH- IMG_FOEBIG_WIDTH);
	m_y = -IMG_FOEBIG_HEIGHT;
	m_blood = DEF_FOEBIG_BLOOD;
	m_showid = 4;
}
void CFoePlaneBig::ShowFoe() {
	::putimage(m_x, m_y, IMG_FOEBIG_WIDTH, IMG_FOEBIG_HEIGHT,
		&m_imgFoe, IMG_FOEBIG_WIDTH, (4 - m_showid) * IMG_FOEBIG_HEIGHT,SRCPAINT);  //œ»œ‘ æ∆¡±ŒÕº

	::putimage(m_x, m_y, IMG_FOEBIG_WIDTH, IMG_FOEBIG_HEIGHT,
		&m_imgFoe, 0, (4 - m_showid) * IMG_FOEBIG_HEIGHT, SRCAND);  
}
bool CFoePlaneBig::IsHitPlayer(CPlayerPlane& pPlayer) {
	int x = pPlayer.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOEBIG_WIDTH && m_y <= pPlayer.m_y && pPlayer.m_y <= m_y + IMG_FOEBIG_HEIGHT) {
		return true;
	}

	int y = pPlayer.m_y + IMG_PLAYER_HEIGHT * 2/3;
	if (m_x <= pPlayer.m_x && pPlayer.m_x <= m_x + IMG_FOEBIG_WIDTH && m_y <= y && y <= m_y + IMG_FOEBIG_HEIGHT) {
		return true;
	}
	
	int x1 = pPlayer.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOEBIG_WIDTH && m_y <= y && y <= m_y + IMG_FOEBIG_HEIGHT) {
		return true;
	}

	return false;
}
bool CFoePlaneBig::IsHitGunner(CGunner* pGun) {
	int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOEBIG_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOEBIG_HEIGHT) {
		return true;
	}


	return false;
}
