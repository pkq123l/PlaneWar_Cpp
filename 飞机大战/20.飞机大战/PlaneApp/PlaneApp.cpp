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
	srand((unsigned int)time(NULL));  //设置随机种子

	m_score = 0;
	::loadimage(&m_scoreBoard, "./res/cardboard.png");

	//背景的初始化
	m_back.InitBackGround();
	//玩家飞机的初始化
	m_player.InitPlayer();
	
	//启动所以的计时器
	SetTimer();
}

void CPlaneApp::SetTimer() {
	//设定背景移动的定时器
	::SetTimer(hWnd, TIMER_BACKGROUND_MOVE_TIMERID, TIMER_BACKGROUND_MOVE_INTERVAL, nullptr);
	//定时检测方向键是否按下
	::SetTimer(hWnd, TIMER_PLAYER_CHECKMOVE_TIMERID, TIMER_PLAYER_CHECKMOVE_INTERVAL, nullptr);

	//定时发射炮弹
	::SetTimer(hWnd, TIMER_SEND_GUNNER_TIMERID, TIMER_SEND_GUNNER_INTERVAL, nullptr);
	//定时移动炮弹
	::SetTimer(hWnd, TIMER_GUNNER_MOVE_TIMERID, TIMER_GUNNER_MOVE_INTERVAL, nullptr);

	//定时创建敌人飞机的定时器
	::SetTimer(hWnd, TIMER_CREAT_FOEBIG_TIMERID, TIMER_CREAT_FOEBIG_INTERVAL, nullptr);
	::SetTimer(hWnd, TIMER_CREAT_FOEMID_TIMERID, TIMER_CREAT_FOEMID_INTERVAL, nullptr);
	::SetTimer(hWnd, TIMER_CREAT_FOESMA_TIMERID, TIMER_CREAT_FOESMA_INTERVAL, nullptr);

	//敌人飞机定向移动
	::SetTimer(hWnd, TIMER_FOEPLAEN_TIMERID, TIMER_FOEPLAEN_INTERVAL, nullptr);

	//定时检测是否碰撞
	::SetTimer(hWnd, TIMER_CHECK_HIT_TIMERID, TIMER_CHECK_HIT_INTERVAL, nullptr);

	//定时切换爆炸效果图片
	::SetTimer(hWnd, TIMER_CHANGE_BOOM_TIMERID, TIMER_CHANGE_BOOM_INTERVAL, nullptr);
}

int CPlaneApp::m_rand = 0;  //静态成员初始化
void CPlaneApp::On_Paint() {
	CPlaneApp::m_rand = rand();

	//显示背景图
	m_back.ShowBackGround();
	//显示玩家飞机
	m_player.ShowPlayer();
	//显示所有的炮弹
	m_gunBox.ShowAllGunner();
	//显示所有敌方飞机
	m_foeBox.ShowAlllFoe();
	//显示所有爆炸的敌方飞机
	m_foeBox.ShowAllBoomFoe();

	//显示分数
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
	case TIMER_BACKGROUND_MOVE_TIMERID:  //背景移动的定时器
	{
		m_back.MoveBackGround(TIMER_BACKGROUND_MOVE_STEP);
	}
	break;
	case TIMER_PLAYER_CHECKMOVE_TIMERID:  //定时检测方向键是否按下
	{
		if (GetAsyncKeyState(VK_LEFT)) {  //判断某个方向键是否是按下的状态
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
	case TIMER_SEND_GUNNER_TIMERID:  //定时发射炮弹
	{
		//发射完炮弹放到炮弹盒子的链表中
		CGunner * pGun = m_player.SendGunner();
		m_gunBox.m_lstGun.push_back(pGun);
	}
	break;
	case TIMER_GUNNER_MOVE_TIMERID:  //定时移动炮弹
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
		bool isBoom = false;  //是否爆炸的标志
		//遍历所有的敌方飞机
		list <CFoePlane*> ::iterator iteFoe = m_foeBox.m_lstFoe.begin();
		while (iteFoe != m_foeBox.m_lstFoe.end()) {
			//1.判断是否撞击玩家飞机：如果撞击 gameover
			if (*iteFoe) {
				if ((*iteFoe)->IsHitPlayer(m_player)) {
					GameOver();
					return;
				}
			}

			//2.判断是否撞击炮弹：循环遍历炮弹
			list <CGunner*> ::iterator iteGun = m_gunBox.m_lstGun.begin();
			while (iteGun != m_gunBox.m_lstGun.end()) {
				if (*iteGun) {
					//判断敌人飞机是否撞击了炮弹
					if ((*iteFoe)->IsHitGunner((*iteGun))) {
						//删除炮弹
						delete (*iteGun);
						(*iteGun) = nullptr;
						//删除炮弹连接结点
						iteGun = m_gunBox.m_lstGun.erase(iteGun);

						//敌人飞机掉血
						(*iteFoe)->m_blood -= DEF_GUNNER_HURT;  //敌人飞机掉血
						if ((*iteFoe)->m_blood <= 0) {
							m_foeBox.m_lstFoeBoom.push_back((*iteFoe));  //将爆炸的飞机加入到爆炸的链表中

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
				if ((*ite)->m_showid < 0) {  //为了显示最后一张爆炸效果图
					//删除敌人爆炸的飞机
					delete (*ite);
					(*ite) = nullptr;
					//删除链表结点
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
	//停止所有的定时器
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

	::MessageBox(hWnd, "GameOver", "提示", MB_OK);  //弹出提示框

	//给消息队列发送一个消息 WM_CLOSE
	::PostMessage(hWnd, WM_CLOSE, 0, 0);
}

void CPlaneApp::ShowScore() {
	string strScore("分数 = ");
	char sc[5] = { 0 };
	_itoa_s(m_score, sc, 10);
	strScore += sc;

	RECT rect = { 0,0,186,60 };

	::settextcolor(RGB(255, 0, 0));
	::putimage(0, 0, &m_scoreBoard);
	::drawtext(strScore.c_str(), &rect, DT_CENTER);
	
}


