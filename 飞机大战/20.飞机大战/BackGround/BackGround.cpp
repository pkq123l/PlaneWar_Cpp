#include"BackGround.h"
#include "../GameConfig/GameConfig.h"

CBackGround::CBackGround() {
	m_x = 0;
	m_y = 0;
}
CBackGround::~CBackGround() {

}

void CBackGround::InitBackGround() {
	::loadimage(&m_imgBack, "./res/±³¾°.jpg");
	m_x = 0;
	m_y = -IMG_BACKGROUND_HEIGHT;
}
void CBackGround::ShowBackGround() {
	::putimage(m_x, m_y, &m_imgBack);
}
void CBackGround::MoveBackGround(int step) {
	m_y += step;
	if (m_y >= 0) {
		m_y = -IMG_BACKGROUND_HEIGHT;
	}
}