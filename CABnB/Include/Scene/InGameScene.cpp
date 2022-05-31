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
	SAFE_RELEASE(m_pStage);
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
	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	string strFileName = GET_SINGLE(CResourcesManager)->GetFileName();

	pStage->LoadFromFullPath(strFileName.c_str());

	SAFE_RELEASE(pStage);

	//Default
	CLayer* pLayer = FindLayer("Default");

	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	pPlayer->SetPos(110.f, 110.f);

	SAFE_RELEASE(pPlayer);


	return true;
}

int CInGameScene::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	return 0;
}

int CInGameScene::LateUpdate(float fDeltaTime)
{
	return 0;
}
