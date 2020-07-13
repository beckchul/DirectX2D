#include "StdAfx.h"
#include "Ending.h"

CEnding::CEnding(void)
{
}

CEnding::~CEnding(void)
{
	Release();
}

void CEnding::Release( void )
{

}


void CEnding::Initialize( void )
{
	//CSoundMgr::GetInstance()->PlaySound(L"Ending.mp3", CHANNEL_BGM);
	CTextureLoadMgr::GetInstance()->LoadImageByScene(SCENE_ENDING);
}

void CEnding::Update( void )
{
	if(CKeyMgr::GetInstance()->OnceKeyDown(VK_RETURN))
	{
		//게임종료
		DestroyWindow(g_hWnd);
	}

	//return RETURN_NULL;
}

void CEnding::Render( HDC hDc )
{
	/*CBitMap* pEndingBmp = CBmpMgr::GetInstance()->FindImage(L"EndingScreen");

	if(NULL == pEndingBmp)
		return;

	TransparentBlt(hDc, 0, 0, ENDING_SCREEN_CX, ENDING_SCREEN_CY,
		pEndingBmp->GetMemDC(),
		0, 0, ENDING_SCREEN_CX, ENDING_SCREEN_CY, NULL);*/
}