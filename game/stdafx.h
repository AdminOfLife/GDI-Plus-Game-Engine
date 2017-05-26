// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#pragma comment(lib, "winmm")

#include <vector>
#include <thread>
#include <map>
#include <unordered_map>
#include <string>

#include <functional>
#include <chrono>

#include <GdiPlus.h>
#pragma comment(lib, "gdiplus")

#include "Function.h"
#include "InputComponent.h"

#include "Object.h"
#include "Character.h"
#include "Enemy.h"
#include "Map.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "UserDefine.h"