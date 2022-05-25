#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core/Core.h"
#include "../Core/Camera.h"
#include "Tile.h"
#include "Block.h"
#include "../Scene/Layer.h"
#include "../Core/PathManager.h"
#include "../Core/Input.h"

CStage::CStage()
{
}

CStage::CStage(const CStage & stage) :
	CObj(stage)
{
	m_vecTile.clear();

	for (size_t i = 0; i < stage.m_vecTile.size(); ++i)
	{
		m_vecTile.push_back(stage.m_vecTile[i]->Clone());
	}

	m_vecBlock.clear();

	for (size_t i = 0; i < stage.m_vecBlock.size(); ++i)
	{
		m_vecBlock.push_back(stage.m_vecBlock[i]->Clone());
	}
}

CStage::~CStage()
{
	ClearTile();
}

void CStage::CreateTile(int iNumX, int iNumY,
	int iSize, const string & strKey,
	const wchar_t * pFileName, const string & strPathKey)
{
	ClearTile();

	m_iTileNumX = iNumX;
	m_iTileNumY = iNumY;
	m_iTileSize = iSize;

	for (int i = 0; i < iNumY; ++i)
	{
		for (int j = 0; j < iNumX; ++j)
		{
			CTile* pTile = CObj::CreateObj<CTile>("Tile");

			pTile->SetSize(iSize, iSize);
			pTile->SetPos(GetPos().x + j * iSize, GetPos().y + i * iSize);

			pTile->SetTexture(strKey, pFileName, strPathKey);
			pTile->SetColorKey(0, 0, 0);

			m_vecTile.push_back(pTile);
		}
	}
}

void CStage::SetTile(const POSITION & tPos, CTexture * pTexture)
{
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1)
		return;

	m_vecTile[iIndex]->SetTexture(pTexture);
}

void CStage::CreateBlock(int iNumX, int iNumY,
	int iSize, const string & strKey,
	const wchar_t * pFileName, const string & strPathKey)
{
	ClearBlock();

	m_iBlockNumX = iNumX;
	m_iBlockNumY = iNumY;
	m_iBlockSize = iSize;

	for (int i = 0; i < iNumY; ++i)
	{
		for (int j = 0; j < iNumX; ++j)
		{
			CBlock* pBlock = CObj::CreateObj<CBlock>("Block");

			pBlock->SetSize(iSize, iSize);
			pBlock->SetPos(GetPos().x + j * iSize, GetPos().y + i * iSize);

			pBlock->SetTexture(strKey, pFileName, strPathKey);
			pBlock->SetColorKey(200, 200, 200);

			m_vecBlock.push_back(pBlock);
		}
	}
}

void CStage::SetBlock(const POSITION & tPos, const string & strTag, BLOCK_TYPE eBT, int iHeigth)
{
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1)
		return;
	if (m_vecBlock[iIndex]->GetTag() == strTag)
		return;

	m_vecBlock[iIndex]->SetTag(strTag);
	m_vecBlock[iIndex]->SetTexture(strTag + "CK");
	m_vecBlock[iIndex]->SetBlockType(eBT);
	m_vecBlock[iIndex]->SetSize(m_vecBlock[iIndex]->GetSize().x, iHeigth);
	m_vecBlock[iIndex]->SetPos(m_vecBlock[iIndex]->GetPos().x,
		m_tPos.y + (iIndex / 15) * 40 - (iHeigth - 40));
}


bool CStage::Init()
{
	SetPos(20.f, 41.f);
	SetSize(600.f, 520.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage", L"bg/Stage.bmp");

	return true;
}

void CStage::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime)
{
	CObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture)
	{
		POSITION	tPos = m_tPos - m_tSize * m_tPivot;
		POSITION	tCamPos = GET_SINGLE(CCamera)->GetPos();

		BitBlt(hDC, tPos.x, tPos.y, GETRESOLUTION.iW,
			GETRESOLUTION.iH, m_pTexture->GetDC(), tCamPos.x, tCamPos.y,
			SRCCOPY);

		for (size_t i = 0; i < m_vecTile.size(); ++i)
		{
			m_vecTile[i]->Render(hDC, fDeltaTime);
		}

		for (size_t i = 0; i < m_vecBlock.size(); ++i)
		{
			m_vecBlock[i]->Render(hDC, fDeltaTime);
		}
		
		for (int i = 1; i < m_iTileNumX; ++i)
		{
			MoveToEx(hDC, GetPos().x + i * m_iTileSize, GetPos().y, NULL);
			LineTo(hDC, GetPos().x + i * m_iTileSize,
				GetPos().y + m_iTileNumY * m_iTileSize);
		}
		for (int i = 1; i < m_iTileNumY; ++i)
		{
			MoveToEx(hDC, GetPos().x, GetPos().y + i * m_iTileSize, NULL);
			LineTo(hDC, GetPos().x + m_iTileNumX * m_iTileSize,
				GetPos().y + i * m_iTileSize);
		}
	}
}

CStage * CStage::Clone()
{
	return new CStage(*this);
}

void CStage::Save(FILE * pFile)
{
	CObj::Save(pFile);

	fwrite(&m_iTileSize, 4, 1, pFile);
	fwrite(&m_iTileNumX, 4, 1, pFile);
	fwrite(&m_iTileNumY, 4, 1, pFile);
	fwrite(&m_iBlockSize, 4, 1, pFile);
	fwrite(&m_iBlockNumX, 4, 1, pFile);
	fwrite(&m_iBlockNumY, 4, 1, pFile);

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		m_vecTile[i]->Save(pFile);
	}

	for (size_t i = 0; i < m_vecBlock.size(); ++i)
	{
		m_vecBlock[i]->Save(pFile);
	}
}

void CStage::Load(FILE * pFile)
{
	CObj::Load(pFile);

	fread(&m_iTileSize, 4, 1, pFile);
	fread(&m_iTileNumX, 4, 1, pFile);
	fread(&m_iTileNumY, 4, 1, pFile);
	fread(&m_iBlockSize, 4, 1, pFile);
	fread(&m_iBlockNumX, 4, 1, pFile);
	fread(&m_iBlockNumY, 4, 1, pFile);

	ClearTile();

	for (int i = 0; i < m_iTileNumX * m_iTileNumY; ++i)
	{
		CTile* pTile = CObj::CreateObj<CTile>("Tile");

		pTile->Load(pFile);

		m_vecTile.push_back(pTile);
	}

	ClearBlock();

	for (int i = 0; i < m_iBlockNumX * m_iBlockNumY; ++i)
	{
		CBlock* pBlock = CObj::CreateObj<CBlock>("Block");

		pBlock->Load(pFile);

		m_vecBlock.push_back(pBlock);
	}
}

int CStage::GetTileIndex(const POSITION & tPos)
{
	return GetTileIndex(tPos.x, tPos.y);
}

int CStage::GetTileIndex(float x, float y)
{
	x -= m_tPos.x;
	y -= m_tPos.y;
	int idxX = (int)x / m_iTileSize;
	int idxY = (int)y / m_iTileSize;

	if (idxX < 0 || idxX >= m_iTileNumX)
		return -1;

	else if (idxY < 0 || idxY >= m_iTileNumY)
		return -1;

	return idxY * m_iTileNumX + idxX;
}

void CStage::ClearTile()
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		CObj::EraseObj(m_vecTile[i]);
	}

	Safe_Release_VecList(m_vecTile);
}

void CStage::ClearBlock()
{
	for (size_t i = 0; i < m_vecBlock.size(); ++i)
	{
		CObj::EraseObj(m_vecBlock[1]);
	}

	Safe_Release_VecList(m_vecBlock);
}