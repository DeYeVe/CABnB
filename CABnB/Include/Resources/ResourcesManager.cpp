#include "ResourcesManager.h"
#include "Texture.h"

DEFINITION_SINGLE(CResourcesManager)

CResourcesManager::CResourcesManager()
{
}


CResourcesManager::~CResourcesManager()
{
	SAFE_RELEASE(m_pBackBuffer);
	Safe_Release_Map(m_mapTexture);
}

CTexture * CResourcesManager::GetBackBuffer() const
{

	m_pBackBuffer->AddRef();
	return m_pBackBuffer;
}

bool CResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hInst = hInst;
	m_hDC = hDC;

	// 백버퍼를 불러온다.
	m_pBackBuffer = LoadTexture("BackBuffer", L"BackBuffer.bmp");
	LoadTexture("BlankBlock", L"Tile/BlankBlock.bmp");
	LoadTexture("BlankTile", L"Tile/BlankTile.bmp");
	LoadTexture("TownGround1", L"Tile/TownGround1.bmp");
	LoadTexture("TownGround2", L"Tile/TownGround2.bmp");
	LoadTexture("TownGround3", L"Tile/TownGround3.bmp");
	LoadTexture("TownGround4", L"Tile/TownGround4.bmp");
	LoadTexture("TownGround5", L"Tile/TownGround5.bmp");
	LoadTexture("TownGround6", L"Tile/TownGround6.bmp");
	LoadTexture("TownGround7", L"Tile/TownGround7.bmp");
	LoadTexture("TownBox", L"Tile/TownBox.bmp");
	LoadTexture("TownHouseBlue", L"Tile/TownHouseBlue.bmp");
	LoadTexture("TownHouseRed", L"Tile/TownHouseRed.bmp");
	LoadTexture("TownHouseYellow", L"Tile/TownHouseYellow.bmp");
	LoadTexture("TownBlockRed", L"Tile/TownBlockRed.bmp");
	LoadTexture("TownBlockYellow", L"Tile/TownBlockYellow.bmp");
	LoadTexture("TownBush", L"Tile/TownBush.bmp");
	LoadTexture("TownTree", L"Tile/TownTree.bmp");

	return true;
}

CTexture * CResourcesManager::LoadTexture(const string & strKey,
	const wchar_t * pFileName, const string & strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;
	
	if (!pTexture->LoadTexture(m_hInst, m_hDC, strKey, pFileName,
		strPathKey))
	{
		SAFE_RELEASE(pTexture);
		return NULL;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CTexture * CResourcesManager::LoadTexture(FILE * pFile)
{
	int iLength = 0;

	char	strKey[MAX_PATH] = {};
	char	strPathKey[MAX_PATH] = {};
	wchar_t	strFileName[MAX_PATH] = {};

	// key의 길이를 저장한다.
	fread(&iLength, 4, 1, pFile);
	fread(strKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	// FileName 저장
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strFileName, 2, iLength, pFile);
	strFileName[iLength] = 0;

	// PathKey 저장
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strPathKey[iLength] = 0;

	// ColorKey 
	bool		bColorKey = false;
	COLORREF	dwColorKey = 0;
	fread(&bColorKey, 1, 1, pFile);
	fread(&dwColorKey, sizeof(COLORREF), 1, pFile);

	CTexture* pTex = GET_SINGLE(CResourcesManager)->LoadTexture(strKey, strFileName, strPathKey);

	if (pTex && bColorKey)
		pTex->SetColorKey(dwColorKey);

	return pTex;
}

CTexture * CResourcesManager::FindTexture(const string & strKey)
{
	unordered_map<string, class CTexture*>::iterator iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return NULL;

	iter->second->AddRef();

	return iter->second;
}
