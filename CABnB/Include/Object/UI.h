#pragma once
#include "Obj.h"
class CUI :
	public CObj
{
protected:
	CUI();
	CUI(const CUI& ui);
	virtual ~CUI() = 0;

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUI* Clone() = 0;
};
 
