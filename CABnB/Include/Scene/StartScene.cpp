#include "StartScene.h"
#include "../Object/UIPanel.h"
#include "../Object/UIButton.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Core.h"
#include "SceneManager.h"
#include "RoomScene.h"
#include "MapEditScene.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	if (!CScene::Init())
		return false;

	CLayer* pLayer = FindLayer("UI");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("MainMenu", L"bg/MainMenu.bmp");

	SAFE_RELEASE(pBackPanel);

	// Start Button
	CUIButton*	pStartBtn = CObj::CreateObj<CUIButton>("StartButton", pLayer);

	pStartBtn->SetPos(GETRESOLUTION.iW / 2 - 201,
		GETRESOLUTION.iH / 2 + 95);
	pStartBtn->SetSize(191, 55);
	pStartBtn->SetTexture("StartButton", L"UI/StartButton.bmp");
	pStartBtn->SetColorKey(255, 0, 255);
	pStartBtn->SetHasOffset(true);

	CColliderRect* pRC = (CColliderRect*)pStartBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 191, 55);

	SAFE_RELEASE(pRC);

	pStartBtn->SetCallback(this, &CStartScene::StartButtonCallback);

	SAFE_RELEASE(pStartBtn);

	// Edit Button
	CUIButton*	pEditBtn = CObj::CreateObj<CUIButton>("EditButton", pLayer);

	pEditBtn->SetPos(GETRESOLUTION.iW / 2 + 10,
		GETRESOLUTION.iH / 2 + 95);
	pEditBtn->SetSize(191, 55);
	pEditBtn->SetTexture("EditButton", L"UI/EditButton.bmp");
	pEditBtn->SetColorKey(255, 0, 255);
	pEditBtn->SetHasOffset(true);

	pRC = (CColliderRect*)pEditBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 191, 55);

	SAFE_RELEASE(pRC);

	pEditBtn->SetCallback(this, &CStartScene::EditButtonCallback);

	SAFE_RELEASE(pEditBtn);

	// End Button
	CUIButton*	pEndBtn = CObj::CreateObj<CUIButton>("EndButton", pLayer);

	pEndBtn->SetPos(GETRESOLUTION.iW / 2 - 95,
		GETRESOLUTION.iH / 2 + 160);
	pEndBtn->SetSize(191, 55);
	pEndBtn->SetTexture("EndButton", L"UI/EndButton.bmp");
	pEndBtn->SetColorKey(255, 0, 255);
	pEndBtn->SetHasOffset(true);

	pRC = (CColliderRect*)pEndBtn->GetCollider("ButtonBody");

	pRC->SetRect(0.f, 0.f, 191, 55);

	SAFE_RELEASE(pRC);

	pEndBtn->SetCallback(this, &CStartScene::EndButtonCallback);

	SAFE_RELEASE(pEndBtn);

	return true;
}

void CStartScene::StartButtonCallback(float fTime, const string & strTag)
{
	GET_SINGLE(CSceneManager)->CreateScene<CRoomScene>(SC_NEXT);
}

void CStartScene::EndButtonCallback(float fTime, const string& strTag)
{
	GET_SINGLE(CCore)->DestroyGame();
}

void CStartScene::EditButtonCallback(float fTime, const string& strTag)
{
	GET_SINGLE(CSceneManager)->CreateScene<CMapEditScene>(SC_NEXT);
}
