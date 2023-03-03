#pragma once
#include<easyx.h>
#include<map>
using namespace std;

LRESULT Wndproc(HWND unnamedParam1,UINT unnamedParam2,WPARAM unnamedParam3,LPARAM unnamedParam4);

#define INIT_MSGMAP(MSG_ID,MSG_TYPE)\
m_msgMap[MSG_ID].msg_type = MSG_TYPE;\
m_msgMap[MSG_ID].p_fun_##MSG_TYPE = &CGameFrame::On_##MSG_ID;



//��װ��Ϸ�ǵ���
class CGameFrame {
private:
	//��Ԫ ��Wndproc ��CGameFrame�����ѣ���Wndproc ����ֱ��ʹ����˽�г�Ա
	friend LRESULT Wndproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);
	
	bool m_isQuit;   //�˳���ʶ


	typedef void (CGameFrame::*P_FUN_MOUSE)(POINT& );
	typedef void (CGameFrame::* P_FUN_WINDOW)(WPARAM, LPARAM);
	typedef void (CGameFrame::* P_FUN_KEY)(WPARAM );
	typedef void (CGameFrame::* P_FUN_CHAR)(WPARAM);
	/*
	#define EM_MOUSE	     1
	#define EM_KEY		     2
	#define EM_CHAR		     4
	#define EM_WINDOW	     8
	*/
	struct Fun_type {
		int msg_type;
		union {
			P_FUN_MOUSE  p_fun_EM_MOUSE;
			P_FUN_WINDOW p_fun_EM_WINDOW;
			P_FUN_KEY    p_fun_EM_KEY;
			P_FUN_CHAR   p_fun_EM_CHAR;
		};
	};

	map<UINT, Fun_type> m_msgMap;   //��Ϣӳ���
protected:
	HWND hWnd;       //���ھ���������ģ��������Ϸ��������ܻ��õ�

public:
	CGameFrame() {
		m_isQuit = false;  //��ʼ ���˳�
	}
	virtual ~CGameFrame() {}
	bool GetQuit() {
		return m_isQuit;
	}
	void InitMsgMap() {
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE)
		//INIT_MSGMAP(WM_CLOSE, EM_WINDOW)  //�����ȡ�����ͻ���ִ����Ѿ��ر��ˣ���Ȼ��ˢ�´���
		INIT_MSGMAP(WM_KEYDOWN, EM_KEY)
		INIT_MSGMAP(WM_CHAR, EM_CHAR)
		INIT_MSGMAP(WM_TIMER, EM_WINDOW)
		INIT_MSGMAP(WM_MOUSEMOVE, EM_MOUSE)
	}
public:
	//1. ��ʼ����Ϸ
	void InitGame(const TCHAR* title ,int width= 400,int height= 400, int x=500,int y= 100) {
		hWnd = ::initgraph(width, height);  //��ʼ����������
		::MoveWindow(hWnd, x, y, width, height, TRUE);   //�ƶ�ָ�����ڵ�һ��ָ��λ��
		::SetWindowText(hWnd, title);
		::setbkcolor(RGB(255, 255, 255));  //�趨һ��Ĭ�ϵı���ɫ
		::cleardevice();   //����
		
		//�����Ϣӳ���
		InitMsgMap();
		//todo: ������Ϸ�ĳ�ʼ��
		On_Init();

		//�趨���ڵ�����
		::SetWindowLong(hWnd, GWL_WNDPROC,(LONG)&Wndproc);  //�����趨���ڵĻص�����
	}

	//2. �ػ洰��
	void PaintGame() {
		::BeginBatchDraw();   //��ʼ�����ػ�
		//ÿ���ػ�֮ǰ ������һ�εĻ�ͼ�ۼ�����
		::cleardevice();  //����
		//todo: ������Ϸ����ʾ
		On_Paint();

		::EndBatchDraw();    //���������ػ�
	}

	//4. �ر���Ϸ
	void CloseGame() {
		On_Close();  //������Ϸ�ͷ���Դ
		::closegraph();   //�رմ���
		m_isQuit = true;  //��ʶ��Ϊfalse
	}
	void On_WM_CLOSE(WPARAM wParam, LPARAM lParam) {
		CloseGame();
	}

	//---------------------------------------------------------------
	// ������Ϸ��صĺ���,�䴿�麯����Ҫ������һ��Ҫ��д���������麯��
	virtual void On_Init() = 0;
	virtual void On_Paint() = 0;
	virtual void On_Close() = 0;

	virtual void On_WM_LBUTTONDOWN(POINT &po) {}
	virtual void On_WM_KEYDOWN(WPARAM wparam) {}
	virtual void On_WM_CHAR(WPARAM wparam) {}
	virtual void On_WM_TIMER(WPARAM wParam, LPARAM lParam) {}
	virtual void On_WM_MOUSEMOVE(POINT& po) {}
	
};


#define WND_PARAM(POS_X,POS_Y,WIDTH,HEIGHT,TITILE)\
	int WND_POS_X = POS_X;\
	int WND_POS_Y = POS_Y;\
	int WND_WIDTH  = WIDTH;\
	int WND_HEIGHT = HEIGHT;\
	const TCHAR* WND_TITLE = TITILE;

#define DYNAMIC_CAEATE(CLASS_OBJECT)\
	CGameFrame* CreateObject() {\
		return new CLASS_OBJECT;\
	}



/*
GameFrame.h  --  main.cpp
�����������̳и���CGameFrame����д���� ��3�����麯������Ҫ����ʵ��
On_Init()
On_Paint()
On_Close()
������Ҫ����Ϣ�������Ϣӳ����д��ڣ�����д��Ϣ��Ӧ�Ĵ�������
�����Ϣӳ������ڣ������ �� InitMsgMap ���һ����Ϣ�� �ڸ����������Ϣ��Ӧ�Ĵ�����,������д����麯��
�������Դ�ļ��У�ʹ��  WND_PARAM   ��DYNAMIC_CAEATE �꣬ ����Ӧ�Ĳ���





*/