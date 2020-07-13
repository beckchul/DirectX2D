#include "StdAfx.h"
#include "Intro.h"

CIntro::CIntro(void)
{
}

CIntro::~CIntro(void)
{
	Release();
}

void CIntro::Release( void )
{
	MCIWndClose(m_hVideo);
}

void CIntro::Initialize( void )
{
	// 동영상 불러오기
	m_hVideo = MCIWndCreate(g_hWnd, NULL,
		MCIWNDF_NOPLAYBAR | WS_CHILD | WS_VISIBLE,
		L"../Texture/Video/Intro.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);

	m_eSceneType = SCENE_INTRO;
}

void CIntro::Update( void )
{
	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_RETURN))
	{
		CSceneMgr::GetInstance()->SetScene(SCENE_TITLE);
	}
	//return RETURN_NULL;
}

void CIntro::Render( HDC hDc )
{
}
