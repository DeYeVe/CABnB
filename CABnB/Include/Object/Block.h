#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
private:
	friend class CStage;

public:
	CBlock();
	CBlock(const CBlock & block);
	~CBlock();

private:
	BLOCK_TYPE		m_eType;
	class CTexture* m_pTex;

public:
	void SetBlockType(BLOCK_TYPE eType);
	BLOCK_TYPE GetBlockType() const
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
	virtual CBlock* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

