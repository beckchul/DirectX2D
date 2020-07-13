#include "StdAfx.h"
#include "Select.h"

CSelect::CSelect(void)
{
}

CSelect::~CSelect(void)
{
	Release();
}

void CSelect::Release( void )
{

}


void CSelect::Initialize( void )
{
	CTextureLoadMgr::GetInstance()->LoadImageByScene(SCENE_SELECT);

	m_iFrameX = 0;

	m_eSceneType = SCENE_SELECT;
}

void CSelect::Update( void )
{
	//  캐릭터 선택 키 입력 
	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_LEFT))
	{
		if(m_iFrameX > 0)
		{
			CSoundMgr::GetInstance()->PlaySound(L"select.wav", CHANNEL_EFF, 0.3f);
			m_iFrameX --;
		}
	}

	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_RIGHT))
	{
		if(m_iFrameX < 1)
		{
			CSoundMgr::GetInstance()->PlaySound(L"select.wav", CHANNEL_EFF, 0.3f);
			m_iFrameX ++;
		}
	}

	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_RETURN))
	{
		if(m_iFrameX == 0)
		{
			CSoundMgr::GetInstance()->PlaySound(L"ok.wav", CHANNEL_EFF, 0.3f);
			CSoundMgr::GetInstance()->StopSound(CHANNEL_BGM);
			//스테이지 시작
			CSceneMgr::GetInstance()->SetScene(SCENE_STAGE);
		}
	}

	//return RETURN_NULL;
}

void CSelect::Render( HDC hDc )
{
	if(m_iFrameX == 0)
	{
		D3DXMATRIX matTrans;
		D3DXMatrixTranslation(&matTrans,TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"select0")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		D3DXMATRIX matTrans;
		D3DXMatrixTranslation(&matTrans,TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"select1")->pTexture
			, NULL
			, &D3DXVECTOR3(TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}