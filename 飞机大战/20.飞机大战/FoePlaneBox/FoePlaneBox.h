#pragma once
#include <list>
using namespace std;
#include"FoePlane.h"

class CFoePlaneBox {
public:
	list <CFoePlane*> m_lstFoe;
	list <CFoePlane*> m_lstFoeBoom;
public:
	CFoePlaneBox();
	~CFoePlaneBox();
public:
	void ShowAlllFoe();
	void ShowAllBoomFoe();
	void MoveAllFoe();


};