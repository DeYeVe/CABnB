#include "Core.h"
#include "../Scene/SceneManager.h"
#include "Timer.h"
#include "PathManager.h"
#include "../resources/ResourcesManager.h"
#include "../resources/Texture.h"
#include "Camera.h"
#include "Input.h"
#include "../Collider/CollisionManager.h"
#include "../Object/Mouse.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;

CCore::CCore()
{
	// 메모리 릭 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(256);

#ifdef _DEBUG
	// 콘솔창을 생성
	AllocConsole();
#endif // _DEBUG

}

CCore::~CCore()
{
	DESTROY_SINGLE(CSceneManager);
	DESTROY_SINGLE(CCollisionManager);
	DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CCamera);
	DESTROY_SINGLE(CResourcesManager);
	DESTROY_SINGLE(CPathManager);
	DESTROY_SINGLE(CTimer);

	ReleaseDC(m_hWnd, m_hDC);

#ifdef _DEBUG
	FreeConsole();
#endif // _DEBUG

}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	MyRegisterClass();

	// 해상도 설정
	m_tRS.iW = 800;
	m_tRS.iH = 600;

	Create();

	// 화면 DC 생성
	m_hDC = GetDC(m_hWnd);

	// 타이머 초기화
	if (!GET_SINGLE(CTimer)->Init(m_hWnd))
		return false;

	// 경로관리자 초기화
	if (!GET_SINGLE(CPathManager)->Init())
		return false;

	// 리소스 관리자 초기화
	if (!GET_SINGLE(CResourcesManager)->Init(hInst, m_hDC))
		return false;

	// 입력관리자 초기화
	if (!GET_SINGLE(CInput)->Init(m_hWnd))
		return false;

	// 카메라 관리자 초기화
	if (!GET_SINGLE(CCamera)->Init(POSITION(0.f, 0.f),
		m_tRS, RESOLUTION(1500, 1200)))
		return false;

	// 장면관리자 초기화
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}


int CCore::Run()
{
	MSG msg;

	// Main message loop:
	while (m_bLoop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;

}

void CCore::Logic()
{
	// 타이머 갱신
	GET_SINGLE(CTimer)->Update();

	float	fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

	Input(fDeltaTime);

	if (Update(fDeltaTime) == SC_CHANGE)
		return;

	if (LateUpdate(fDeltaTime) == SC_CHANGE)
		return;

	Collision(fDeltaTime);
	Render(fDeltaTime);

}


void CCore::Input(float fDeltaTime)
{
	GET_SINGLE(CInput)->Update(fDeltaTime);

	GET_SINGLE(CSceneManager)->Input(fDeltaTime);
	GET_SINGLE(CCamera)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->Update(fDeltaTime);
	GET_SINGLE(CCamera)->Update(fDeltaTime);
	return sc;
}

int CCore::LateUpdate(float fDeltaTime)
{
	SCENE_CHANGE sc;
	sc = GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
	return sc;
}

void CCore::Collision(float fDeltaTime)
{
	GET_SINGLE(CSceneManager)->Collision(fDeltaTime);

	GET_SINGLE(CCollisionManager)->Collision(fDeltaTime);
}


void CCore::Render(float fDeltaTime)
{
	CTexture*	pBackBuffer = GET_SINGLE(CResourcesManager)->GetBackBuffer();

	GET_SINGLE(CSceneManager)->Render(pBackBuffer->GetDC(), fDeltaTime);

	CMouse* pMouse = GET_SINGLE(CInput)->GetMouse();

	pMouse->Render(pBackBuffer->GetDC(), fDeltaTime);

	BitBlt(m_hDC, 0, 0, m_tRS.iW, m_tRS.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY);

	SAFE_RELEASE(pBackBuffer);
}

ATOM CCore::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"CrazyArcadeBnB";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

BOOL CCore::Create()
{
	m_hWnd = CreateWindowW(L"CrazyArcadeBnB", L"CrazyArcadeBnB", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}


	
	RECT rc = { 0, 0, m_tRS.iW, m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

