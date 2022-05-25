#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
private:
	friend class CSceneManager;

public:
	CStartScene();
	~CStartScene();

public:
	virtual bool Init();

public:
	void StartButtonCallback(float fTime, const string& strTag);
	void EndButtonCallback(float fTime, const string& strTag);
	void EditButtonCallback(float fTime, const string& strTag);
};
