#include "StdAfx.h"
#include "MainGame.h"
#include "Scene.h"

CMainGame::CMainGame(void)
:m_hDc(NULL)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize( void )
{
	CSoundMgr::GetInstance()->LoadSoundFile();

	srand(unsigned(time(NULL)));

	m_hDc = GetDC(g_hWnd);

	CSceneMgr::GetInstance()->SetScene(SCENE_INTRO);

	if( FAILED(CDevice::GetInstance()->InitD3D()))
	{
		MessageBox(g_hWnd, L"디바이스 생성 실패!", L"디바이스 생성 실패!", MB_OK);
	}
}

void CMainGame::Update( void )
{
	CSoundMgr::GetInstance()->UpdateSound();
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::Render( void )
{
	if(SCENE_INTRO != CSceneMgr::GetInstance()->GetScene()->GetSceneType())
	{
		CDevice::GetInstance()->Render_Begin();
		CSceneMgr::GetInstance()->Render(m_hDc);
		CDevice::GetInstance()->Render_End();
	}
}

void CMainGame::Release( void )
{
	ReleaseDC(g_hWnd, m_hDc);
	CObjMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->Destroy();
	CSoundMgr::GetInstance()->DestroyInstance();
}
