#include "Bomb.h"

CBomb::CBomb() :
	m_fLifeTime(0.f)
{
}

CBomb::CBomb(const CBomb & bomb) :
	CObj(bomb)
{
	m_fLifeTime = bomb.GetLifeTime();
}

CBomb::~CBomb()
{
}

bool CBomb::Init()
{
	return true;
}

void CBomb::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CBomb::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	return 0;
}

int CBomb::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBomb::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CBomb::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
}

CBomb * CBomb::Clone()
{
	return new CBomb(*this);
	return nullptr;
}
