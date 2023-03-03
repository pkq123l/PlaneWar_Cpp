#pragma once
#include"FoePlane.h"

class CFoePlaneBig :public CFoePlane {
public:
	CFoePlaneBig();
	~CFoePlaneBig();
public:
	virtual void InitFoe();
	virtual void ShowFoe();
	virtual bool IsHitPlayer(CPlayerPlane& pPlayer);
	virtual bool IsHitGunner(CGunner* pGun);
};

