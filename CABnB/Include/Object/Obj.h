#pragma once

#include "../Core/Ref.h"
#include "../Scene/Layer.h"
#include "../Collider/Collider.h"

class CObj :
	public CRef
{

protected:
	friend class CScene;

protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

private:
	static list<CObj*>	m_ObjList;

public:
	static void AddObj(CObj* pObj);
	static CObj* FindObject(const string& strTag);
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);
	static void EraseObj();

protected:
	class CScene*	m_pScene;
	class CLayer*	m_pLayer;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}

	class CScene* GetScene()	const
	{
		return m_pScene;
	}

	class CLayer* GetLayer()	const
	{
		return m_pLayer;
	}

protected:
	bool		m_bIsPhysics;
	float		m_fGravityTime;

public:
	void ClearGravity()
	{
		m_fGravityTime = 0.f;
	}

public:
	void SetPhysics(bool bPhysics)
	{
		m_bIsPhysics = bPhysics;
	}

	bool GetPhysics()	const
	{
		return m_bIsPhysics;
	}

protected:
	POSITION	m_tPos;
	_SIZE		m_tSize;
	_SIZE		m_tImageOffset;
	POSITION	m_tPivot;
	class CTexture*		m_pTexture;
	list<CCollider*>	m_ColliderList;
	class CAnimation*	m_pAnimation;

public:
	class CAnimation* CreateAnimation(const string& strTag);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	bool AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const vector<wstring> vecFileName,
		const string& strPathKey = TEXTURE_PATH);
	void SetAnimationClipColorKey(const string& strClip,
		unsigned char r, unsigned char g, unsigned char b);

public:
	const list<class CCollider*>* GetColliderList() const
	{
		return &m_ColliderList;
	}

	CCollider* GetCollider(const string& strTag);

	template <typename T>
	void AddCollisionFunction(const string &strTag,
		COLLISION_STATE eState, T* pObj,
		void(T::*pFunc)(CCollider*, CCollider*, float))
	{
		for (CCollider* coll : m_ColliderList)
		{
			if (*coll->GetTag() == strTag)
			{
				(*coll)->AddCollisionFunction(eState, pObj, pFunc);
				break;
			}
			
		}
	}

public:
	template <typename T>
	T* AddCollider(const string& strTag)
	{
		T*	pCollider = new T;

		pCollider->SetObj(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return NULL;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;
	}

	bool CheckCollider()
	{
		return !m_ColliderList.empty();
	}

public:
	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	void SetPos(const POINT& tPt)
	{
		m_tPos = tPt;
	}

	void SetSize(const _SIZE& tSize)
	{
		m_tPos = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void SetPivot(const _SIZE& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

	void SetImageOffset(const _SIZE& tOffset)
	{
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x, float y)
	{
		m_tImageOffset.x = x;
		m_tImageOffset.y = y;
	}

public:
	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	CTexture* GetTexture()
	{
		return m_pTexture;
	}

public:
	float GetLeft() const
	{
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}

	float GetRight() const
	{
		return GetLeft() + m_tSize.x;
	}

	float GetTop() const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}

	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}

	POSITION GetCenter() const
	{
		return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f);
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE GetSize() const
	{
		return m_tSize;
	}

	POSITION GetPivot() const
	{
		return m_tPivot;
	}

public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0;
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	void SaveFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void SaveFromFullPath(const char* pFullPath);
	void LoadFromPath(const char* pFileName, const string& strPathKey = DATA_PATH);
	void LoadFromFullPath(const char* pFullPath);

public:
	template <typename T>
	static T* CreateObj(const string& strTag, class CLayer* pLayer = NULL)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_DELETE(pObj);
			return NULL;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}

		AddObj(pObj);

		return pObj;
	}

	static CObj* CreateCloneObj(const string& strPrototypeKey,
		const string& strTag, SCENE_CREATE sc,
		class CLayer* pLayer = NULL);
};

