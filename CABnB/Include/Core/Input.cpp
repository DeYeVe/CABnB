#include "Input.h"
#include "../Object/Mouse.h"
#include "../Animation/Animation.h"
#include "../Scene/Layer.h"
#include "../Collider/CollisionManager.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()	:
	m_pCreateKey(NULL),
	m_pMouse(NULL)
{
}

CInput::~CInput()
{
	CObj::EraseObj(m_pMouse);
	SAFE_RELEASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

POSITION CInput::GetMouseClientPos() const
{
	return m_pMouse->GetPos();
}

POSITION CInput::GetMouseWorldPos() const
{
	return m_pMouse->GetWorldPos();
}

POSITION CInput::GetMouseMove() const
{
	return m_pMouse->GetMove();
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	AddKey('D', "1P_MoveLeft");
	AddKey('F', "1P_MoveDown");
	AddKey('G', "1P_MoveRight");
	AddKey('R', "1P_MoveUp");

	AddKey(VK_LBUTTON, "MouseLButton");
	AddKey(VK_RBUTTON, "MouseRButton");
	AddKey(VK_F1, "ToggleBorder");

	GetCursorPos(&m_tMousePos);

	m_pMouse = CObj::CreateObj<CMouse>("Mouse");

	m_pMouse->SetSize(40, 44); 

	m_pMouse->SetTexture("CursorIdle", L"UI/CursorIdle.bmp");
	m_pMouse->SetColorKey(255, 0, 255);

	m_bToggleBorder = false;

	return true;
}

void CInput::Update(float fDeltaTime)
{
	unordered_map<string, PKEYINFO>::iterator	iter;
	unordered_map<string, PKEYINFO>::iterator	iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		int iPushCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iPushCount;
		}

		if (iPushCount == iter->second->vecKey.size())
		{
			if (!iter->second->bDown && !iter->second->bPress)
			{
				iter->second->bPress = true;
				iter->second->bDown = true;
			}

			else if (iter->second->bDown)
			{
				iter->second->bDown = false;
			}
		}

		else
		{
			if (iter->second->bDown || iter->second->bPress)
			{
				iter->second->bUp = true;
				iter->second->bDown = false;
				iter->second->bPress = false;
			}

			else if (iter->second->bUp)
			{
				iter->second->bUp = false;
			}
		}
	}

	if (KeyDown("ToggleBorder"))
		m_bToggleBorder = !m_bToggleBorder;

	if (KeyPress("MouseLButton"))
	{
		m_pMouse->SetTexture("CursorPressed", L"UI/CursorPressed.bmp");
		m_pMouse->SetColorKey(255, 0, 255);
	}
	else
	{
		m_pMouse->SetTexture("CursorIdle", L"UI/CursorIdle.bmp");
		m_pMouse->SetColorKey(255, 0, 255);
	}

	m_pMouse->Update(fDeltaTime);
	m_pMouse->LateUpdate(fDeltaTime);

	GET_SINGLE(CCollisionManager)->AddObject(m_pMouse);
}

bool CInput::KeyDown(const string & strKey) const
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bDown;
}

bool CInput::KeyPress(const string & strKey) const
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPress;
}

bool CInput::KeyUp(const string & strKey) const
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bUp;
}

PKEYINFO CInput::FindKey(const string & strKey)		const
{
	unordered_map<string, PKEYINFO>::const_iterator	iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return NULL;

	return iter->second;
}
