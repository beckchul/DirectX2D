// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <io.h>

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <d3dx9math.h>


#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "msimg32.lib")
//�������� ����ϱ� ���� ���̺귯��.

// fmod ���̺귯��
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#pragma comment(lib, "fmodex_vc.lib")

using namespace std;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Define.h"
#include "Constant.h"
#include "Macro.h"
#include "Enum.h"
#include "Struct.h"
#include "Typedef.h"
#include "Function.h"
#include "Functor.h"
#include "AbstractFactory.h"
#include "Device.h"

//////// MANAGER ////////
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "TextureLoadMgr.h"
#include "ObjMgr.h"
#include "TextureMgr.h"
#include "CollisionMgr.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

#endif