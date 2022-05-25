#pragma once
#include "Scene.h"
class CRoomScene :
	public CScene
{
private:
	friend class CSceneManager;

public:
	CRoomScene();
	~CRoomScene();

public:
	virtual bool Init();

public:
	void RoomStartButtonCallback(float fTime, const string& strTag);
	void MapSelectButtonCallback(float fTime, const string& strTag);
};

