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

private:
	char	m_strFileName[MAX_PATH] = {};

public:
	const char * GetFileName()
	{
		return m_strFileName;
	}

public:
	virtual bool Init();

public:
	void RoomStartButtonCallback(float fTime, const string& strTag);
	void MapSelectButtonCallback(float fTime, const string& strTag);
};

