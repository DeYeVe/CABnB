#include "Block.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"

CBlock::CBlock() :
	m_eType(BT_NORMAL)
{
}

CBlock::CBlock(const CBlock & block) :
	CObj(block)
{
	m_eType = block.m_eType;
	m_pTex = block.m_pTex;

	if (m_pTex)
		m_pTex->AddRef();
}

CBlock::~CBlock()
{
	SAFE_RELEASE(m_pTex);
}

void CBlock::SetBlockType(BLOCK_TYPE eType)
{
	m_eType = eType;
}

bool CBlock::Init()
{
	return true;
}

void CBlock::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CBlock::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	m_pTex = m_pTexture;
	return 0;
}

int CBlock::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBlock::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CBlock::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);POSITION	tPos = m_tPos - m_tSize * m_tPivot;

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

CBlock * CBlock::Clone()
{
	return new CBlock(*this);
}

void CBlock::Save(FILE * pFile)
{
	CObj::Save(pFile);

	fwrite(&m_eType, 4, 1, pFile);
}

void CBlock::Load(FILE * pFile)
{
	CObj::Load(pFile);

	fread(&m_eType, 4, 1, pFile);
}
