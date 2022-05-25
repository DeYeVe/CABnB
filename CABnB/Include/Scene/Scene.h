#pragma once

#include "../Game.h"
class CScene
{
protected:
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0; // 부모클래스로 쓸거면 일단 virtual 붙여두는 습관

private:
	static unordered_map<string, class CObj*> m_mapPrototype[SC_END];

public:
	static void ErasePrototype(const string& strTag, SCENE_CREATE sc);
	static void ErasePrototype(SCENE_CREATE sc);

protected:
	list<class CLayer*> m_LayerList;
	SCENE_CREATE	m_eSceneType;

public:
	void SetSceneType(SCENE_CREATE eType)
	{
		m_eSceneType = eType;
	}

	SCENE_CREATE GetSceneType()
	{
		return m_eSceneType;
	}

public:
	class CLayer* CreateLayer(const string& strTag, int iZorder = 0);
	class CLayer* FindLayer(const string& strTag);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);

public:
	template <typename T>
	static T* CreatePrototype(const string& strTag, SCENE_CREATE sc)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_DELETE(pObj);
			return NULL;
		}

		pObj->AddRef();
		m_mapPrototype[sc].insert(make_pair(strTag, pObj));

		return pObj;
	}

	static CObj* FindPrototype(const string& strKey, SCENE_CREATE sc);
	static void ChangeProtoType();
};

