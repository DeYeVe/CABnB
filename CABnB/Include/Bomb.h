#pragma once
#include "Object/Obj.h"
class CBomb :
	public CObj
{

public:
	CBomb();
	CBomb(const CBomb & block);
	~CBomb();

private:
	float		m_fLifeTime;

public:
	void SetLifeTile(float fLifeTime)
	{
		m_fLifeTime += fLifeTime;
	}
	float GetLifeTime() const
	{
		return m_fLifeTime;
	}


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBomb* Clone();
};