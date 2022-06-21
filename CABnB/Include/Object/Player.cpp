#include "Player.h"
#include "../Core/Input.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"
#include "../Scene/Scene.h"

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
	SetBomb(1);
	SetRange(1);
	if (CObj::FindObject("Player1"))
		m_iPlayerNumber = 2;
	else 
		m_iPlayerNumber = 1;

	
	string strPN = to_string(m_iPlayerNumber);
	SetTag("Player" + strPN);
	CColliderRect* pColl = AddCollider<CColliderRect>("PlayerBody" + strPN);

	//pRC->AddCollisionFunction(CS_ENTER, this,
	//	&CPlayer::Hit);
	//pRC->AddCollisionFunction(CS_STAY, this,
	//	&CPlayer::HitStay);

	SAFE_RELEASE(pColl);

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
		}

		if (m_strArrowKeys.back() == "Right")
		{
			Move(m_fSpeed, 0, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveRight");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopRight");
		}

		if (m_strArrowKeys.back() == "Up")
		{
			Move(0, -m_fSpeed, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveUp");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopUp");
		}

		if (m_strArrowKeys.back() == "Down")
		{
			Move(0, m_fSpeed, fDeltaTime);
			m_pAnimation->ChangeClip(strPN + "P_" + "MoveDown");
			m_pAnimation->SetDefaultClip(strPN + "P_" + "StopDown");
		}
	}

	if (KEYDOWN("Fire"))
	{
	}

	if (KEYDOWN("Skill1"))
	{
		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
	}
}

int CPlayer::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	if (!m_bMove)
		m_pAnimation->ReturnClip();

	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
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