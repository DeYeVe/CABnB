#pragma once
#include "Collider.h"

class CColliderPoint :
	public CCollider
{
protected:
	friend class CObj;

public:
	CColliderPoint();
	CColliderPoint(const CColliderPoint& coll);
	virtual ~CColliderPoint();

protected:
	POSITION	m_tDist;
	POSITION	m_tPos;

public:
	POSITION GetPoint() const
	{
		return m_tPos;
	}

public:
	void SetDistance(float x, float y)
	{
		m_tDist.x = x;
		m_tDist.y = y;
	}

	void SetDistance(const POSITION& tDist)
	{
		m_tDist = tDist;
	}

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderPoint* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

