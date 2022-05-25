//#include "Player.h"
//#include "../Core/Input.h"
//#include "../Collider/ColliderRect.h"
//#include "../Core/Camera.h"
//#include "../Animation/Animation.h"
//#include "../Scene/Scene.h"
//
//CPlayer::CPlayer()
//{
//}
//
//CPlayer::CPlayer(const CPlayer & player) :
//	CObj(player)
//{
//}
//
//CPlayer::~CPlayer()
//{
//}
//
//bool CPlayer::Init()
//{
//	SetPos(50.f, 50.f);
//	SetSize(80.f, 80.f);
//	SetSpeed(400.f);
//	SetPivot(0.5f, 0.5f);
//	SetImageOffset(0.f, 0.f);
//
//	//SetTexture("Player", L"HOS.bmp");
//	//SetColorKey(255, 255, 255);
//
//	CColliderRect* pRC = AddCollider<CColliderRect>("PlayerBody");
//
//	pRC->SetRect(-40.f, -40.f, 40.f, 40.f);
//	pRC->AddCollisionFunction(CS_ENTER, this,
//		&CPlayer::Hit);
//	pRC->AddCollisionFunction(CS_STAY, this,
//		&CPlayer::HitStay);
//
//	SAFE_RELEASE(pRC);
//
//	m_iDir = 1;
//
//	m_iHP = 1000;
//
//	// 중력을 적용한다.
//	SetPhysics(true);
//
//	// 점프할 힘을 설정한다.
//	SetForce(200.f);
//
//	CAnimation* pAni = CreateAnimation("PlayerAnimation");
//
//	AddAnimationClip("IdleRight", AT_ATLAS, AO_LOOP, 1.0f, 10, 1,
//		0, 0, 10, 1, 0.f, "PlayerIdleRight", L"Player/Idle/Right/Player_Stand_Right.bmp");
//	SetAnimationClipColorKey("IdleRight", 255, 255, 255);
//
//	AddAnimationClip("IdleLeft", AT_ATLAS, AO_LOOP, 1.0f, 10, 1,
//		0, 0, 10, 1, 0.f, "PlayerIdleLeft", L"Player/Idle/Left/Player_Stand_Left.bmp");
//	SetAnimationClipColorKey("IdleLeft", 255, 255, 255);
//
//	AddAnimationClip("RunRight", AT_ATLAS, AO_ONCE_RETURN, 0.4f, 4, 1,
//		0, 0, 4, 1, 0.f, "PlayerRunRight", L"Player/Run/Right/Player_Run_Right.bmp");
//	SetAnimationClipColorKey("RunRight", 255, 255, 255);
//
//	AddAnimationClip("RunLeft", AT_ATLAS, AO_ONCE_RETURN, 0.4f, 4, 1,
//		0, 0, 4, 1, 0.f, "PlayerRunLeft", L"Player/Run/Left/Player_Run_Left.bmp");
//	SetAnimationClipColorKey("RunLeft", 255, 255, 255);
//
//	AddAnimationClip("NormalAttackRight", AT_ATLAS, AO_ONCE_RETURN, 0.4f, 3, 1,
//		0, 0, 3, 1, 0.f, "PlayerAttackRight", L"Player/Attack/Right/Player_Attack_Right.bmp");
//	SetAnimationClipColorKey("NormalAttackRight", 255, 255, 255);
//
//	vector<wstring> vecFileName;
//
//	for (int i = 1; i <= 3; ++i)
//	{
//		wchar_t strFileName[MAX_PATH] = {};
//		wsprintf(strFileName, L"Player/Attack/Left/%d.bmp", i);
//		vecFileName.push_back(strFileName);
//	}
//
//	AddAnimationClip("NormalAttackLeft", AT_FRAME, AO_ONCE_RETURN, 0.4f, 3, 1,
//		0, 0, 3, 1, 0.f, "PlayerAttackLeft",
//		vecFileName);
//	SetAnimationClipColorKey("NormalAttackLeft", 255, 255, 255);
//
//
//
//	SAFE_RELEASE(pAni);
//
//	return true;
//}
//
//void CPlayer::Input(float fDeltaTime)
//{
//	CMoveObj::Input(fDeltaTime);
//
//	if (KEYDOWN("MoveFront"))
//	{
//		Jump();
//		//MoveYFromSpeed(fDeltaTime, MD_BACK);
//	}
//
//	if (KEYPRESS("MoveBack"))
//	{
//		//MoveYFromSpeed(fDeltaTime, MD_FRONT);
//	}
//
//	if (KEYPRESS("MoveLeft"))
//	{
//		MoveXFromSpeed(fDeltaTime, MD_BACK);
//		m_pAnimation->ChangeClip("RunLeft");
//		m_iDir = -1;
//		m_pAnimation->SetDefaultClip("IdleLeft");
//	}
//
//	if (KEYPRESS("MoveRight"))
//	{
//		MoveXFromSpeed(fDeltaTime, MD_FRONT);
//		m_pAnimation->ChangeClip("RunRight");
//		m_iDir = 1;
//		m_pAnimation->SetDefaultClip("IdleRight");
//	}
//
//	if (KEYDOWN("Fire"))
//	{
//		Fire();
//		if (m_iDir == -1)
//			m_pAnimation->ChangeClip("NormalAttackLeft");
//
//		else if (m_iDir == 1)
//			m_pAnimation->ChangeClip("NormalAttackRight");
//	}
//
//	if (KEYDOWN("Skill1"))
//	{
//		MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
//	}
//}
//
//int CPlayer::Update(float fDeltaTime)
//{
//	CMoveObj::Update(fDeltaTime);
//
//	if (!m_bMove && m_pAnimation->GetMotionEnd())
//		m_bAttack = false;
//
//	if (!m_bMove && !m_bAttack)
//		m_pAnimation->ReturnClip();
//
//	return 0;
//}
//
//int CPlayer::LateUpdate(float fDeltaTime)
//{
//	CMoveObj::LateUpdate(fDeltaTime);
//	return 0;
//}
//
//void CPlayer::Collision(float fDeltaTime)
//{
//	CMoveObj::Collision(fDeltaTime);
//}
//
//void CPlayer::Render(HDC hDC, float fDeltaTime)
//{
//	CMoveObj::Render(hDC, fDeltaTime);
//	wchar_t strHP[32] = {};
//	wsprintf(strHP, L"HP : %d", m_iHP);
//	POSITION	tPos = m_tPos - m_tSize * m_tPivot;
//	tPos -= GET_SINGLE(CCamera)->GetPos();
//	TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP));
//}
//
//CPlayer * CPlayer::Clone()
//{
//	return new CPlayer(*this);
//}
//
//void CPlayer::Move(float x, float y, float fDeltaTime)
//{
//	m_tPos.x += x * fDeltaTime;
//	m_tPos.y += y * fDeltaTime;
//}
//
//
