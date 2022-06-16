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
	int			m_iBomb;
	int			m_iRange;

private:
	vector<string> m_strArrowKeys;

public:
	void SetMove(bool bMove)
	{
		m_bMove = bMove;
	}
	void SetDir(DIR eDir)
	{
		m_eDir = eDir;
	}
	void SetSpeed(float fSpeed)
	{
		m_fSpeed = fSpeed;
		if (m_fSpeed > 72)
			m_fSpeed = 72;
	}
	void SetBomb(int iBomb)
	{
		m_iBomb = iBomb;
		if (m_iBomb > 6)
			m_iBomb = 6;
	}
	void SetRange(int iRange)
	{
		m_iRange = iRange;
		if (m_iRange > 7)
			m_iRange = 7;
	}

	void AddSpeed()
	{
		m_fSpeed += 16.f;
		if (m_fSpeed > 144.f)
			m_fSpeed = 144.f;
	}
	void AddiBomb(int iBomb)
	{
		m_iBomb += iBomb;
		if (m_iBomb > 6)
			m_iBomb = 6;
		if (m_iBomb < 1)
			m_iBomb = 1;
	}
	void AddRange(int iRange)
	{
		m_iRange += iRange;
		if (m_iRange > 7)
			m_iRange = 7;
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
	int GetBomb() const
	{
		return m_iBomb;
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

private:
	wstring StringToWstring(string str)
	{
		wstring wstr;
		wstr = wstring(str.begin(), str.end());

		return wstr;
	}
};

