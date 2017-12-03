#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	sceneManager::_readyScene->init();

	sceneManager::_currentScene = sceneManager::_readyScene;
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)	
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)	
{
	if (_currentScene) _currentScene->render();
}

void sceneManager::getChar(WPARAM wParam)
{
	if (_currentScene) _currentScene->getChar(wParam);
}


//¾À Ãß°¡
gameNode* sceneManager::addScene(wstring sceneName, gameNode* scene)				 
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

gameNode* sceneManager::addLoadingScene(wstring loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

bool sceneManager::isCurScene(wstring sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//ÇØ´ç ¾ÀÀ» Ã£Áö ¸øÇß´Ù¸é         
	if (find == _mSceneList.end())    return false;

	//Ã£À¸·Á´Â ¾ÀÀÌ ÇöÀç ¾ÀÀÌ¸é
	if (find->second == _currentScene) return true;
	
	return false;
}


HRESULT sceneManager::changeScene(wstring sceneName)							
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//ÇØ´ç ¾ÀÀ» Ã£Áö ¸øÇß´Ù¸é         ½ÇÆÐÇß½À´Ï´Ù!
	if (find == _mSceneList.end()) return E_FAIL;

	//Ã£À¸·Á´Â ¾ÀÀÌ ÇÏÇÊ ÇöÀç ¾ÀÀÌ¸é	 ±¦Âú´Ù°í ÀüÇØ¶ó
	if (find->second == _currentScene) return S_OK;

	//¹«»çÈ÷ ¹Ù²åÀ¸¸é
	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;


		playBGM();

		return S_OK;
	}


	return E_FAIL;
}

HRESULT sceneManager::changeScene(wstring sceneName, wstring loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_loadingScene = findLoading->second;

		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	}

	return E_FAIL;
}


void sceneManager::playBGM(void)
{
	if (_currentScene == _mSceneList.find(L"¼±ÅÃ¾À")->second
		|| _currentScene == _mSceneList.find(L"¸ÊÅø¾À")->second
		|| _currentScene == _mSceneList.find(L"À¯´Ö¿¡µðÅÍ")->second)
	{
		SOUNDMANAGER->stop(L"Se_b_02");
		SOUNDMANAGER->stop(L"Se_b_04");
		SOUNDMANAGER->stop(L"Se_b_05");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_00") == FALSE)		SOUNDMANAGER->play(L"Se_b_00");
	}
	else if (_currentScene == _mSceneList.find(L"´ëÈ­¾À")->second)
	{
		SOUNDMANAGER->stop(L"Se_b_00");
		SOUNDMANAGER->stop(L"Se_b_02");
		SOUNDMANAGER->stop(L"Se_b_04");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_05") == FALSE)		SOUNDMANAGER->play(L"Se_b_05");
	}
	else if (_currentScene == _mSceneList.find(L"ÁØºñ±âº»¾À")->second
			|| _currentScene == _mSceneList.find(L"ÃâÁø¾À")->second
			|| _currentScene == _mSceneList.find(L"Àåºñ¾À")->second
			|| _currentScene == _mSceneList.find(L"±¸¸Å»óÁ¡¾À")->second
			|| _currentScene == _mSceneList.find(L"ÆÇ¸Å»óÁ¡¾À")->second)
	{
		SOUNDMANAGER->stop(L"Se_b_00");
		SOUNDMANAGER->stop(L"Se_b_04");
		SOUNDMANAGER->stop(L"Se_b_05");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_02") == FALSE)		SOUNDMANAGER->play(L"Se_b_02");
	}
	else if (_currentScene == _mSceneList.find(L"ÀüÅõ¾À")->second)
	{
		SOUNDMANAGER->stop(L"Se_b_00");
		SOUNDMANAGER->stop(L"Se_b_02");
		SOUNDMANAGER->stop(L"Se_b_05");
		if (SOUNDMANAGER->isPlaySound(L"Se_b_04") == FALSE)		SOUNDMANAGER->play(L"Se_b_04");
	}
	else if (_currentScene == _mSceneList.find(L"°á°ú¾À")->second)
	{
		SOUNDMANAGER->stop(L"Se_b_00");
		SOUNDMANAGER->stop(L"Se_b_02");
		SOUNDMANAGER->stop(L"Se_b_05");
		SOUNDMANAGER->stop(L"Se_b_04");
	}
}

