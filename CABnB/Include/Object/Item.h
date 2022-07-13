#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	CItem(const CItem & itme);
	~CItem();

private:
	ITEM_TYPE		m_eType;
	float			m_fOffsetTime;
	int				m_iOffsetReverse;
	class CColliderRect*	m_pRC;

public:
	void SetItemType(ITEM_TYPE eType);
	ITEM_TYPE GetItemType() const
	{
		return m_eType;
	}


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CItem* Clone();
};

