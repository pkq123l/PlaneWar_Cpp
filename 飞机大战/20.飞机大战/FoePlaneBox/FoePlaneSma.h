#pragma once
#include"FoePlane.h"

class CFoePlaneSma :public CFoePlane {
public:
	CFoePlaneSma();
	~CFoePlaneSma();
public:
	virtual void InitFoe();
	virtual void ShowFoe();
	virtual bool IsHitPlayer(CPlayerPlane& pPlayer);
	virtual bool IsHitGunner(CGunner* pGun);
};
