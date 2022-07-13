#include "MapEditScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Core.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "../Core/Input.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../resource.h"
#include "../Core/PathManager.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "../Object/Tile.h"
#include "../Object/Block.h"

wchar_t CMapEditScene::m_strText[MAX_PATH] = {};

CMapEditScene::CMapEditScene()
{
}

CMapEditScene::~CMapEditScene()
{
	SAFE_RELEASE(m_pStage);
}

bool CMapEditScene::Init()
{
	if (!CScene::Init())
		return false;

	GET_SINGLE(CInput)->SetBorder(true);

	CLayer* pLayer = FindLayer("UI");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("Edit", L"bg/Edit.bmp");
	pBackPanel->SetColorKey(255, 0, 255);

	SAFE_RELEASE(pBackPanel);

	CLayer* pStageLayer = FindLayer("Stage");

	m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	m_pStage->SetTileVisible(true);
	m_pStage->SetBlockVisible(true);

	m_pStage->CreateTile(15, 13, 40, "BlankTile", L"Tile/BlankTile.bmp");
	m_pStage->CreateBlock(15, 13, 40, "BlankBlockCK", L"Tile/BlankBlock.bmp");
	m_bIsTile = true;

	m_pSelectedTile = CObj::CreateObj<CTile>("SelectedTile", pLayer);
	m_pSelectedTile->SetTexture("BlankTile");
	m_pSelectedTile->SetPos(697, 68);
	m_pSelectedTile->SetSize(40, 40);

	m_pSelectedBlock = CObj::CreateObj<CBlock>("SelectedBlock", pLayer);
	m_pSelectedBlock->SetLayer(NULL);
	m_pSelectedBlock->SetTexture("BlankBlock", L"Tile/BlankBlock.bmp");
	m_pSelectedBlock->SetPos(697, 68);
	m_pSelectedBlock->SetSize(40, 40);

	GET_SINGLE(CInput)->AddKey("Save", 'S', VK_CONTROL);
	GET_SINGLE(CInput)->AddKey("Load", 'O', VK_CONTROL);

	// Buttons
	// Exit Button
	CUIButton*	pExitBtn = CObj::CreateObj<CUIButton>("ExitButton", pLayer);

	pExitBtn->SetPos(647, 561);
	pExitBtn->SetSize(140, 32);
	pExitBtn->SetTexture("ExitButton", L"UI/ExitButton.bmp");
	pExitBtn->SetColorKey(255, 0, 255);
	pExitBtn->SetHasOffset(true);

	CColliderRect* pRC = (CColliderRect*)pExitBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 140, 32);

	SAFE_RELEASE(pRC);

	pExitBtn->SetCallback(this, &CMapEditScene::ExitButtonCallback);

	SAFE_RELEASE(pExitBtn);

	// Save Button
	CUIButton*	pSaveBtn = CObj::CreateObj<CUIButton>("SaveButton", pLayer);

	pSaveBtn->SetPos(700, 500);
	pSaveBtn->SetSize(85, 44);
	pSaveBtn->SetTexture("SaveButton", L"UI/SaveButton.bmp");
	pSaveBtn->SetColorKey(255, 0, 255);
	pSaveBtn->SetHasOffset(true);

	pRC = (CColliderRect*)pSaveBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 85, 44);

	SAFE_RELEASE(pRC);

	pSaveBtn->SetCallback(this, &CMapEditScene::SaveButtonCallback);

	SAFE_RELEASE(pExitBtn);

	// Tile
	for (int i = 1; i <= 7; ++i)
	{
		CUIButton*	pTileBtn = CObj::CreateObj<CUIButton>("TownGround" + to_string(i), pLayer);

		int iPosX, iPosY;
		iPosX = ((i - 1) % 3) * 48;
		iPosY = ((i - 1) / 3) * 60;
		pTileBtn->SetPos(649 + iPosX, 145 + iPosY);
		pTileBtn->SetSize(40, 40);
		
		string str = "Tile/TownGround" + to_string(i) + ".bmp";

		pTileBtn->SetTexture("TownGround" + to_string(i),
			(const wchar_t *) wstring(str.begin(), str.end()).c_str());
		pTileBtn->SetColorKey(255, 0, 255);
		
		CColliderRect* pRC = (CColliderRect*)pTileBtn->GetCollider("ButtonBody");

		pRC->SetRect(0.f, 0.f, 40, 40);

		pTileBtn->SetCallback(this, &CMapEditScene::TileButtonCallback);

		SAFE_RELEASE(pRC);
		SAFE_RELEASE(pTileBtn);
	}

	// Block
	// BlankBlock
	CUIButton*	pBlockBtn = CObj::CreateObj<CUIButton>("BlankBlock", pLayer);

	pBlockBtn->SetPos(649, 145 + 60 * 3);
	pBlockBtn->SetSize(40, 40);
	pBlockBtn->SetTexture("BlankBlockCK", L"Tile/BlankBlock.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("BlankBlock", L"Tile/BlankBlock.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 40);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// Start
	pBlockBtn = CObj::CreateObj<CUIButton>("Start", pLayer);

	pBlockBtn->SetPos(649 + 48, 145 + 60 * 3);
	pBlockBtn->SetSize(40, 40);
	pBlockBtn->SetTexture("StartCK", L"Tile/Start.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("Start", L"Tile/Start.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 40);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownBox
	pBlockBtn = CObj::CreateObj<CUIButton>("TownBox", pLayer);

	pBlockBtn->SetPos(649 + 48 * 2, 141 + 60 * 3);
	pBlockBtn->SetSize(40, 44);
	pBlockBtn->SetTexture("TownBoxCK", L"Tile/TownBox.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownBox", L"Tile/TownBox.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 44);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownHouseBlue
	pBlockBtn = CObj::CreateObj<CUIButton>("TownHouseBlue", pLayer);

	pBlockBtn->SetPos(649, 128 + 60 * 4);
	pBlockBtn->SetSize(40, 57);
	pBlockBtn->SetTexture("TownHouseBlueCK", L"Tile/TownHouseBlue.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownHouseBlue", L"Tile/TownHouseBlue.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 57);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownHouseRed
	pBlockBtn = CObj::CreateObj<CUIButton>("TownHouseRed", pLayer);

	pBlockBtn->SetPos(649 + 48, 128 + 60 * 4);
	pBlockBtn->SetSize(40, 57);
	pBlockBtn->SetTexture("TownHouseRedCK", L"Tile/TownHouseRed.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownHouseRed", L"Tile/TownHouseRed.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 57);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownHouseYellow
	pBlockBtn = CObj::CreateObj<CUIButton>("TownHouseYellow", pLayer);

	pBlockBtn->SetPos(649 + 48 * 2, 128 + 60 * 4);
	pBlockBtn->SetSize(40, 57);
	pBlockBtn->SetTexture("TownHouseYellowCK", L"Tile/TownHouseYellow.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownHouseYellow", L"Tile/TownHouseYellow.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 57);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownBlockRed
	pBlockBtn = CObj::CreateObj<CUIButton>("TownBlockRed", pLayer);

	pBlockBtn->SetPos(649, 128 + 60 * 5);
	pBlockBtn->SetSize(40, 44);
	pBlockBtn->SetTexture("TownBlockRedCK", L"Tile/TownBlockRed.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownBlockRed", L"Tile/TownBlockRed.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 44);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	// TownBlockYellow
	pBlockBtn = CObj::CreateObj<CUIButton>("TownBlockYellow", pLayer);

	pBlockBtn->SetPos(649 + 48, 128 + 60 * 5);
	pBlockBtn->SetSize(40, 44);
	pBlockBtn->SetTexture("TownBlockYellowCK", L"Tile/TownBlockYellow.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownBlockYellow", L"Tile/TownBlockYellow.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 44);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);
	// TownBush
	pBlockBtn = CObj::CreateObj<CUIButton>("TownBush", pLayer);

	pBlockBtn->SetPos(649 + 48 * 2, 128 + 60 * 5);
	pBlockBtn->SetSize(40, 57);
	pBlockBtn->SetTexture("TownBushCK", L"Tile/TownBush.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownBush", L"Tile/TownBush.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 57);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);


	// TownTree
	pBlockBtn = CObj::CreateObj<CUIButton>("TownTree", pLayer);

	pBlockBtn->SetPos(649, 118 + 60 * 6);
	pBlockBtn->SetSize(40, 67);
	pBlockBtn->SetTexture("TownTreeCK", L"Tile/TownTree.bmp");
	pBlockBtn->SetColorKey(200, 200, 200);
	pBlockBtn->SetTexture("TownTree", L"Tile/TownTree.bmp");
	pBlockBtn->SetColorKey(1.0f, 1.0f, 1.0f);

	pRC = (CColliderRect*)pBlockBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 40, 67);

	pBlockBtn->SetCallback(this, &CMapEditScene::BlockButtonCallback);

	SAFE_RELEASE(pRC);
	SAFE_RELEASE(pBlockBtn);

	return true;
}

void CMapEditScene::Input(float fDeltaTime)
{
	CScene::Input(fDeltaTime);

	if (KEYPRESS("MouseLButton"))
	{
		POSITION	tMouseWorldPos = MOUSEWORLDPOS;

		if (m_bIsTile)
		{
			m_pStage->SetTile(tMouseWorldPos, m_pSelectedTile->GetTexture());
		}
		else
		{
			m_pStage->SetBlock(tMouseWorldPos, m_pSelectedBlock->GetTag(),
				m_pSelectedBlock->GetBlockType(), m_pSelectedBlock->GetSize().y);
		}
	}
}

void CMapEditScene::ExitButtonCallback(float fTime, const string & strTag)
{
	GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

void CMapEditScene::SaveButtonCallback(float fTime, const string & strTag)
{
	ShowCursor(TRUE);
	DialogBox(WINDOWINSTANCE, MAKEINTRESOURCE(IDD_DIALOG1),
		WINDOWHANDLE, CMapEditScene::DlgProc);

	ShowCursor(FALSE);

	char	strFileName[MAX_PATH] = {};
	WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName,
		lstrlen(m_strText), 0, 0);

	m_pStage->SaveFromPath(strFileName);
}

void CMapEditScene::TileButtonCallback(float fTime, const string& strTag)
{
	CLayer* pLayer = FindLayer("UI");

	if (m_pSelectedBlock)
	{
		m_pSelectedBlock->SetTexture("BlankBlockCK");
	}

	if (m_pSelectedTile)
	{
		m_pSelectedTile->SetTag(strTag);
		m_pSelectedTile->SetTexture(strTag);
		m_pSelectedTile->SetPos(697, 68);
		m_pSelectedTile->SetSize(40, 40);
	}

	m_bIsTile = true;
}

void CMapEditScene::BlockButtonCallback(float fTime, const string& strTag)
{
	CLayer* pLayer = FindLayer("UI");

	if (m_pSelectedTile)
	{
		m_pSelectedTile->SetTexture("BlankTile");
	}

	if (m_pSelectedBlock)
	{
		m_pSelectedBlock->SetTag(strTag);
		m_pSelectedBlock->SetTexture(strTag);

		if (strTag == "Start")
		{
			m_pSelectedBlock->SetBlockType(BT_START);
			m_pSelectedBlock->SetPos(697, 68);
			m_pSelectedBlock->SetSize(40, 40);
		}
		else if (strTag == "BlankBlock")
		{
			m_pSelectedBlock->SetBlockType(BT_BLANK);
			m_pSelectedBlock->SetPos(697, 68);
			m_pSelectedBlock->SetSize(40, 40);
		}
		else if (strTag == "TownBlockRed" || strTag == "TownBlockYellow")
		{
			m_pSelectedBlock->SetBlockType(BT_NORMAL);
			m_pSelectedBlock->SetPos(697, 66);
			m_pSelectedBlock->SetSize(40, 44);

		}
		else if (strTag == "TownBox")
		{
			m_pSelectedBlock->SetBlockType(BT_BOX);
			m_pSelectedBlock->SetPos(697, 66);
			m_pSelectedBlock->SetSize(40, 44);

		}
		else if (strTag == "TownBush")
		{
			m_pSelectedBlock->SetBlockType(BT_BUSH);
			m_pSelectedBlock->SetPos(697, 60);
			m_pSelectedBlock->SetSize(40, 57);

		}
		else if (strTag == "TownHouseBlue" || strTag == "TownHouseRed" || strTag == "TownHouseYellow")
		{
			m_pSelectedBlock->SetBlockType(BT_UNBRK);
			m_pSelectedBlock->SetPos(697, 60);
			m_pSelectedBlock->SetSize(40, 57);

		}
		else if (strTag == "TownTree")
		{
			m_pSelectedBlock->SetBlockType(BT_UNBRK);
			m_pSelectedBlock->SetPos(697, 50);
			m_pSelectedBlock->SetSize(40, 67);

		}

		m_pSelectedBlock->SetColorKey(1.0f, 1.0f, 1.0f);
	}

	m_bIsTile = false;
}

INT_PTR CMapEditScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			memset(m_strText, 0, sizeof(wchar_t) * MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDIT1, m_strText, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return FALSE;
	}

	return FALSE();
}
