#include"GunnerBox.h"
#include "../GameConfig/GameConfig.h"


CGunnerBox::CGunnerBox() {

}
CGunnerBox::~CGunnerBox() {
	list <CGunner*> ::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			//回收炮弹
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();  //清空链表结点
}
void CGunnerBox::ShowAllGunner() {
	list <CGunner*> ::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			(*ite)->ShowGunner();
		}
		ite++;
	}
}
void CGunnerBox::MoveAllGunner(int step) {
	list <CGunner*> ::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			//移动所有的炮弹
			(*ite)->MoveGunner(step);
			//判断炮弹是否出界
			if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
				//出界，手动删除炮弹
				delete (*ite);
				(*ite) = nullptr;
				//删除对应的结点
				ite = m_lstGun.erase(ite);
				continue;
			}
		}
		ite++;
	}
}