#include "Stream.h"
#include "../Animation/Animation.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Collider/ColliderRect.h"
#include "Block.h"
#include "Item.h"
#include "../Core/Math.h"

CStream::CStream() :
	m_fLifeTime(0.f)
{
}

CStream::CStream(const CStream & stream) :
	CObj(stream)
{
	m_fLifeTime = stream.GetLifeTime();
}

CStream::~CStream()
{
}

bool CStream::Init()
{
	SetPos(0.f, 0.f);
	SetSize(40.f, 40.f);
	SetLifeTime(0.3f);
	SetRange(0);
	m_bIsSpread = false;
	m_bIsCollided = false;

	CColliderRect* pRC = AddCollider<CColliderRect>("Stream");
	pRC->SetRect(0.f, 0.f, 40.f, 40.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CStream::Hit);

	SAFE_RELEASE(pRC);

	CAnimation* pAni = CreateAnimation("StreamAnimation");

	AddAnimationClip("StreamLeft", AT_ATLAS, AO_LOOP, 0.3f, 20, 1,
		0, 0, 20, 1, 0.f, "StreamLeft", L"Bomb/StreamLeft.bmp");
	SetAnimationClipColorKey("StreamLeft", 255, 0, 255);

	AddAnimationClip("StreamRight", AT_ATLAS, AO_LOOP, 0.3f, 20, 1,
		0, 0, 20, 1, 0.f, "StreamRight", L"Bomb/StreamRight.bmp");
	SetAnimationClipColorKey("StreamRight", 255, 0, 255);

	AddAnimationClip("StreamUp", AT_ATLAS, AO_LOOP, 0.3f, 20, 1,
		0, 0, 20, 1, 0.f, "StreamUp", L"Bomb/StreamUp.bmp");
	SetAnimationClipColorKey("StreamUp", 255, 0, 255);

	AddAnimationClip("StreamDown", AT_ATLAS, AO_LOOP, 0.3f, 20, 1,
		0, 0, 20, 1, 0.f, "StreamDown", L"Bomb/StreamDown.bmp");
	SetAnimationClipColorKey("StreamDown", 255, 0, 255);

	AddAnimationClip("StreamNone", AT_ATLAS, AO_LOOP, 0.15f, 4, 1,
		0, 0, 4, 1, 0.f, "StreamNone", L"Bomb/StreamNone.bmp");
	SetAnimationClipColorKey("StreamNone", 255, 0, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CStream::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CStream::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	if (m_iRange <= 0)
		Die();

	m_fLifeTime -= fDeltaTime;

	if (m_fLifeTime <= 0)
		Die();

	switch (m_eDir)
	{
	case DIR_NONE:
		m_pAnimation->ChangeClip("StreamNone");
		break;
	case DIR_LEFT:
		m_pAnimation->ChangeClip("StreamLeft");
		break;
	case DIR_RIGHT:
		m_pAnimation->ChangeClip("StreamRight");
		break;
	case DIR_UP:
		m_pAnimation->ChangeClip("StreamUp");
		break;
	case DIR_DOWN:
		m_pAnimation->ChangeClip("StreamDown");
		break;
	default:
		break;
	}

	if (m_iRange > 0 && !m_bIsSpread && m_bIsCollided)
	{
		Expand();
	}

	return 0;
}

int CStream::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStream::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
	m_bIsCollided = true;
}

void CStream::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
}

CStream * CStream::Clone()
{
	return new CStream(*this);
}

void CStream::Expand()
{
	POSITION pPosLeft = GetPos();
	POSITION pPosRight = GetPos();
	POSITION pPosUp = GetPos();
	POSITION pPosDown = GetPos();
	pPosLeft.x -= 40.f;
	pPosRight.x += 40.f;
	pPosUp.y -= 40.f;
	pPosDown.y += 40.f;

	CLayer* pLayer = GET_SINGLE(CSceneManager)->GetScene()->FindLayer("Stage");

	if (m_eDir == DIR_NONE)
	{
		CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_LEFT);
		pStream->SetPos(pPosLeft);

		pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_RIGHT);
		pStream->SetPos(pPosRight);

		pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_UP);
		pStream->SetPos(pPosUp);

		pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_DOWN);
		pStream->SetPos(pPosDown);

		SAFE_RELEASE(pStream);
	}
	else if (m_eDir == DIR_LEFT)
	{
		CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_LEFT);
		pStream->SetPos(pPosLeft);

		SAFE_RELEASE(pStream);
	}
	else if (m_eDir == DIR_RIGHT)
	{
		CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_RIGHT);
		pStream->SetPos(pPosRight);

		SAFE_RELEASE(pStream);
	}
	else if (m_eDir == DIR_UP)
	{
		CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_UP);
		pStream->SetPos(pPosUp);

		SAFE_RELEASE(pStream);
	}
	else if (m_eDir == DIR_DOWN)
	{
		CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
		pStream->SetObjTag("Stream");
		pStream->SetRange(GetRange() - 1);
		pStream->SetDir(DIR_DOWN);
		pStream->SetPos(pPosDown);

		SAFE_RELEASE(pStream);
	}

	m_bIsSpread = true;
}

void CStream::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	CObj* pDestObj = pDest->GetObj();
	string strDestObjTag = pDestObj->GetObjTag();

	if (strDestObjTag == "Block")
	{
		BLOCK_TYPE eBlockType = ((CBlock*)pDestObj)->GetBlockType();

		if (eBlockType == BT_BUSH)
		{
			pDestObj->Die();
		}
		else if (eBlockType == BT_NORMAL)
		{
			pDestObj->Die();
			SetRange(0);

			int iRand = CMath::RandInt();

			if (iRand > 33)
				return;

			POSITION pPos = GetPos();
			pPos.y -= 20;

			CLayer* pLayer = GET_SINGLE(CSceneManager)->GetScene()->FindLayer("Default");

			CItem* pItem = CObj::CreateObj<CItem>("Item", pLayer);
			pItem->SetObjTag("Item");

			iRand = CMath::RandInt();
			if(iRand % 10 < 3)
				pItem->SetItemType(IT_SPEED);
			else if (iRand % 10 < 6)
				pItem->SetItemType(IT_BOMB);
			else if (iRand % 10 < 9)
				pItem->SetItemType(IT_RANGE);
			else if(iRand % 10 < 10)
				pItem->SetItemType(IT_ULTRA);
				
			pItem->SetPos(pPos);

			SAFE_RELEASE(pItem);
		}
		else if (eBlockType == BT_UNBRK)
		{
			SetRange(0);
		}
	}
	else if (strDestObjTag == "Bomb")
	{
		((CBomb*)pDestObj)->Explosion();
	}
	else if (strDestObjTag == "Item")
	{
		pDestObj->Die();
	}
}