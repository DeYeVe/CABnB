#pragma once

#include "UI.h"
class CUITimer :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	CUITimer();
	CUITimer(const CUITimer& ui);
	~CUITimer();

private:
	float m_fInGameTime;
	class CTexture* m_pMinute;
	class CTexture* m_pSecondTen;
	class CTexture* m_pSecondOne;

public:
	float GetInGameTime() const
	{
		return m_fInGameTime;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUITimer* Clone();

private:
	wstring StringToWstring(string str)
	{
		wstring wstr;
		wstr = wstring(str.begin(), str.end());

		return wstr;
	}
};

