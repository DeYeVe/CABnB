#include "UIMessage.h"

CUIMessage::CUIMessage()
{
}

CUIMessage::CUIMessage(const CUIMessage & ui) :
	CUI(ui)
{
}

CUIMessage::~CUIMessage()
{
}

bool CUIMessage::Init()
{
	m_fUILifeTime = 4.0f;

	return true;
}

void CUIMessage::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUIMessage::Update(float fDeltaTime)
{
	m_fUILifeTime -= fDeltaTime;

	if (m_fUILifeTime < 0.0f)
	{
		Die();
	}
	else if (m_fUILifeTime < 1.0f)
	{
		SetPos(GetPos().x, -79.f + m_fUILifeTime * 200.f);
	}
	else if (m_fUILifeTime > 3.0f)
	{
		SetPos(GetPos().x, -79.f + (1.f - (m_fUILifeTime - 3.f)) * 200.f);
	}

	CUI::Update(fDeltaTime);
	return 0;
}

int CUIMessage::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CUIMessage::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUIMessage::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CUIMessage * CUIMessage::Clone()
{
	return new CUIMessage(*this);
}
