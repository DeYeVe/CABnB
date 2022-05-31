#pragma once

#include "../Game.h"

class CResourcesManager
{
private:
	unordered_map<string, class CTexture*> m_mapTexture;
	HINSTANCE		m_hInst;
	HDC				m_hDC;	
	class CTexture* m_pBackBuffer;

private:
	string	m_strFilePath;

public:
	string GetFileName()
	{
		return m_strFilePath;
	}
	void SetFileName(string strFileName)
	{
		m_strFilePath = strFileName;
	}

public:
	class CTexture* GetBackBuffer() const;

public:
	bool Init(HINSTANCE hInst, HDC hDC);
	class CTexture* LoadTexture(const string& strKey, 
		const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* LoadTexture(FILE* pFile);
	class CTexture* FindTexture(const string& strKey);

	DECLARE_SINGLE(CResourcesManager)
};

