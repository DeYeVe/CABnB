#pragma once

#include "../Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();

public:
	~CLayer();

private:
	class CScene*	m_pScene;
	string		m_strTag;
	int			m_iZOrder;
	list<class CObj*>	m_ObjList;
	bool		m_bEnable;
	bool		m_bLife;

public:
	void SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}

	void Die()
	{
		m_bLife = false;
	}

	bool GetEnable()	const
	{
		return m_bEnable;
	}

	bool GetLife()	const
	{
		return m_bLife;
	}

public:
	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}


	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	string GetTag() const
	{
		return m_strTag;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

	CScene* GetSCene()	const
	{
		return m_pScene;
	}

public:
	void AddObject(class CObj* pObj);

public:
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
};


