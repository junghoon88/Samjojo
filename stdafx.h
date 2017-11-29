#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commdlg.h>	//OPENFILENAME

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "database.h"
#include "RenderManager.h"
#include "txtData.h"
#include "collision.h"
#include "camera.h"
//#include "editboxManager.h"

//전역 매크로변수
#include "globalMacroVariables.h"


using namespace std;
using namespace IOTA_UTIL;

//===============================================
// ## 윈도우 설정 디파인 ## 2017.07. 28 ##
//===============================================

#define WINNAME (LPTSTR)(TEXT("Samjojo"))
#define WINSTARTX 0
#define WINSTARTY 0

#define WINSIZEX 1104	//
#define WINSIZEY 960	//

#define WINSIZEX2 640	//작은창
#define WINSIZEY2 400	//

#define WINSIZEX3 617   //출진씬전용
#define WINSIZEY3 522   //

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SIDEWINSIZE 144

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define TIMEMANAGER timeManager::getSingleton() 
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define INIDATA iniDataManager::getSingleton()
#define DATABASE database::getSingleton()
#define MAINCAMERA camera::getSingleton()
#define RENDERMANAGER RenderManager::getSingleton()
//#define EDITBOXMANAGER editboxManager::getSingleton()

//==================================
// ## 매크로 함수 ## 17.08.07 ##
//==================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//===================================
// ## 전역 변수 ## 17.08.07 ##
//===================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

extern HFONT _gFont[FONTVERSION_MAX];
extern HBRUSH _gBrush[BRUSHVERSION_MAX];