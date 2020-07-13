#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_dwOldFrameTime = 0;
	m_dwCurFrameTime = 0;
	m_bDeadCheck = false;
}

CObj::~CObj(void)
{
}