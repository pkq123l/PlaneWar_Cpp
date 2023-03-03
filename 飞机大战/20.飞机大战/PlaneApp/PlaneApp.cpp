#include "PlaneApp.h"
#include "../GameConfig/GameConfig.h"
#include<time.h>
#include"../FoePlaneBox/FoePlane.h"
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"
#include <string>
using namespace std;

WND_PARAM(WND_X, WND_Y, WND_GAME_WIDTH, WND_GAME_HEIGHT, WND_GAME_TITLE)
DYNAMIC_CAEATE(CPlaneApp)

CPlaneApp::CPlaneApp() {

}
CPlaneApp::~CPlaneApp() {

}

void CPlaneApp::On_Init(){
	srand((unsigned int)time(NULL));  //�����������

	m_score = 0;
	::loadimage(&m_scoreBoard, "./res/cardboard.png");

	//�����ĳ�ʼ��
	m_back.InitBackGround();
	//��ҷɻ��ĳ�ʼ��
	m_player.InitPlayer();
	
	//�������Եļ�ʱ��
	SetTimer();
}

void CPlaneApp::SetTimer() {
	//�趨�����ƶ��Ķ�ʱ��
	::SetTimer(hWnd, TIMER_BACKGROUND_MOVE_TIMERID, TIMER_BACKGROUND_MOVE_INTERVAL, nullptr);
	//��ʱ��ⷽ����Ƿ���
	::SetTimer(hWnd, TIMER_PLAYER_CHECKMOVE_TIMERID, TIMER_PLAYER_CHECKMOVE_INTERVAL, nullptr);

	//��ʱ�����ڵ�
	::SetTimer(hWnd, TIMER_SEND_GUNNER_TIMERID, TIMER_SEND_GUNNER_INTERVAL, nullptr);
	//��ʱ�ƶ��ڵ�
	::SetTimer(hWnd, TIMER_GUNNER_MOVE_TIMERID, TIMER_GUNNER_MOVE_INTERVAL, nullptr);

	//��ʱ�������˷ɻ��Ķ�ʱ��
	::SetTimer(hWnd, TIMER_CREAT_FOEBIG_TIMERID, TIMER_CREAT_FOEBIG_INTERVAL, nullptr);
	::SetTimer(hWnd, TIMER_CREAT_FOEMID_TIMERID, TIMER_CREAT_FOEMID_INTERVAL, nullptr);
	::SetTimer(hWnd, TIMER_CREAT_FOESMA_TIMERID, TIMER_CREAT_FOESMA_INTERVAL, nullptr);

	//���˷ɻ������ƶ�
	::SetTimer(hWnd, TIMER_FOEPLAEN_TIMERID, TIMER_FOEPLAEN_INTERVAL, nullptr);

	//��ʱ����Ƿ���ײ
	::SetTimer(hWnd, TIMER_CHECK_HIT_TIMERID, TIMER_CHECK_HIT_INTERVAL, nullptr);

	//��ʱ�л���ըЧ��ͼƬ
	::SetTimer(hWnd, TIMER_CHANGE_BOOM_TIMERID, TIMER_CHANGE_BOOM_INTERVAL, nullptr);
}

int CPlaneApp::m_rand = 0;  //��̬��Ա��ʼ��
void CPlaneApp::On_Paint() {
	CPlaneApp::m_rand = rand();

	//��ʾ����ͼ
	m_back.ShowBackGround();
	//��ʾ��ҷɻ�
	m_player.ShowPlayer();
	//��ʾ���е��ڵ�
	m_gunBox.ShowAllGunner();
	//��ʾ���ез��ɻ�
	m_foeBox.ShowAlllFoe();
	//��ʾ���б�ը�ĵз��ɻ�
	m_foeBox.ShowAllBoomFoe();

	//��ʾ����
	ShowScore();
}

void CPlaneApp::On_Close() {

}


#define CREATE_FOEPLANE(FOE_CLASS)\
	CFoePlane* pFoe = new FOE_CLASS;\
	pFoe->InitFoe();\
	m_foeBox.m_lstFoe.push_back(pFoe);

void CPlaneApp::On_WM_TIMER(WPARAM wParam, LPARAM lParam) {
	switch (wParam) {
	case TIMER_BACKGROUND_MOVE_TIMERID:  //�����ƶ��Ķ�ʱ��
	{
		m_back.MoveBackGround(TIMER_BACKGROUND_MOVE_STEP);
	}
	break;
	case TIMER_PLAYER_CHECKMOVE_TIMERID:  //��ʱ��ⷽ����Ƿ���
	{
		if (GetAsyncKeyState(VK_LEFT)) {  //�ж�ĳ��������Ƿ��ǰ��µ�״̬
			m_player.MovePlayer(VK_LEFT, TIMER_PLAYER_MOVE_STEP);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			m_player.MovePlayer(VK_RIGHT, TIMER_PLAYER_MOVE_STEP);
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_player.MovePlayer(VK_UP, TIMER_PLAYER_MOVE_STEP);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			m_player.MovePlayer(VK_DOWN, TIMER_PLAYER_MOVE_STEP);
		}
	}
	break;
	case TIMER_SEND_GUNNER_TIMERID:  //��ʱ�����ڵ�
	{
		//�������ڵ��ŵ��ڵ����ӵ�������
		CGunner * pGun = m_player.SendGunner();
		m_gunBox.m_lstGun.push_back(pGun);
	}
	break;
	case TIMER_GUNNER_MOVE_TIMERID:  //��ʱ�ƶ��ڵ�
	{
		m_gunBox.MoveAllGunner(TIMER_GUNNER_MOVE_STEP);
	}
	break;
	case TIMER_CREAT_FOEBIG_TIMERID:  
	{
		CREATE_FOEPLANE(CFoePlaneBig);
	}
	break;
	case TIMER_CREAT_FOEMID_TIMERID: 
	{
		CREATE_FOEPLANE(CFoePlaneMid);
	}
	break;
	case TIMER_CREAT_FOESMA_TIMERID:  
	{
		CREATE_FOEPLANE(CFoePlaneSma);
	}
	break;
	case TIMER_FOEPLAEN_TIMERID: 
	{
		m_foeBox.MoveAllFoe();
	}
	break;
	case TIMER_CHECK_HIT_TIMERID:
	{
		bool isBoom = false;  //�Ƿ�ը�ı�־
		//�������еĵз��ɻ�
		list <CFoePlane*> ::iterator iteFoe = m_foeBox.m_lstFoe.begin();
		while (iteFoe != m_foeBox.m_lstFoe.end()) {
			//1.�ж��Ƿ�ײ����ҷɻ������ײ�� gameover
			if (*iteFoe) {
				if ((*iteFoe)->IsHitPlayer(m_player)) {
					GameOver();
					return;
				}
			}

			//2.�ж��Ƿ�ײ���ڵ���ѭ�������ڵ�
			list <CGunner*> ::iterator iteGun = m_gunBox.m_lstGun.begin();
			while (iteGun != m_gunBox.m_lstGun.end()) {
				if (*iteGun) {
					//�жϵ��˷ɻ��Ƿ�ײ�����ڵ�
					if ((*iteFoe)->IsHitGunner((*iteGun))) {
						//ɾ���ڵ�
						delete (*iteGun);
						(*iteGun) = nullptr;
						//ɾ���ڵ����ӽ��
						iteGun = m_gunBox.m_lstGun.erase(iteGun);

						//���˷ɻ���Ѫ
						(*iteFoe)->m_blood -= DEF_GUNNER_HURT;  //���˷ɻ���Ѫ
						if ((*iteFoe)->m_blood <= 0) {
							m_foeBox.m_lstFoeBoom.push_back((*iteFoe));  //����ը�ķɻ����뵽��ը��������

							iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);
							isBoom = true;
							m_score += 3;
							break;
						}
						continue;
					}
				}
				iteGun++;
			}
			if (!isBoom)
				iteFoe++;
			else
				isBoom = false;
		}
	}
	break;
	case TIMER_CHANGE_BOOM_TIMERID:
	{
		list <CFoePlane*> :: iterator ite = m_foeBox.m_lstFoeBoom.begin();
		while (ite != m_foeBox.m_lstFoeBoom.end()) {
			if (*ite) {
				(*ite)->m_showid--;
				if ((*ite)->m_showid < 0) {  //Ϊ����ʾ���һ�ű�ըЧ��ͼ
					//ɾ�����˱�ը�ķɻ�
					delete (*ite);
					(*ite) = nullptr;
					//ɾ��������
					ite = m_foeBox.m_lstFoeBoom.erase(ite);
					continue;
				}
			}
			ite++;
		}
	}
	break;

	}
}
void CPlaneApp::On_WM_KEYDOWN(WPARAM wparam) {
	//m_player.MovePlayer(wparam, TIMER_PLAYER_MOVE_STEP);
}

void CPlaneApp::GameOver() {
	//ֹͣ���еĶ�ʱ��
	::KillTimer(hWnd, TIMER_BACKGROUND_MOVE_TIMERID);
	::KillTimer(hWnd, TIMER_PLAYER_CHECKMOVE_TIMERID);
	::KillTimer(hWnd, TIMER_SEND_GUNNER_TIMERID);
	::KillTimer(hWnd, TIMER_GUNNER_MOVE_TIMERID);
	::KillTimer(hWnd, TIMER_CREAT_FOEBIG_TIMERID);
	::KillTimer(hWnd, TIMER_CREAT_FOEMID_TIMERID);
	::KillTimer(hWnd, TIMER_CREAT_FOESMA_TIMERID);
	::KillTimer(hWnd, TIMER_FOEPLAEN_TIMERID);
	::KillTimer(hWnd, TIMER_CHECK_HIT_TIMERID);
	::KillTimer(hWnd, TIMER_CHANGE_BOOM_TIMERID);

	::MessageBox(hWnd, "GameOver", "��ʾ", MB_OK);  //������ʾ��

	//����Ϣ���з���һ����Ϣ WM_CLOSE
	::PostMessage(hWnd, WM_CLOSE, 0, 0);
}

void CPlaneApp::ShowScore() {
	string strScore("���� = ");
	char sc[5] = { 0 };
	_itoa_s(m_score, sc, 10);
	strScore += sc;

	RECT rect = { 0,0,186,60 };

	::settextcolor(RGB(255, 0, 0));
	::putimage(0, 0, &m_scoreBoard);
	::drawtext(strScore.c_str(), &rect, DT_CENTER);
	
}


