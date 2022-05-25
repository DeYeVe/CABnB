#pragma once
#include "UI.h"
class CMouse :
	public CUI
{
private:
	friend class CObj;
	friend class CScene;

private:
	CMouse();
	CMouse(const CMouse& mouse);
	~CMouse();

private:
	POSITION	m_tMove;
	POSITION	m_tWorldPos;

public:
	POSITION GetMove() const
	{
		return m_tMove;
	}

	POSITION GetWorldPos() const
	{
		return m_tWorldPos;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMouse* Clone();

public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
};

