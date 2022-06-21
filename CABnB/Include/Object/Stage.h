#pragma once
#include "Obj.h"

class CStage :
	public CObj
{
private:
	friend class CScene;

public:
	CStage();
	CStage(const CStage & stage);
	~CStage();

private:
	int		m_iTileSize;
	int		m_iTileNumX;
	int		m_iTileNumY;
	int		m_iBlockSize;
	int		m_iBlockNumX;
	int		m_iBlockNumY;

	std::vector<class CTile*> m_vecTile;
	std::vector<class CBlock*> m_vecBlock;

	std::vector<class CPlayer*> m_vecPlayer;
	// Item
	// Bomb

public:
	void CreateTile(int iNumX, int iNumY, int iSize,
		const string& strKey = "", const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);
	void SetTile(const POSITION & tPos, CTexture * pTexture);

	void CreateBlock(int iNumX, int iNumY, int iSize,
		const string& strKey = "", const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);
	void SetBlock(const POSITION & tPos, const string & strTag, BLOCK_TYPE eBT, int iHeight);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStage* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	int GetTileIndex(const POSITION& tPos);
	int GetTileIndex(float x, float y);

private:
	void ClearTile();
	void ClearBlock();

public:
	void EmptyTile();
	void EmptyBlock();

	void SetPlayer(CPlayer* pP1, CPlayer* pP2);

public:
	POSITION GetStartPos();

public:
	static bool ObjSort(class CObj* pObj1, class CObj* pObj2);
};

