#pragma once
#include "Obj.h"
#include "Bomb.h"

class CStream :
	public CObj
{

public:
	CStream();
	CStream(const CStream & stream);
	~CStream();

private:
	float			m_fLifeTime;
	int				m_iRange;
	class CStream*	m_pStream;
	DIR				m_eDir;
	bool			m_bIsSpread;
	bool			m_bIsCollided;

public:
	void SetLifeTime(float fLifeTime)
	{
		m_fLifeTime += fLifeTime;
	}
	float GetLifeTime() const
	{
		return m_fLifeTime;
	}

	void SetStream(CStream* stream)
	{
		m_pStream = stream;
	}
	CStream* GetStream() const
	{
		return m_pStream;
	}

	void SetRange(int range)
	{
		m_iRange = range;
	}
	int GetRange() const
	{
		return m_iRange;
	}

	void SetDir(DIR dir)
	{
		m_eDir = dir;
	}
	DIR GetDir() const
	{
		return m_eDir;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStream* Clone();

public:
	void Expand();
	void Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime);
};