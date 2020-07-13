#include "StdAfx.h"
#include "Title.h"
#include "Maingame.h"

CTitle::CTitle(void)
{
}

CTitle::~CTitle(void)
{
	Release();
}

void CTitle::Release( void )
{
	
}

void CTitle::Initialize( void )
{
	CSoundMgr::GetInstance()->PlayBGM(L"Title.mid", CHANNEL_BGM, 1.0f);
	CTextureLoadMgr::GetInstance()->LoadImageByScene(SCENE_TITLE);

	m_iStartFrameX = 1;
	m_iQuitFrameX = 0;

	m_eSceneType = SCENE_TITLE;
}

void CTitle::Update( void )
{
	//  메뉴 선택 키 입력 
	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_UP))
	{
		if(m_iStartFrameX < 1)
		{
			CSoundMgr::GetInstance()->PlaySound(L"select.wav", CHANNEL_EFF, 0.3f);
			m_iStartFrameX ++;
			m_iQuitFrameX --;
		}
	}

	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_DOWN))
	{
		if(m_iQuitFrameX < 1)
		{
			CSoundMgr::GetInstance()->PlaySound(L"select.wav", CHANNEL_EFF, 0.3f);
			m_iStartFrameX --;
			m_iQuitFrameX ++;
		}
	}

	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_RETURN))
	{
		if(m_iStartFrameX == 1)
		{
			CSoundMgr::GetInstance()->PlaySound(L"ok.wav", CHANNEL_EFF, 0.3f);
			//캐릭터 선택화면
			CSceneMgr::GetInstance()->SetScene(SCENE_SELECT);
		}
		else if(m_iQuitFrameX == 1)
		{
			//게임종료
			DestroyWindow(g_hWnd);
		}
	}

	//return RETURN_NULL;
}

void CTitle::Render( HDC hDc )
{
	//Title
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"title")->pTexture
					, NULL
					, &D3DXVECTOR3(TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f)
					, NULL
					, D3DCOLOR_ARGB(255, 255, 255, 255));

	// Start
	D3DXMatrixTranslation(&matTrans, 320.f, 350.f, 0.f);

	if(m_iStartFrameX == 0)
	{
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Start0")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_START_CX / 2.f , TITLE_START_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Start1")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_START_CX / 2.f , TITLE_START_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
	// Quit
	D3DXMatrixTranslation(&matTrans, 320.f, 380.f, 0.f);

	if(m_iQuitFrameX == 0)
	{
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Quit0")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_QUIT_CX / 2.f, TITLE_QUIT_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Quit1")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_QUIT_CX / 2.f, TITLE_QUIT_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}