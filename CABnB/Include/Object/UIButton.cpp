#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Input.h"
#include "../Sound/SoundManager.h"

CUIButton::CUIButton() :
	m_bEnableCallback(false),
	m_eState(BS_NONE)
{
}

CUIButton::CUIButton(const CUIButton & ui) :
	CUI(ui)
{
	m_bEnableCallback = false;
	m_eState = BS_NONE;
	m_bHasOffset = false;
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
	GET_SINGLE(CSoundManager)->LoadSound("Button", false, "se/button.wav");

	CColliderRect* pColl = AddCollider<CColliderRect>("ButtonBody");

	pColl->AddCollisionFunction(CS_ENTER, this, &CUIButton::MouseOn);
	pColl->AddCollisionFunction(CS_LEAVE, this, &CUIButton::MouseOut);

	SAFE_RELEASE(pColl);

	m_bHasOffset = false;

	return true;
}

void CUIButton::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);
	return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE)
	{
		if (KEYPRESS("MouseLButton"))
		{
			m_eState = BS_CLICK;
			if (m_bHasOffset)
				SetImageOffset(m_tSize.x * 2.f, 0.f);
		}
	}

	if (m_eState == BS_CLICK && KEYUP("MouseLButton"))
	{
		m_eState = BS_MOUSEON;
		if (m_bHasOffset)
			SetImageOffset(m_tSize.x, 0.f);
		if (m_bEnableCallback)
			m_BtnCallback(fDeltaTime, GetTag());
	}

	return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CUIButton * CUIButton::Clone()
{
	return new CUIButton(*this);
}

void CUIButton::MouseOn(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if(pDest->GetTag() == "Mouse")
		m_eState = BS_MOUSEON;

	if (m_bHasOffset)
		SetImageOffset(m_tSize.x, 0.f);

	GET_SINGLE(CSoundManager)->Play("Button");
}

void CUIButton::MouseOut(CCollider * pSrc, CCollider * pDest, float fDeltaTime)
{
	if (pDest->GetTag() == "Mouse")
	{
		m_eState = BS_NONE;

		if (m_bHasOffset)
			SetImageOffset(0.f, 0.f);
	}
}
