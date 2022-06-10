#include "RoomScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Core.h"
#include "SceneManager.h"
#include "../Core/PathManager.h"
#include "InGameScene.h"
#include "../Resources/ResourcesManager.h"

CRoomScene::CRoomScene()
{
}

CRoomScene::~CRoomScene()
{
}

bool CRoomScene::Init()
{
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("room", L"bg/room.bmp");

	SAFE_RELEASE(pBackPanel);

	// Start Button
	CUIButton*	pStartBtn = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartBtn->SetPos(512, 494);
	pStartBtn->SetSize(191, 55);
	pStartBtn->SetTexture("StartButton", L"UI/StartButton.bmp");
	pStartBtn->SetColorKey(255, 0, 255);
	pStartBtn->SetHasOffset(true);

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 191, 55);

	SAFE_RELEASE(pRC);

	pStartBtn->SetCallback(this, &CRoomScene::RoomStartButtonCallback);

	SAFE_RELEASE(pStartBtn);


	// Map Select Button
	CUIButton*	pMapSelectBtn = CObj::CreateObj<CUIButton>("MapSelectButton", pLayer);

	pMapSelectBtn->SetPos(646, 428);
	pMapSelectBtn->SetSize(123, 48);
	pMapSelectBtn->SetTexture("MapSelectButton", L"UI/MapSelectButton.bmp");
	pMapSelectBtn->SetColorKey(255, 0, 255);
	pMapSelectBtn->SetHasOffset(true);

	pRC = (CColliderRect*)pMapSelectBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 123, 48);

	SAFE_RELEASE(pRC);

	pMapSelectBtn->SetCallback(this, &CRoomScene::MapSelectButtonCallback);

	SAFE_RELEASE(pMapSelectBtn);

	return true;
}

void CRoomScene::RoomStartButtonCallback(float fTime, const string& strTag)
{
	GET_SINGLE(CSceneManager)->CreateScene<CInGameScene>(SC_NEXT);
}

void CRoomScene::MapSelectButtonCallback(float fTime, const string& strTag)
{
	ShowCursor(TRUE);

	HANDLE hFile;
	OPENFILENAME OFN;
	const wchar_t* strPath = GET_SINGLE(CPathManager)->FindPath(DATA_PATH);
	wchar_t mapPath[MAX_PATH] = L"";
	wcscat_s(mapPath, strPath);
	wcscat_s(mapPath, L"Map");
	TCHAR lpstrFile[MAX_PATH] = L"";

	memset(&OFN, 0, sizeof(OPENFILENAME));

	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = WINDOWHANDLE;
	OFN.lpstrInitialDir = mapPath;
	OFN.lpstrFilter = TEXT("Map(*.map)\0*.map\0ALL FILE(*.*)\0*.*\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;	
	if (GetOpenFileName(&OFN) != 0)
	{
		hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(WINDOWHANDLE, L"¸Ê ¼±ÅÃ ½ÇÆÐ", L"Error", MB_OK);
		}
		else
		{
			CloseHandle(hFile);

			char strFileName[MAX_PATH] = {};
			size_t i;
			wcstombs_s(&i, strFileName, MAX_PATH, lpstrFile, wcslen(lpstrFile) + 1);
			string strFilePath = strFileName;
			GET_SINGLE(CResourcesManager)->SetFileName(strFilePath);
		}
	}

	ShowCursor(FALSE);
}
