#include "InGameScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Collider/ColliderPixel.h"
#include "../Core/Core.h"
#include "SceneManager.h"
#include "../Core/Input.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../resource.h"
#include "../Core/PathManager.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "../Object/UIMessage.h"
#include "../Object/UITimer.h"
#include "../Object/Tile.h"
#include "../Object/Block.h"
#include "../Object/Player.h"
#include "../Sound/SoundManager.h"

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

	m_bEnd = false;

	//// UI
	CLayer* pUILayer = FindLayer("HUD");
	CUIMessage* pMessage = CObj::CreateObj<CUIMessage>("Message", pUILayer);
	pMessage->SetSize(382.f, 78.f);
	pMessage->SetTexture("Start", L"UI/start.bmp");
	pMessage->SetColorKey(255, 0, 255);
	pMessage->SetPos(321.f - 191.f, -78.f);

	CUITimer* pTimer = CObj::CreateObj<CUITimer>("Timer", pUILayer);
	pInGameTimer = pTimer;
		
	//// Frame
	CLayer* pFrameLayer = FindLayer("Frame");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pFrameLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("InGame", L"bg/InGame.bmp");
	pBackPanel->SetColorKey(255, 0, 255);

	//// Default
	CLayer* pLayer = FindLayer("Default");

	////Stage
	CLayer* pStageLayer = FindLayer("Stage");
	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	string strFileName = GET_SINGLE(CResourcesManager)->GetFileName();

	pStage->LoadFromFullPath(strFileName.c_str());
	std::vector<class CBlock*> vecBlock = pStage->GetVecBlock();
	for (size_t i = 0; i < vecBlock.size(); ++i)
	{
		if(!(vecBlock[i]->GetBlockType() == BT_BLANK) && !(vecBlock[i]->GetBlockType() == BT_START))
			pLayer->AddObject(vecBlock[i]);
	}
	pStage->SetTileVisible(true);

	//// Default
	// 1P
	POSITION tStartPos = pStage->GetStartPos() + (20.f, 20.f);
	CPlayer* pPlayer1 = CObj::CreateObj<CPlayer>("Player1", pLayer);
	pPlayer1->SetPos(tStartPos);

	// 2P
	tStartPos = pStage->GetStartPos() + (20.f, 20.f);
	CPlayer* pPlayer2 = CObj::CreateObj<CPlayer>("Player2", pLayer);
	pPlayer2->SetPos(tStartPos);

	SAFE_RELEASE(pStage);
	SAFE_RELEASE(pPlayer1);
	SAFE_RELEASE(pPlayer2);

	return true;
}

int CInGameScene::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	if (m_bEnd)
		return 0;

	if (pInGameTimer->GetInGameTime() < 0.f)
	{
		GameEnd(true);
		m_bEnd = true;
	}

	return 0;
}

int CInGameScene::LateUpdate(float fDeltaTime)
{
	CScene::LateUpdate(fDeltaTime);

	return 0;
}

void CInGameScene::GameEnd(bool bIsDraw)
{
	if (bIsDraw)
	{
		GET_SINGLE(CSoundManager)->Stop(ST_BGM);
		GET_SINGLE(CSoundManager)->LoadSound("Draw", false, "system/draw.wav");
		GET_SINGLE(CSoundManager)->Play("Draw");

		CLayer* pUILayer = FindLayer("HUD");
		CUIMessage* pMessage = CObj::CreateObj<CUIMessage>("Message", pUILayer);
		pMessage->SetSize(382.f, 79.f);
		pMessage->SetTexture("Draw", L"UI/draw.bmp");
		pMessage->SetColorKey(255, 0, 255);
		pMessage->SetPos(321.f - 191.f, -79.f);

	}
	else
	{
		GET_SINGLE(CSoundManager)->Stop(ST_BGM);
		GET_SINGLE(CSoundManager)->LoadSound("Win", false, "system/win.wav");
		GET_SINGLE(CSoundManager)->Play("Win");

		CLayer* pUILayer = FindLayer("HUD");
		CUIMessage* pMessage = CObj::CreateObj<CUIMessage>("Message", pUILayer);
		pMessage->SetSize(278, 79.f);
		pMessage->SetTexture("Win", L"UI/win.bmp");
		pMessage->SetColorKey(255, 0, 255);
		pMessage->SetPos(321.f - 139.f, -79.f);
	}
}
