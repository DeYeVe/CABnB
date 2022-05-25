#include "ColliderPoint.h"
#include "../Object/Obj.h"
#include "ColliderRect.h"

CColliderPoint::CColliderPoint()
{
	m_eCollType = CT_POINT;
}

CColliderPoint::CColliderPoint(const CColliderPoint & coll) :
	CCollider(coll)
{
	m_tDist = coll.m_tDist;
}

CColliderPoint::~CColliderPoint()
{
}

bool CColliderPoint::Init()
{
	return true;
}

void CColliderPoint::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderPoint::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CColliderPoint::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION	tPos = m_pObj->GetPos();
	m_tPos.x = tPos.x + m_tDist.x;
	m_tPos.y = tPos.y + m_tDist.y;

	return 0;
}

bool CColliderPoint::Collision(CCollider * pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPoint(((CColliderRect*)pDest)->GetWorldInfo(), m_tPos);
	}
	return false;
}

void CColliderPoint::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CColliderPoint * CColliderPoint::Clone()
{
	return new CColliderPoint(*this);
}

void CColliderPoint::Save(FILE * pFile)
{
}

void CColliderPoint::Load(FILE * pFile)
{
}
