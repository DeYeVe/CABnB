#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
private:
	friend class CStage;

public:
	CTile();
	CTile(const CTile & tile);
	~CTile();

private:
	class CTexture* m_pTex;


public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CTile* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

