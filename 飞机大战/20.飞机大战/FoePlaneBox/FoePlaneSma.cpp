#include"FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"
#include"../PlaneApp/PlaneApp.h"

CFoePlaneSma::CFoePlaneSma() {

}
CFoePlaneSma::~CFoePlaneSma() {

}

void CFoePlaneSma::InitFoe() {
	::loadimage(&m_imgFoe, "./res/foeplanesma.jpg");
	m_x = CPlaneApp::m_rand % (IMG_BACKGROUND_WIDTH - IMG_FOESMA_WIDTH);
	m_y = -IMG_FOESMA_HEIGHT;
	m_blood = DEF_FOESMA_BLOOD;
	m_showid = 2;
}
void CFoePlaneSma::ShowFoe() {
	::putimage(m_x, m_y, IMG_FOESMA_WIDTH, IMG_FOESMA_HEIGHT,
		&m_imgFoe, IMG_FOESMA_WIDTH, (2 - m_showid) * IMG_FOESMA_HEIGHT, SRCPAINT);  //œ»œ‘ æ∆¡±ŒÕº

	::putimage(m_x, m_y, IMG_FOESMA_WIDTH, IMG_FOESMA_HEIGHT,
		&m_imgFoe, 0, (2 - m_showid) * IMG_FOESMA_HEIGHT, SRCAND);
}
bool CFoePlaneSma::IsHitPlayer(CPlayerPlane& pPlayer) {
	int x = pPlayer.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOESMA_WIDTH && m_y <= pPlayer.m_y && pPlayer.m_y <= m_y + IMG_FOESMA_HEIGHT) {
		return true;
	}

	int y = pPlayer.m_y + IMG_PLAYER_HEIGHT * 2 / 3;
	if (m_x <= pPlayer.m_x && pPlayer.m_x <= m_x + IMG_FOESMA_WIDTH && m_y <= y && y <= m_y + IMG_FOESMA_HEIGHT) {
		return true;
	}

	int x1 = pPlayer.m_x + IMG_PLAYER_WIDTH;
	if (m_x <= x1 && x1 <= m_x + IMG_FOESMA_WIDTH && m_y <= y && y <= m_y + IMG_FOESMA_HEIGHT) {
		return true;
	}
	return false;
}
bool CFoePlaneSma::IsHitGunner(CGunner* pGun) {
	int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
	if (m_x <= x && x <= m_x + IMG_FOESMA_WIDTH && m_y <= pGun->m_y && pGun->m_y <= m_y + IMG_FOESMA_HEIGHT) {
		return true;
	}

	return false;
}
