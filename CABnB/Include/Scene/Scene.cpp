#include "Scene.h"	
#include "Layer.h"
#include "../Object/Obj.h"
#include "../Object/UIPanel.h"

unordered_map<string, CObj*> CScene::m_mapPrototype[SC_END];

CScene::CScene()
{
	CLayer*	pLayer = CreateLayer("UI", INT_MAX - 2);
	pLayer = CreateLayer("HUD", INT_MAX);
	pLayer = CreateLayer("Default", 2);
	pLayer = CreateLayer("Stage", 1);
	m_eSceneType = SC_CURRENT;
}

CScene::~CScene()
{
	ErasePrototype(m_eSceneType);
	Safe_Delete_VecList(m_LayerList);
}

void CScene::ErasePrototype(const string & strTag, SCENE_CREATE sc)
{
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype[sc].find(strTag);

	if (!iter->second)
		return;

	SAFE_RELEASE(iter->second);
	m_mapPrototype[sc].erase(iter);
}

void CScene::ErasePrototype(SCENE_CREATE sc)
{
	Safe_Release_Map(m_mapPrototype[sc]);
}

CLayer * CScene::CreateLayer(const string & strTag, int iZOrder)
{

	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this);

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);

	return pLayer;
}

CLayer * CScene::FindLayer(const string & strTag)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
			return *iter;
	}

	return NULL;
}

bool CScene::Init()
{
	return true;
}

void CScene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Input(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}

		else
			++iter;
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}

		else
			++iter;
	}
	return 0;
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}

		else
			++iter;
	}
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}

		else
			++iter;
	}
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife())
		{
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}

		else
			iter++;
	}
}

CObj * CScene::FindPrototype(const string & strKey, SCENE_CREATE sc)
{
	unordered_map<string, CObj*>::iterator iter = m_mapPrototype[sc].find(strKey);

	if (iter == m_mapPrototype[sc].end())
		return NULL;

	return iter->second;
}

void CScene::ChangeProtoType()
{
	ErasePrototype(SC_CURRENT);
	m_mapPrototype[SC_CURRENT] = m_mapPrototype[SC_NEXT];
	m_mapPrototype[SC_NEXT].clear();
}

void CScene::FadeIn()
{/*
	CLayer* pLayer = FindLayer("UI");

	CUIPanel*	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel = CObj::CreateObj<CUIPanel>("BackPanel", pLayer);

	pBackPanel->SetSize(GETRESOLUTION.iW, GETRESOLUTION.iH);
	pBackPanel->SetTexture("Fade", L"bg/Fade5.bmp");
	pBackPanel->SetColorKey(255, 255, 255);

	SAFE_RELEASE(pBackPanel);*/
}

void CScene::FadeOut()
{
}

bool CScene::LayerSort(CLayer * pL1, CLayer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}
