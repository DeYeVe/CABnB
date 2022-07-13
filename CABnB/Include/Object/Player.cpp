#include "Player.h"
#include "../Core/Input.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Object/Block.h"
#include "../Object/Bomb.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer & player) :
	CObj(player)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	SetMove(false);
	SetPos(0.f, 0.f);
	SetSize(44.f, 58.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetDir(DIR_DOWN);
	SetSpeed(80.f);
	SetBomb(3);
	SetRange(3);
	SetObjTag("Player");
	m_bPossiblePlant = true;

	if (CObj::FindObject("Player1"))
		m_iPlayerNumber = 2;
	else 
		m_iPlayerNumber = 1;

	
	string strPN = to_string(m_iPlayerNumber);
	SetTag("Player" + strPN);
	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody" + strPN);
	pRC->SetRect(-20.f, -20.f, 20.f, 20.f);

	pRC->AddCollisionFunction(CS_ENTER, this, &CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this, &CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	CAnimation* pAni = CreateAnimation("Player" + strPN + "Animation");

	AddAnimationClip(strPN + "P_StopDown", AT_ATLAS, AO_LOOP, 1.0f, 1, 1,
		0, 0, 1, 1, 0.f, strPN + "P_StopDown", StringToWstring("Player/" + strPN + "P/stop_down.bmp").c_str());
	SetAnimationClipColorKey(strPN + "P_StopDown", 255, 0, 255);

	AddAnimationClip(strPN + "P_StopLeft", AT_ATLAS, AO_LOOP, 1.0f, 1, 1,
		0, 0, 1, 1, 0.f, strPN + "P_StopLeft", StringToWstring("Player/" + strPN + "P/stop_left.bmp").c_str());
	SetAnimationClipColorKey(strPN + "P_StopLeft", 255, 0, 255);

	AddAnimationClip(strPN + "P_StopRight", AT_ATLAS, AO_LOOP, 1.0f, 1, 1,
		0, 0, 1, 1, 0.f, strPN + "P_StopRight", StringToWstring("Player/" + strPN + "P/stop_right.bmp").c_str());
	SetAnimationClipColorKey(strPN + "P_StopRight", 255, 0, 255);

	AddAnimationClip(strPN + "P_StopUp", AT_ATLAS, AO_LOOP, 1.0f, 1, 1,
		0, 0, 1, 1, 0.f, strPN + "P_StopUp", StringToWstring("Player/" + strPN + "P/stop_up.bmp").c_str());
	SetAnimationClipColorKey(strPN + "P_StopUp", 255, 0, 255);

	AddAnimationClip(strPN + "P_Hide", AT_ATLAS, AO_LOOP, 1.0f, 1, 1,
		0, 0, 1, 1, 0.f, strPN + "P_Hide", StringToWstring("Player/" + strPN + "P/hide.bmp").c_str());
	SetAnimationClipColorKey(strPN + "P_Hide", 255, 0, 255);


	vector<wstring> vecFileName;

	for (int i = 1; i <= 6; ++i)
	{
		vecFileName.push_back(StringToWstring("Player/" + strPN + "P/move_down_" + to_string(i) + ".bmp"));
	}
	AddAnimationClip(strPN + "P_MoveDown", AT_FRAME, AO_ONCE_RETURN , 0.5f, 6, 1,
		0, 0, 6, 1, 0.f, strPN + "P_MoveDown",
		vecFileName);
	SetAnimationClipColorKey(strPN + "P_MoveDown", 255, 0, 255);
	vecFileName.clear();

	for (int i = 1; i <= 6; ++i)
	{
		vecFileName.push_back(StringToWstring("Player/" + strPN + "P/move_up_" + to_string(i) + ".bmp"));
	}
	AddAnimationClip(strPN + "P_MoveUp", AT_FRAME, AO_ONCE_RETURN, 0.5f, 6, 1,
		0, 0, 6, 1, 0.f, strPN + "P_MoveUp",
		vecFileName);
	SetAnimationClipColorKey(strPN + "P_MoveUp", 255, 0, 255);
	vecFileName.clear();

	for (int i = 1; i <= 6; ++i)
	{
		vecFileName.push_back(StringToWstring("Player/" + strPN + "P/move_left_" + to_string(i) + ".bmp"));
	}
	AddAnimationClip(strPN + "P_MoveLeft", AT_FRAME, AO_ONCE_RETURN, 0.5f, 4, 1,
		0, 0, 4, 1, 0.f, strPN + "P_MoveLeft",
		vecFileName);
	SetAnimationClipColorKey(strPN + "P_MoveLeft", 255, 0, 255);
	vecFileName.clear();

	for (int i = 1; i <= 6; ++i)
	{
		vecFileName.push_back(StringToWstring("Player/" + strPN + "P/move_right_" + to_string(i) + ".bmp"));
	}
	AddAnimationClip(strPN + "P_MoveRight", AT_FRAME, AO_ONCE_RETURN, 0.5f, 4, 1,
		0, 0, 4, 1, 0.f, strPN + "P_MoveRight",
		vecFileName);
	SetAnimationClipColorKey(strPN + "P_MoveRight", 255, 0, 255);
	vecFileName.clear();

	SAFE_RELEASE(pAni);

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);

	string strPN = to_string(m_iPlayerNumber);

	if (KEYDOWN(strPN + "P_" + "MoveLeft"))
	{
		m_strArrowKeys.push_back("Left");
	}
	if (KEYDOWN(strPN + "P_" + "MoveRight"))
	{
		m_strArrowKeys.push_back("Right");
	}
	if (KEYDOWN(strPN + "P_" + "MoveDown"))
	{
		m_strArrowKeys.push_back("Down");
	}
	if (KEYDOWN(strPN + "P_" + "MoveUp"))
	{
		m_strArrowKeys.push_back("Up");
	}

	if (KEYUP(strPN + "P_" + "MoveLeft"))
	{
		m_strArrowKeys.erase(remove(m_strArrowKeys.begin(), m_strArrowKeys.end(), "Left"),
			m_strArrowKeys.end());
	}
	if (KEYUP(strPN + "P_" + "MoveRight"))
	{
		m_strArrowKeys.erase(remove(m_strArrowKeys.begin(), m_strArrowKeys.end(), "Right"),
			m_strArrowKeys.end());;
	}
	if (KEYUP(strPN + "P_" + "MoveDown"))
	{
		m_strArrowKeys.erase(remove(m_strArrowKeys.begin(), m_strArrowKeys.end(), "Down"),
			m_strArrowKeys.end());
	}
	if (KEYUP(strPN + "P_" + "MoveUp"))
	{
		m_strArrowKeys.erase(remove(m_strArrowKeys.begin(), m_strArrowKeys.end(), "Up"),
			m_strArrowKeys.end());
	}

	if (m_strArrowKeys.empty())
	{
		m_bMove = false;
	}
	else if (!m_strArrowKeys.empty())
	{
		if (m_strArrowKeys.back() == "Left")
		{
			Move(-m_fSpeed, 0, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveLeft");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopLeft");
			m_eDir = DIR_LEFT;
		}

		if (m_strArrowKeys.back() == "Right")
		{
			Move(m_fSpeed, 0, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveRight");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopRight");
			m_eDir = DIR_RIGHT;
		}

		if (m_strArrowKeys.back() == "Up")
		{
			Move(0, -m_fSpeed, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveUp");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopUp");
			m_eDir = DIR_UP;
		}

		if (m_strArrowKeys.back() == "Down")
		{
			Move(0, m_fSpeed, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveDown");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopDown");
			m_eDir = DIR_DOWN;
		}
	}

	if (KEYDOWN(strPN + "P_" + "Plant"))
	{
		Plant();
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	if (!m_bMove)
		m_pAnimation->ReturnClip();

	m_bPossiblePlant = true;

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);

	if (m_tPos.x < 40.f)
		m_tPos.x = 40.f;
	if (m_tPos.x > 600.f)
		m_tPos.x = 600.f;
	if (m_tPos.y < 61.f)
		m_tPos.y = 61.f;
	if (m_tPos.y > 541.f)
		m_tPos.y = 541.f;

	return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();
}

CPlayer * CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;
	m_bMove = true;
}

void CPlayer::Plant()
{
	if (!m_bPossiblePlant)
		return;

	if (m_iBomb < 1)
		return;

	CLayer* pLayer = GET_SINGLE(CSceneManager)->GetScene()->FindLayer("Stage");
	CBomb* pBomb = CObj::CreateObj<CBomb>("Bomb", pLayer);
	pBomb->SetObjTag("Bomb");

	POSITION pPos = GetPos();
	pPos.x -= 20.f;
	pPos.y -= 41.f;
	int iX = (int)pPos.x - (int)pPos.x % 40;
	int iY = (int)pPos.y - (int)pPos.y % 40;

	pPos.x = iX;
	pPos.y = iY;
	pPos.x += 20.f;
	pPos.y += 41.f;

	pBomb->SetPos(pPos);
	pBomb->SetPlayer(this);
	pBomb->SetRange(GetRange());
	CColliderRect* pRC = pBomb->AddCollider<CColliderRect>("Bomb");
	pRC->SetRect(0.f, 0.f, 40.f, 40.f);

	AddBomb(-1);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBomb);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	CObj* pDestObj = pDest->GetObj();
	string strDestObjTag = pDestObj->GetObjTag();
	RECTANGLE tSrcRect = ((CColliderRect*)pSrc)->GetWorldInfo();
	RECTANGLE tDestRect = ((CColliderRect*)pDest)->GetWorldInfo();

	if (strDestObjTag == "Block")
	{
		BLOCK_TYPE eBlockType = ((CBlock*)pDestObj)->GetBlockType();

		if (eBlockType == BT_NORMAL || eBlockType == BT_UNBRK)
		{			
			//left
			if (tSrcRect.l < tDestRect.l && abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t)
				&& m_eDir == DIR_RIGHT)
			{
				SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				//left top
				if (tSrcRect.t < tDestRect.t)
				{
					if (tSrcRect.b - m_fSpeed * fDeltaTime < tDestRect.t)
						SetPos(GetPos().x, GetPos().y - abs(tSrcRect.b - tDestRect.t));
					else
						SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				}
				//left bottom
				else if (tSrcRect.t > tDestRect.t)
				{
					if (tSrcRect.t + m_fSpeed * fDeltaTime > tDestRect.b)
						SetPos(GetPos().x, GetPos().y + abs(tSrcRect.t - tDestRect.b));
					else
						SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				}
			}
			//right
			else if (tSrcRect.l > tDestRect.l && abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t)
				&& m_eDir == DIR_LEFT)
			{
				SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				//right top
				if (tSrcRect.t < tDestRect.t)
				{
					if (tSrcRect.b - m_fSpeed * fDeltaTime < tDestRect.t)
						SetPos(GetPos().x, GetPos().y - abs(tSrcRect.b - tDestRect.t));
					else
						SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				}
				//right bottom
				else if (tSrcRect.t > tDestRect.t)
				{
					if (tSrcRect.t + m_fSpeed * fDeltaTime > tDestRect.b)
						SetPos(GetPos().x, GetPos().y + abs(tSrcRect.t - tDestRect.b));
					else
						SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				}
			}
			//top
			else if (tSrcRect.t < tDestRect.t && abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l)
				&& m_eDir == DIR_DOWN)
			{
				SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				//top left
				if (tSrcRect.l < tDestRect.l)
				{
					if (tSrcRect.r - m_fSpeed * fDeltaTime < tDestRect.l)
						SetPos(GetPos().x - abs(tSrcRect.r - tDestRect.l), GetPos().y);
					else
						SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				}
				//top right
				else if (tSrcRect.l > tDestRect.l)
				{
					if (tSrcRect.l + m_fSpeed * fDeltaTime > tDestRect.r)
						SetPos(GetPos().x + abs(tSrcRect.l - tDestRect.r), GetPos().y);
					else
						SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				}
			}
			//bottom
			else if (tSrcRect.t > tDestRect.t && abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l)
				&& m_eDir == DIR_UP)
			{
				SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				//bottom left
				if (tSrcRect.l < tDestRect.l)
				{
					if (tSrcRect.r - m_fSpeed * fDeltaTime < tDestRect.l)
						SetPos(GetPos().x - abs(tSrcRect.r - tDestRect.l), GetPos().y);
					else
						SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				}
				//bottom right	
				else if (tSrcRect.l > tDestRect.l)
				{
					if (tSrcRect.l + m_fSpeed * fDeltaTime > tDestRect.r)
						SetPos(GetPos().x + abs(tSrcRect.l - tDestRect.r), GetPos().y);
					else
						SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				}
			}
		}

	}
	else if (strDestObjTag == "Bomb")
	{
		if ((abs(tSrcRect.l - tDestRect.l) < 20.f && abs(tSrcRect.t - tDestRect.t) < 20.f))
		{
			m_bPossiblePlant = false;
		}

		if (!(abs(tSrcRect.l - tDestRect.l) < 39.f && abs(tSrcRect.t - tDestRect.t) < 39.f))
			return;

		//left
		if (tSrcRect.r > tDestRect.l && tSrcRect.r < tDestRect.l + 2.f &&
			abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t) && m_eDir == DIR_RIGHT && m_bMove)
		{
			SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
		}
		//right
		else if (tSrcRect.l < tDestRect.r && tSrcRect.l + 2.f > tDestRect.r &&
			abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t) && m_eDir == DIR_LEFT && m_bMove)
		{
			SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
		}
		//top
		else if (tSrcRect.b > tDestRect.t && tSrcRect.b < tDestRect.t + 2.f &&
			abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l) && m_eDir == DIR_DOWN && m_bMove)
		{
			SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
		}
		//bottom
		else if (tSrcRect.t < tDestRect.b && tSrcRect.t + 2.f > tDestRect.b &&
			abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l) && m_eDir == DIR_UP && m_bMove)
		{
			SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
		}
	}

	//else if (strDestObjTag == "Item")
	//{
	//ITEM_TYPE eItemType = ((CItem*)pDestObj)->GetItemType();
	//}
}

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	CObj* pDestObj = pDest->GetObj();
	string strDestObjTag = pDestObj->GetObjTag();
	RECTANGLE tSrcRect = ((CColliderRect*)pSrc)->GetWorldInfo();
	RECTANGLE tDestRect = ((CColliderRect*)pDest)->GetWorldInfo();

	if (strDestObjTag == "Block")
	{
		BLOCK_TYPE eBlockType = ((CBlock*)pDestObj)->GetBlockType();

		if (eBlockType == BT_BUSH)
		{
			POSITION tCenter = POSITION((tSrcRect.l + tSrcRect.r) / 2.f, (tSrcRect.b + tSrcRect.t) / 2.f);
			if (tCenter.x > tDestRect.l && tCenter.x < tDestRect.r && 
				tCenter.y > tDestRect.t && tCenter.y < tDestRect.b)
				m_pAnimation->ChangeClip(to_string(m_iPlayerNumber) + "P_" + "Hide");

		}
		else if (eBlockType == BT_NORMAL || eBlockType == BT_UNBRK)
		{
			//left
			if (tSrcRect.l < tDestRect.l && abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t)
				&& m_eDir == DIR_RIGHT)
			{
				SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				//left top
				if (tSrcRect.t < tDestRect.t)
				{
					if (tSrcRect.b - m_fSpeed * fDeltaTime < tDestRect.t)
						SetPos(GetPos().x, GetPos().y - abs(tSrcRect.b - tDestRect.t));
					else
						SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				}
				//left bottom
				else if (tSrcRect.t > tDestRect.t)
				{
					if (tSrcRect.t + m_fSpeed * fDeltaTime > tDestRect.b)
						SetPos(GetPos().x, GetPos().y + abs(tSrcRect.t - tDestRect.b));
					else
						SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				}
			}
			//right
			else if (tSrcRect.l > tDestRect.l && abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t)
				&& m_eDir == DIR_LEFT)
			{
				SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				//right top
				if (tSrcRect.t < tDestRect.t)
				{
					if (tSrcRect.b - m_fSpeed * fDeltaTime < tDestRect.t)
						SetPos(GetPos().x, GetPos().y - abs(tSrcRect.b - tDestRect.t));
					else
						SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				}
				//right bottom
				else if (tSrcRect.t > tDestRect.t)
				{
					if (tSrcRect.t + m_fSpeed * fDeltaTime > tDestRect.b)
						SetPos(GetPos().x, GetPos().y + abs(tSrcRect.t - tDestRect.b));
					else
						SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				}
			}
			//top
			else if (tSrcRect.t < tDestRect.t && abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l)
				&& m_eDir == DIR_DOWN)
			{
				SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
				//top left
				if (tSrcRect.l < tDestRect.l)
				{
					if (tSrcRect.r - m_fSpeed * fDeltaTime < tDestRect.l)
						SetPos(GetPos().x - abs(tSrcRect.r - tDestRect.l), GetPos().y);
					else
						SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				}
				//top right
				else if (tSrcRect.l > tDestRect.l)
				{
					if (tSrcRect.l + m_fSpeed * fDeltaTime > tDestRect.r)
						SetPos(GetPos().x + abs(tSrcRect.l - tDestRect.r), GetPos().y);
					else
						SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				}
			}
			//bottom
			else if (tSrcRect.t > tDestRect.t && abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l)
				&& m_eDir == DIR_UP)
			{
				SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
				//bottom left
				if (tSrcRect.l < tDestRect.l)
				{
					if (tSrcRect.r - m_fSpeed * fDeltaTime < tDestRect.l)
						SetPos(GetPos().x - abs(tSrcRect.r - tDestRect.l), GetPos().y);
					else
						SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
				}
				//bottom right	
				else if (tSrcRect.l > tDestRect.l)
				{
					if (tSrcRect.l + m_fSpeed * fDeltaTime > tDestRect.r)
						SetPos(GetPos().x + abs(tSrcRect.l - tDestRect.r), GetPos().y);
					else
						SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
				}
			}
		}
	}
	else if (strDestObjTag == "Bomb")
	{
		if ((abs(tSrcRect.l - tDestRect.l) < 20.f && abs(tSrcRect.t - tDestRect.t) < 20.f))
		{
			m_bPossiblePlant = false;
		}

		if (!(abs(tSrcRect.l - tDestRect.l) < 39.f && abs(tSrcRect.t - tDestRect.t) < 39.f))
			return;

		//left
		if (tSrcRect.r > tDestRect.l && tSrcRect.r < tDestRect.l + 2.f && 
			abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t) && m_eDir == DIR_RIGHT && m_bMove)
		{
			SetPos(GetPos().x - m_fSpeed * fDeltaTime, GetPos().y);
		}
		//right
		else if (tSrcRect.l < tDestRect.r && tSrcRect.l + 2.f > tDestRect.r &&
			abs(tSrcRect.l - tDestRect.l) > abs(tSrcRect.t - tDestRect.t) && m_eDir == DIR_LEFT && m_bMove)
		{
			SetPos(GetPos().x + m_fSpeed * fDeltaTime, GetPos().y);
		}
		//top
		else if (tSrcRect.b > tDestRect.t && tSrcRect.b < tDestRect.t + 2.f && 
			abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l) && m_eDir == DIR_DOWN && m_bMove)
		{
			SetPos(GetPos().x, GetPos().y - m_fSpeed * fDeltaTime);
		}
		//bottom
		else if (tSrcRect.t < tDestRect.b && tSrcRect.t + 2.f > tDestRect.b && 
			abs(tSrcRect.t - tDestRect.t) > abs(tSrcRect.l - tDestRect.l) && m_eDir == DIR_UP && m_bMove)
		{
			SetPos(GetPos().x, GetPos().y + m_fSpeed * fDeltaTime);
		}
	}
}