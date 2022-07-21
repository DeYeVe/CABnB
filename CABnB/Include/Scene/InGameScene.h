#pragma once
#include "Scene.h"

class CInGameScene :
	public CScene
{
private:
	friend class CSceneManager;

private:
	class CUITimer* pInGameTimer;
	bool			m_bEnd;

public:
	CInGameScene();
	~CInGameScene();

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);

public:
	void GameEnd(bool bIsDraw);
};
