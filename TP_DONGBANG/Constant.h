#pragma once

class CObj;

extern HWND g_hWnd;
extern D3DXVECTOR3 g_vCollision;
extern CObj* g_pObjCollision;
extern int g_iRGB;

const int KEYMAX = 256;

const WORD MIN_STR		= 64;
const WORD MIDDLE_STR	= 128;
const WORD MAX_STR		= 256;

const DWORD MONSTER_MOVE	= 0x00000001;
const DWORD MONSTER_ATTACK	= 0x00000002;
const DWORD MONSTER_STAND	= 0x00000004;