#pragma once
#include "Scene.h"

class CInGameScene :
	public CScene
{
private:
	friend class CSceneManager;

public:
	CInGameScene();
	~CInGameScene();

public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
};
