
#pragma once
#include "UI.h"
class CUIMessage :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	CUIMessage();
	CUIMessage(const CUIMessage& ui);
	~CUIMessage();

private:
	float m_fUILifeTime;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIMessage* Clone();
};

