#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
private:
	friend class CObj;
	friend class CScene;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	int			m_iPlayerNumber;
	bool		m_bMove;
	DIR			m_eDir;
	float		m_fSpeed;
	int			m_iBubbles;
	int			m_iRange;

public:
	void SetMove(bool bMove)
	{
		m_bMove = bMove;
	}
	void SetDir(DIR eDir)
	{
		m_eDir = eDir;
	}
	void SetSpeed(bool fSpeed)
	{
		m_fSpeed = fSpeed;
	}
	void SetBubbles(bool iBubbles)
	{
		m_iBubbles = iBubbles;
	}
	void SetRange(bool iRange)
	{
		m_iRange = iRange;
	}

public:
	bool GetMove() const
	{
		return m_bMove;
	}
	DIR GetDir() const
	{
		return m_eDir;
	}
	float GetSpeed() const
	{
		return m_fSpeed;
	}
	int GetBubbles() const
	{
		return m_iBubbles;
	}
	int GetRange() const
	{
		return m_iRange;
	}

public:
	void Move(float x, float y, float fDeltaTime);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer* Clone();

};

