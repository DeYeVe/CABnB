#include "Tile.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"

CTile::CTile()
{
}

CTile::CTile(const CTile & tile) :
	CObj(tile)
{
	m_pTex = tile.m_pTex;

	if (m_pTex)
		m_pTex->AddRef();
}

CTile::~CTile()
{
	SAFE_RELEASE(m_pTex);
}

bool CTile::Init()
{
	return true;
}

void CTile::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CTile::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	m_pTex = m_pTexture;

	return 0;
}

int CTile::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CTile::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CTile::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
	POSITION	tPos = m_tPos - m_tSize * m_tPivot;

	tPos -= GET_SINGLE(CCamera)->GetPos();

	RESOLUTION tClientRS = GET_SINGLE(CCamera)->GetClientRS();

	bool bInClient = true;

	if (tPos.x + m_tSize.x < 0)
		bInClient = false;

	else if (tPos.x > tClientRS.iW)
		bInClient = false;

	else if (tPos.y + m_tSize.y < 0)
		bInClient = false;

	else if (tPos.y > tClientRS.iH)
		bInClient = false;

	if (m_pTex && bInClient)
	{
		POSITION	tImagePos;

		tImagePos += m_tImageOffset;

		if (m_pTex->GetColorKeyEnable())
		{
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y, m_pTex->GetDC(), tImagePos.x, tImagePos.y,
				m_tSize.x, m_tSize.y, m_pTex->GetColorKey());
		}

		else
		{
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y, m_pTex->GetDC(), tImagePos.x, tImagePos.y,
				SRCCOPY);
		}
	}
}

CTile * CTile::Clone()
{
	return new CTile(*this);
}

void CTile::Save(FILE * pFile)
{
	CObj::Save(pFile);
}

void CTile::Load(FILE * pFile)
{
	CObj::Load(pFile);
}
