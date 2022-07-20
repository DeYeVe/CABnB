#include "SceneManager.h"
#include "InGameScene.h"
#include "StartScene.h"
#include "../Collider/CollisionManager.h"

DEFINITION_SINGLE(CSceneManager);

CSceneManager::CSceneManager() :
	m_pScene(NULL),
	m_pNextScene(NULL)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
}

bool CSceneManager::Init()
{
	CreateScene<CStartScene>(SC_CURRENT);
	return true;
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime);
}

SCENE_CHANGE CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	return ChangeScene();
}

SCENE_CHANGE CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);
	return ChangeScene();
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC, fDeltaTime);
}

SCENE_CHANGE CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		SAFE_DELETE(m_pScene);
		m_pScene = m_pNextScene;
		m_pNextScene = NULL;

		GET_SINGLE(CCollisionManager)->Clear();

		m_pScene->SetSceneType(SC_CURRENT);
		CScene::ChangeProtoType();

		return SC_CHANGE;
	}
	return SC_NONE;
}
