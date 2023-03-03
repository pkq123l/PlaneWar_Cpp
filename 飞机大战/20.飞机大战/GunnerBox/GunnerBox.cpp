#include"GunnerBox.h"
#include "../GameConfig/GameConfig.h"


CGunnerBox::CGunnerBox() {

}
CGunnerBox::~CGunnerBox() {
	list <CGunner*> ::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			//�����ڵ�
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();  //���������
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
			//�ƶ����е��ڵ�
			(*ite)->MoveGunner(step);
			//�ж��ڵ��Ƿ����
			if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
				//���磬�ֶ�ɾ���ڵ�
				delete (*ite);
				(*ite) = nullptr;
				//ɾ����Ӧ�Ľ��
				ite = m_lstGun.erase(ite);
				continue;
			}
		}
		ite++;
	}
}