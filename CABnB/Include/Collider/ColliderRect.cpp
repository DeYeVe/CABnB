#include "ColliderRect.h"
#include "../Object/Obj.h"
#include "ColliderPoint.h"
#include "../Core/Camera.h"
#include "../Core/Input.h"

CColliderRect::CColliderRect()
{
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect & coll)		:
	CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

CColliderRect::~CColliderRect()
{
}

void CColliderRect::SetRect(float l, float t, float r, float b)
{
	m_tInfo.l = l;
	m_tInfo.t = t;
	m_tInfo.r = r;
	m_tInfo.b = b;
}

bool CColliderRect::Init()
{
	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION	tPos = m_pObj->GetPos();
	m_tWorldInfo.l = tPos.x + m_tInfo.l;
	m_tWorldInfo.t = tPos.y + m_tInfo.t;
	m_tWorldInfo.r = tPos.x + m_tInfo.r;
	m_tWorldInfo.b = tPos.y + m_tInfo.b;
	
	return 0;
}

bool CColliderRect::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CColliderRect*)pDest)->GetWorldInfo());

	case CT_POINT:
		return CollisionRectToPoint(m_tWorldInfo,
			((CColliderPoint*)pDest)->GetPoint());
	}
	return false;
}

void CColliderRect::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);

	POSITION	tCamPos = GET_SINGLE(CCamera)->GetPos();

	RECTANGLE tRC = m_tWorldInfo;
	tRC.l -= tCamPos.x;
	tRC.r -= tCamPos.x;
	tRC.t -= tCamPos.y;
	tRC.b -= tCamPos.y;

	if (GET_SINGLE(CInput)->GetToggleBorder())
	{
		MoveToEx(hDC, tRC.l, tRC.t, NULL);
		LineTo(hDC, tRC.r, tRC.t);
		LineTo(hDC, tRC.r, tRC.b);
		LineTo(hDC, tRC.l, tRC.b);
		LineTo(hDC, tRC.l, tRC.t);
	}
}

CColliderRect * CColliderRect::Clone()
{
	return new CColliderRect(*this);
}

void CColliderRect::Save(FILE * pFile)
{
}

void CColliderRect::Load(FILE * pFile)
{
}
