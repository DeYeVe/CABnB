#include "SoundManager.h"
#include "../Core/PathManager.h"

DEFINITION_SINGLE(CSoundManager);

CSoundManager::CSoundManager()	:
	m_pSystem(NULL)
{
}

CSoundManager::~CSoundManager()
{
	m_pSystem->close();
	m_pSystem->release();
}

bool CSoundManager::Init()
{
	System_Create(&m_pSystem);

	m_pSystem->init(10, FMOD_INIT_NORMAL, NULL);

	return true;
}

bool CSoundManager::LoadSound(const string & strKey, bool bLoop, const char * pFileName, const string & strPathKey)
{
	if (FindSound(strKey))
		return true;

	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(strPathKey);

	string strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	FMOD_MODE	eMode = FMOD_LOOP_NORMAL;
	if (!bLoop)
		eMode = FMOD_DEFAULT;

	PSOUNDINFO pSoundInfo = new SOUNDINFO;

	pSoundInfo->bLoop = bLoop;

	m_pSystem->createSound(strFullPath.c_str(), eMode, NULL, &pSoundInfo->pSound);

	m_mapSound.insert(make_pair(strKey, pSoundInfo));

	return true;
}

bool CSoundManager::Play(const string & strKey)
{
	PSOUNDINFO pSound = FindSound(strKey);

	if(!pSound)
		return false;

	m_pSystem->update();

	SOUND_TYPE eType = ST_BGM;

	if (!pSound->bLoop)
		eType = ST_EFFECT;

	m_pSystem->playSound(pSound->pSound, NULL, false, &m_pChannel[eType]);

	return true;
}

bool CSoundManager::Stop(SOUND_TYPE eType)
{
	m_pChannel[eType]->stop();

	return true;
}

bool CSoundManager::Volume(SOUND_TYPE eType, float fVolume)
{
	m_pChannel[eType]->setVolume(fVolume);

	return true;
}

PSOUNDINFO CSoundManager::FindSound(const string & strKey)
{
	unordered_map<string, PSOUNDINFO>::iterator iter = m_mapSound.find(strKey);

	if (iter == m_mapSound.end())
		return NULL;

	return iter->second;
}