#include "FoePlaneBox.h"
#include <typeinfo>
#include "FoePlaneBig.h"
#include "FoePlaneMid.h"
#include "FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"

CFoePlaneBox::CFoePlaneBox() {

}


#define DELETE_FOE_LIST(FOE_LIST)\
	list <CFoePlane*> ::iterator ite##FOE_LIST = FOE_LIST.begin();\
	while (ite##FOE_LIST != FOE_LIST.end()) {\
		if (*ite##FOE_LIST) {\
			delete (*ite##FOE_LIST);\
			(*ite##FOE_LIST) = nullptr;\
		}\
		ite##FOE_LIST++;\
	}\
	FOE_LIST.clear();

CFoePlaneBox::~CFoePlaneBox() {
	/*
	list <CFoePlane*> ::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end()) {
		if (*ite) {
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstFoe.clear();
	*/
	
	DELETE_FOE_LIST(m_lstFoe)
	DELETE_FOE_LIST(m_lstFoeBoom)
}

void CFoePlaneBox::ShowAlllFoe() {
	list <CFoePlane*> ::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end()) {
		if (*ite) {
			(*ite)->ShowFoe();
		}
		ite++;
	}
}
void CFoePlaneBox::ShowAllBoomFoe() {
	list <CFoePlane*> ::iterator ite = m_lstFoeBoom.begin();
	while (ite != m_lstFoeBoom.end()) {
		if (*ite) {
			(*ite)->ShowFoe();
		}
		ite++;
	}
}
void CFoePlaneBox::MoveAllFoe() {
	list <CFoePlane*> ::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end()) {
		if (*ite) {
			//运行时类型识别：RTTI（Run Time Type Id）
			if (typeid(**ite) == typeid(CFoePlaneBig)) {
				(*ite)->MoveFoe(TIMER_FOEBIG_MOVE_STEP);
			}
			else if (typeid(**ite) == typeid(CFoePlaneMid)) {
				(*ite)->MoveFoe(TIMER_FOEMID_MOVE_STEP);
			}
			else if (typeid(**ite) == typeid(CFoePlaneSma)) {
				(*ite)->MoveFoe(TIMER_FOESMA_MOVE_STEP);
			}
			//判断敌人飞机是否出界
			if ((*ite)->m_y > IMG_BACKGROUND_HEIGHT) {
				delete (*ite);
				(*ite) = nullptr;

				ite = m_lstFoe.erase(ite);
				continue;
			}

		}
		ite++;
	}
}