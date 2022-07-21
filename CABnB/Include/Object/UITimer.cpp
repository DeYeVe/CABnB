#include "UITimer.h"
#include "../Scene/Layer.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"

CUITimer::CUITimer()
{
}

CUITimer::CUITimer(const CUITimer & ui) :
	CUI(ui)
{
}

CUITimer::~CUITimer()
{
}

bool CUITimer::Init()
{
	m_fInGameTime = 180.0f;
	SetPos(0.f, 0.f);
	SetSize(0.f, 0.f);
/*
	m_pMinute->SetPos(725.f, 78.f);
	
	m_pSecondTen->SetPos(743.f, 78.f);

	m_pSecondOne->SetPos(757.f, 78.f);*/

	return true;
}

void CUITimer::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CUITimer::Update(float fDeltaTime)
{
	m_fInGameTime -= fDeltaTime;

	int iMinute = (int)(m_fInGameTime) / 60;
	int iSecondTen = (int)(m_fInGameTime) % 60 / 10;
	int iSecondOne = (int)(m_fInGameTime) % 60 % 10;
	
	m_pMinute = GET_SINGLE(CResourcesManager)->LoadTexture("digit_" + to_string(iMinute), 
		StringToWstring("UI/digit_" + to_string(iMinute) + ".bmp").c_str());
	m_pMinute->SetColorKey(255, 0, 255);

	m_pSecondTen = GET_SINGLE(CResourcesManager)->LoadTexture("digit_" + to_string(iSecondTen),
		StringToWstring("UI/digit_" + to_string(iSecondTen) + ".bmp").c_str());
	m_pSecondTen->SetColorKey(255, 0, 255);

	m_pSecondOne = GET_SINGLE(CResourcesManager)->LoadTexture("digit_" + to_string(iSecondOne),
		StringToWstring("UI/digit_" + to_string(iSecondOne) + ".bmp").c_str());
	m_pSecondOne->SetColorKey(255, 0, 255);

	CUI::Update(fDeltaTime);
	return 0;
}

int CUITimer::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CUITimer::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CUITimer::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);

	TransparentBlt(hDC, 725.f, 78.f, 12.f,
		10.f, m_pMinute->GetDC(), 0.f, 0.f,
		12.f, 10.f, m_pMinute->GetColorKey());

	TransparentBlt(hDC, 743.f, 78.f, 12.f,
		10.f, m_pSecondTen->GetDC(), 0.f, 0.f,
		12.f, 10.f, m_pSecondTen->GetColorKey());

	TransparentBlt(hDC, 757.f, 78.f, 12.f,
		10.f, m_pSecondOne->GetDC(), 0.f, 0.f,
		12.f, 10.f, m_pSecondOne->GetColorKey());
}

CUITimer * CUITimer::Clone()
{
	return new CUITimer(*this);
}
