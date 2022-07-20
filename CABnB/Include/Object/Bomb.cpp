#include "Bomb.h"
#include "../Animation/Animation.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "Stream.h"
#include "../Collider/ColliderRect.h"
#include "../Sound/SoundManager.h"

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
	SetPos(0.f, 0.f);
	SetSize(44.f, 41.f);
	SetLifeTime(3.f);
	SetRange(0);

	GET_SINGLE(CSoundManager)->LoadSound("Explode", false, "se/explode.wav");

	CAnimation* pAni = CreateAnimation("BombAnimation");

	AddAnimationClip("Bomb", AT_ATLAS, AO_LOOP, 0.7f, 4, 1,
		0, 0, 4, 1, 0.f, "Bomb", L"Bomb/Bomb.bmp");
	SetAnimationClipColorKey("Bomb", 255, 0, 255);

	SAFE_RELEASE(pAni);

	return true;
}

void CBomb::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CBomb::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	m_fLifeTime -= fDeltaTime;

	if (m_fLifeTime <= 0)
		Explosion();

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
}

void CBomb::Explosion()
{
	GetPlayer()->AddBomb(1);

	CLayer* pLayer = GET_SINGLE(CSceneManager)->GetScene()->FindLayer("Stage");
	CStream* pStream = CObj::CreateObj<CStream>("Stream", pLayer);
	pStream->SetObjTag("Stream");
	pStream->SetRange(GetRange());

	POSITION pPos = GetPos();

	pStream->SetPos(pPos);
	pStream->SetDir(DIR_NONE);

	SAFE_RELEASE(pStream);

	GET_SINGLE(CSoundManager)->Play("Explode");

	Die();
}
