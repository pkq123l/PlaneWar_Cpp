#pragma once
#include<easyx.h>
#include<map>
using namespace std;

LRESULT Wndproc(HWND unnamedParam1,UINT unnamedParam2,WPARAM unnamedParam3,LPARAM unnamedParam4);

#define INIT_MSGMAP(MSG_ID,MSG_TYPE)\
m_msgMap[MSG_ID].msg_type = MSG_TYPE;\
m_msgMap[MSG_ID].p_fun_##MSG_TYPE = &CGameFrame::On_##MSG_ID;



//封装游戏壳的类
class CGameFrame {
private:
	//友元 ：Wndproc 是CGameFrame的朋友，在Wndproc 可以直接使用其私有成员
	friend LRESULT Wndproc(HWND unnamedParam1, UINT unnamedParam2, WPARAM unnamedParam3, LPARAM unnamedParam4);
	
	bool m_isQuit;   //退出标识


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

	map<UINT, Fun_type> m_msgMap;   //消息映射表
protected:
	HWND hWnd;       //窗口句柄，将来的（具体的游戏）子类可能会用到

public:
	CGameFrame() {
		m_isQuit = false;  //开始 不退出
	}
	virtual ~CGameFrame() {}
	bool GetQuit() {
		return m_isQuit;
	}
	void InitMsgMap() {
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE)
		//INIT_MSGMAP(WM_CLOSE, EM_WINDOW)  //如果不取消，就会出现窗口已经关闭了，仍然会刷新窗口
		INIT_MSGMAP(WM_KEYDOWN, EM_KEY)
		INIT_MSGMAP(WM_CHAR, EM_CHAR)
		INIT_MSGMAP(WM_TIMER, EM_WINDOW)
		INIT_MSGMAP(WM_MOUSEMOVE, EM_MOUSE)
	}
public:
	//1. 初始化游戏
	void InitGame(const TCHAR* title ,int width= 400,int height= 400, int x=500,int y= 100) {
		hWnd = ::initgraph(width, height);  //初始化创建窗口
		::MoveWindow(hWnd, x, y, width, height, TRUE);   //移动指定窗口到一个指定位置
		::SetWindowText(hWnd, title);
		::setbkcolor(RGB(255, 255, 255));  //设定一个默认的背景色
		::cleardevice();   //清屏
		
		//添加消息映射表
		InitMsgMap();
		//todo: 具体游戏的初始化
		On_Init();

		//设定窗口的属性
		::SetWindowLong(hWnd, GWL_WNDPROC,(LONG)&Wndproc);  //重新设定窗口的回调函数
	}

	//2. 重绘窗口
	void PaintGame() {
		::BeginBatchDraw();   //开始批量重绘
		//每次重回之前 ，吧上一次的绘图痕迹擦除
		::cleardevice();  //清屏
		//todo: 具体游戏的显示
		On_Paint();

		::EndBatchDraw();    //结束批量重绘
	}

	//4. 关闭游戏
	void CloseGame() {
		On_Close();  //具体游戏释放资源
		::closegraph();   //关闭窗口
		m_isQuit = true;  //标识置为false
	}
	void On_WM_CLOSE(WPARAM wParam, LPARAM lParam) {
		CloseGame();
	}

	//---------------------------------------------------------------
	// 具体游戏相关的函数,变纯虚函数，要求子类一定要重写这三个纯虚函数
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
定义子类对象继承父类CGameFrame，重写父类 的3个纯虚函数，且要定义实现
On_Init()
On_Paint()
On_Close()
对于需要的消息、如果消息映射表中存在，则重写消息对应的处理函数，
如果消息映射表不存在，则添加 ， InitMsgMap 添加一条消息和 在父类中添加消息对应的处理函数,子类重写这个虚函数
在子类的源文件中，使用  WND_PARAM   ，DYNAMIC_CAEATE 宏， 传对应的参数





*/