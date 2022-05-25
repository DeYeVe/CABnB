#pragma once
#include "Scene.h"

class CMapEditScene :
	public CScene
{
private:
	friend class CSceneManager;

public:
	CMapEditScene();
	~CMapEditScene();

private:
	class CStage*	m_pStage;
	class CTile*	m_pSelectedTile;
	class CBlock*	m_pSelectedBlock;
	bool			m_bIsTile;

private:
	static wchar_t	m_strText[MAX_PATH];

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);

public:
	void TileButtonCallback(float fTime, const string& strTag);
	void BlockButtonCallback(float fTime, const string& strTag);
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};