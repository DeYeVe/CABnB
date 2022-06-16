#include "InGameScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Core.h"
#include "SceneManager.h"
#include "../Core/Input.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../resource.h"
#include "../Core/PathManager.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "../Object/Tile.h"
#include "../Object/Block.h"
#include "../Object/Player.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
	if (!CScene::Init())
		return false;

	//UI
	CLayer* pUILayer = FindLayer("UI");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pUILayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("InGame", L"bg/InGame.bmp");
	pBackPanel->SetColorKey(255, 0, 255);

	//Stage
	CStage* pStageTile = CObj::CreateObj<CStage>("StageTile", FindLayer("StageTile"));
	
	CStage* pStageBlock = CObj::CreateObj<CStage>("StageBlock", FindLayer("StageBlock"));

	string strFileName = GET_SINGLE(CResourcesManager)->GetFileName();

	pStageTile->LoadFromFullPath(strFileName.c_str());
	pStageTile->EmptyBlock();
	pStageBlock->LoadFromFullPath(strFileName.c_str());
	pStageBlock->EmptyTile();
	pStageBlock->SetColorKey(255.f, 255.f, 255.f);

	// Default
	CLayer* pLayer = FindLayer("Default");

	// 1P
	POSITION	m_tStartPos = pStageBlock->GetStartPos() + (20.f, 20.f);
	CPlayer* pPlayer1 = CObj::CreateObj<CPlayer>("Player1", pLayer);
	pPlayer1->SetPos(m_tStartPos);

	CColliderRect* pRC = (CColliderRect*)pPlayer1->GetCollider("PlayerBody1");
	pRC->SetRect(-20.f, -20.f, 20.f, 20.f);

	// 2P
	m_tStartPos = pStageBlock->GetStartPos() + (20.f, 20.f);
	CPlayer* pPlayer2 = CObj::CreateObj<CPlayer>("Player2", pLayer);
	pPlayer2->SetPos(m_tStartPos);

	pRC = (CColliderRect*)pPlayer2->GetCollider("PlayerBody2");
	pRC->SetRect(-20.f, -20.f, 20.f, 20.f);

	SAFE_RELEASE(pRC);

	SAFE_RELEASE(pPlayer1);
	SAFE_RELEASE(pPlayer2);

	SAFE_RELEASE(pStageTile);
	SAFE_RELEASE(pStageBlock);

	return true;
}

int CInGameScene::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	return 0;
}

int CInGameScene::LateUpdate(float fDeltaTime)
{
	CScene::LateUpdate(fDeltaTime);

	return 0;
}
