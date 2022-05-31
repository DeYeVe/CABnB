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
	SetPos(50.f, 50.f);
	SetSize(44.f, 58.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetDir(DIR_DOWN);
	SetSpeed(0.1f);
	SetBubbles(1);
	SetRange(1);
	if (CObj::FindObject("Player1"))
		m_iPlayerNumber = 2;
	else 
		m_iPlayerNumber = 1;

	
	string strPN = to_string(m_iPlayerNumber);
	SetTag("Player" + strPN);
	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody" + strPN);

	pRC->SetRect(-10.f, -10.f, 10.f, 10.f);
	//pRC->AddCollisionFunction(CS_ENTER, this,
	//	&CPlayer::Hit);
	//pRC->AddCollisionFunction(CS_STAY, this,
	//	&CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	CAnimation* pAni = CreateAnimation("Player" + strPN + "Animation");

	AddAnimationClip("MoveDown", AT_ATLAS, AO_LOOP, 1.0f, 4, 1,
		0, 0, 4, 1, 0.f, "PlayerMoveDown", StringToWstring("Player/" + strPN + "P/MoveDown.bmp").c_str());
	SetAnimationClipColorKey("MoveDown", 255, 0, 255);


	vector<wstring> vecFileName;

	for (int i = 1; i <= 3; ++i)
	{
		wchar_t strFileName[MAX_PATH] = {};
		wsprintf(strFileName, L"Player/Attack/Left/%d.bmp", i);
		vecFileName.push_back(strFileName);
	}

	AddAnimationClip("NormalAttackLeft", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1,
		0, 0, 3, 1, 0.f, "PlayerAttackLeft",
		vecFileName);
	SetAnimationClipColorKey("NormalAttackLeft", 255, 255, 255);



	SAFE_RELEASE(pAni);

	return true;
}

void CPlayer::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);

	if (KEYDOWN("MoveFront"))
	{
		//MoveYFromSpeed(fDeltaTime, MD_BACK);
	}

	if (KEYPRESS("MoveBack"))
	{
		//MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYPRESS("MoveLeft"))
	{/*
		MoveXFromSpeed(fDeltaTime, MD_BACK);
		m_pAnimation->ChangeClip("RunLeft");
		m_iDir = -1;
		m_pAnimation->SetDefaultClip("IdleLeft");*/
	}

	if (KEYPRESS("MoveRight"))
	{
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
}


