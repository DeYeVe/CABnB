#include "Item.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Collider/ColliderRect.h"
#include "Stream.h"

CItem::CItem()
{
}

CItem::CItem(const CItem & item) :
	CObj(item)
{
	m_eType = item.m_eType;
}

CItem::~CItem()
{
}

void CItem::SetItemType(ITEM_TYPE eType)
{
	m_eType = eType;
}

bool CItem::Init()
{
	SetSize(42.f, 45.f);
	CColliderRect* pRC = AddCollider<CColliderRect>("Item");
	m_pRC = pRC;
	m_pRC->SetRect(0.f, 20.f, 40.f, 60.f);
	//pRC->AddCollisionFunction(CS_ENTER, this, &CStream::Hit);

	SAFE_RELEASE(pRC);

	CAnimation* pAni = CreateAnimation("ItemAnimation");

	AddAnimationClip("ItemBomb", AT_ATLAS, AO_LOOP, 0.27f, 3, 1,
		0, 0, 3, 1, 0.f, "ItemBomb", L"Item/ItemBomb.bmp");
	SetAnimationClipColorKey("ItemBomb", 255, 0, 255);

	AddAnimationClip("ItemSpeed", AT_ATLAS, AO_LOOP, 2.27f, 3, 1,
		0, 0, 3, 1, 0.f, "ItemSpeed", L"Item/ItemSpeed.bmp");
	SetAnimationClipColorKey("ItemSpeed", 255, 0, 255);

	AddAnimationClip("ItemRange", AT_ATLAS, AO_LOOP, 0.27f, 3, 1,
		0, 0, 3, 1, 0.f, "ItemRange", L"Item/ItemRange.bmp");
	SetAnimationClipColorKey("ItemRange", 255, 0, 255);

	AddAnimationClip("ItemUltra", AT_ATLAS, AO_LOOP, 0.27f, 3, 1,
		0, 0, 3, 1, 0.f, "ItemUltra", L"Item/ItemUltra.bmp");
	SetAnimationClipColorKey("ItemUltra", 255, 0, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CItem::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CItem::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	switch (m_eType)
	{
	case IT_BOMB:
		m_pAnimation->ChangeClip("ItemBomb");
		break;
	case IT_SPEED:
		m_pAnimation->ChangeClip("ItemSpeed");
		break;
	case IT_RANGE:
		m_pAnimation->ChangeClip("ItemRange");
		break;
	case IT_ULTRA:
		m_pAnimation->ChangeClip("ItemUltra");
		break;
	default:
		break;
	}

	m_fOffsetTime += fDeltaTime;

	if (m_fOffsetTime > 0.2f)
	{
		POSITION pPos = GetPos();
		POSITION pOffset = { 0.f, 1.f };

		if (m_iOffsetReverse < 5)
		{
			m_fOffsetTime = 0.f;
			SetPos(pPos + pOffset);
			m_pRC->SetRect(0.f, 19.f - m_iOffsetReverse, 40.f, 59.f - m_iOffsetReverse);
			m_iOffsetReverse++;
			m_iOffsetReverse %= 10;
		}
		else
		{
			m_fOffsetTime = 0.f;
			SetPos(pPos - pOffset);
			m_pRC->SetRect(0.f, 11.f + m_iOffsetReverse, 40.f, 51.f + m_iOffsetReverse);
			m_iOffsetReverse++;
			m_iOffsetReverse %= 10;
		}
	}

	return 0;
}

int CItem::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CItem::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CItem::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
}

CItem * CItem::Clone()
{
	return new CItem(*this);
}