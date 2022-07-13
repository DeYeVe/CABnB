#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "Collider.h"
#include "../Core/Math.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::AddObject(CObj * pObj)
{
	if (pObj->CheckCollider())
	{
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2)
	{
		m_CollisionList.clear();
		return;
	}

	// 오브젝트간 충돌처리를 한다.
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == "Block" || (*iter)->GetTag() == "Item")
			continue;
		list<CObj*>::iterator	iter1 = iter;
		++iter1;
		list<CObj*>::iterator	iter1End = m_CollisionList.end();
		for (; iter1 != iter1End; ++iter1)
		{
			if ((*iter)->GetTag() == "Block" || (*iter)->GetTag() == "Item")
			{
				if (CMath::Distance((*iter)->GetPos(), (*iter1)->GetPos()) < 42.f)
					Collision(*iter, *iter1, fDeltaTime);
			}
			else
				Collision(*iter, *iter1, fDeltaTime);
		}
	}

	m_CollisionList.clear();
}

bool CCollisionManager::Collision(CObj * pSrc, CObj * pDest, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator	iterSrc;
	list<CCollider*>::const_iterator	iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator	iterDest;
	list<CCollider*>::const_iterator	iterDestEnd = pDestList->end();

	bool	bCollision = false;

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc)
	{
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest)
		{
			if ((*iterSrc)->Collision(*iterDest))
			{
				bCollision = true;

				(*iterDest)->SetHitPoint((*iterSrc)->GetHitPoint());

				// 충돌 목록에서 이전에 충돌된 적이 없다면
				// 처음 막 충돌되었다는 의미이다.
				if (!(*iterSrc)->CheckCollisionList(*iterDest))
				{
					// 서로 상대방을 충돌 목록으로 추가한다.
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					(*iterSrc)->CallFunction(CS_ENTER, *iterDest,
						fDeltaTime);
					(*iterDest)->CallFunction(CS_ENTER, *iterSrc,
						fDeltaTime);
				}

				// 기존 충돌된적이 있다면 계속 충돌 상태인 것이다.
				else
				{
					(*iterSrc)->CallFunction(CS_STAY, *iterDest,
						fDeltaTime);
					(*iterDest)->CallFunction(CS_STAY, *iterSrc,
						fDeltaTime);
				}
			}

			// 현재 충돌이 안된 상태에서 이전에 충돌이 되고 있었다면
			// 이제 막 충돌상태에서 떨어졌다는 의미이다.
			else if ((*iterSrc)->CheckCollisionList(*iterDest))
			{
				// 서로 충돌이 안되므로 충돌목록에서 지워준다.
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDest,
					fDeltaTime);
				(*iterDest)->CallFunction(CS_LEAVE, *iterSrc,
					fDeltaTime);
			}
		}
	}

	return bCollision;
}

void CCollisionManager::Clear()
{
	m_CollisionList.clear();
}
