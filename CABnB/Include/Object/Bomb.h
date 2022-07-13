#pragma once
#include "Obj.h"
#include "Player.h"

class CBomb :
	public CObj
{

public:
	CBomb();
	CBomb(const CBomb & bomb);
	~CBomb();

private:
	float			m_fLifeTime;
	int				m_iRange;
	class CPlayer*	m_pPlayer;

public:
	void SetLifeTime(float fLifeTime)
	{
		m_fLifeTime += fLifeTime;
	}
	float GetLifeTime() const
	{
		return m_fLifeTime;
	}

	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}
	CPlayer* GetPlayer() const
	{
		return m_pPlayer;
	}

	void SetRange(int range)
	{
		m_iRange = range;
	}
	int GetRange() const
	{
		return m_iRange;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBomb* Clone();

public:
	void Explosion();
};