#include<windowsx.h>
#include"GameFrame.h"

CGameFrame* pGame = nullptr;

// 3. ��Ϸ����
// msgid  Я���Ĳ���  WPARAM wparam, LPARAM lparam
LRESULT Wndproc(HWND hwnd, UINT msgid, WPARAM wparam, LPARAM lparam) {
	
	//if (msgid == WM_LBUTTONDOWN) {  //�������������
	//	POINT po = { 0 };
	//	/*po.x = msg.x;
	//	po.y = msg.y;*/
	//	po.x = GET_X_LPARAM(lparam);
	//	po.y = GET_Y_LPARAM(lparam);

	//	pGame->On_WM_LBUTTONDOWN(po);

	//}
	//if (msgid == WM_CLOSE) {
	//	pGame->CloseGame();
	//}

	if (pGame->m_msgMap.count(msgid)) {  //���key���ڣ��ܴ�����Ϣ
		switch (pGame->m_msgMap[msgid].msg_type)
		{
		case EM_MOUSE:
		{
			POINT po = { 0 };
			/*po.x = msg.x;
			po.y = msg.y;*/
			po.x = GET_X_LPARAM(lparam);
			po.y = GET_Y_LPARAM(lparam);
			(pGame->*(pGame->m_msgMap[msgid].p_fun_EM_MOUSE))(po);
		}
		break;
		case EM_WINDOW:
		{
			(pGame->*(pGame->m_msgMap[msgid].p_fun_EM_WINDOW))(wparam,lparam);
		}
		break;
		case EM_KEY:
		{
			(pGame->*(pGame->m_msgMap[msgid].p_fun_EM_KEY))(wparam);
		}
		break;
		case EM_CHAR:
		{
			(pGame->*(pGame->m_msgMap[msgid].p_fun_EM_CHAR))(wparam);
		}
		break;
		}
		//�κ���Ϣ�����꣬ˢ�´���
		pGame->PaintGame();
	}

	//���ڹرյ���Ϣ�ó�����������
	if (msgid == WM_CLOSE) {
		pGame->On_WM_CLOSE(wparam, lparam);
	}

	return DefWindowProc(hwnd, msgid, wparam, lparam);
}

CGameFrame* CreateObject();
extern int WND_POS_X ;
extern int WND_POS_Y ;
extern int WND_WIDTH ;
extern int WND_HEIGHT;
extern const TCHAR* WND_TITLE;

int main() {
	pGame = CreateObject();
	pGame->InitGame(WND_TITLE,WND_WIDTH, WND_HEIGHT, WND_POS_X, WND_POS_Y);
	pGame->PaintGame();

	while (!pGame->GetQuit()) {
	
		Sleep(200);
	}


	//������Դ
	delete pGame;
	pGame = nullptr;

	return 0;
}