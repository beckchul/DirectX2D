#include "StdAfx.h"
#include "TextureLoadMgr.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureLoadMgr)

CTextureLoadMgr::CTextureLoadMgr(void)
{
}

CTextureLoadMgr::~CTextureLoadMgr(void)
{
	Release();
}

void CTextureLoadMgr::Release( void )
{
	CTextureMgr::GetInstance()->DestroyInstance();
}



void CTextureLoadMgr::LoadImageByScene( SCENE_TYPE eSceneType )
{
	switch(eSceneType)
	{
	case SCENE_TITLE:
		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/title.png", L"title", TEX_SINGLE))
		|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/Quit0.png", L"Quit0", TEX_SINGLE))
		|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/Quit1.png", L"Quit1", TEX_SINGLE))
		|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/Start0.png", L"Start0", TEX_SINGLE))
		|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/Start1.png", L"Start1", TEX_SINGLE)))
		{
			MessageBox(g_hWnd, L"단일 이미지 로드 실패!", L"단일 이미지 로드 실패!", MB_OK);
		}
		break;

	case SCENE_SELECT:
		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/select0.png", L"select0", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Title/select1.png", L"select1", TEX_SINGLE)))
		{
			MessageBox(g_hWnd, L"단일 이미지 로드 실패!", L"단일 이미지 로드 실패!", MB_OK);
		}
		break;

	case SCENE_STAGE:
		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/BackGround.png", L"BackGround", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/UI_BackGround.png", L"UI_BackGround", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Back.png", L"Back", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bullet/Bullet0.png", L"Bullet0", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bullet/Bullet1.png", L"Bullet1", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/BigPower.png", L"BigPower", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Item.png", L"Item", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Life.png", L"Life", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Power.png", L"Power", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/SubWeapon/SubWeapon.png", L"SubWeapon", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/UI_LOGO.png", L"UI_LOGO", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/BulletEffect/RedEffect.png", L"RedEffect", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/BulletEffect/BlueEffect.png", L"BlueEffect", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Orora.png", L"Orora", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Orora2.png", L"Orora2", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/PlayerIllust.png", L"PlayerIllust", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Effect/Effect0.png", L"Effect0", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Effect/Effect1.png", L"Effect1", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Effect/Effect2.png", L"Effect2", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Effect/Effect3.png", L"Effect3", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Effect/Effect4.png", L"Effect4", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Bomb0.png", L"Bomb0", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Bomb1.png", L"Bomb1", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Bomb2.png", L"Bomb2", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Bomb/Bomb3.png", L"Bomb3", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Boss/Satellite0.png", L"Satellite", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/BossBoom.png", L"BossBoom", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/State.png", L"State", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/LifeStar.png", L"LifeStar", TEX_SINGLE))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/BombStar.png", L"BombStar", TEX_SINGLE)))
		{
			MessageBox(g_hWnd, L"단일 이미지 로드 실패!", L"단일 이미지 로드 실패!", MB_OK);
		}

		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Nomal/%d.png"
			, L"EasyMonster", TEX_MULTI, L"EasyMonster", 8))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Mid/%d.png"
			, L"NomalMonster", TEX_MULTI, L"NomalMonster", 8))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Boss/Attack/Boss%d.png"
			, L"BossMonsterAttack", TEX_MULTI, L"BossMonsterAttack", 5))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/Boss/Move/Boss%d.png"
			, L"BossMonsterMove", TEX_MULTI, L"BossMonsterMove", 5)))
		{
			MessageBox(g_hWnd, L"다중 이미지 로드 실패!", L"다중 이미지 로드 실패!", MB_OK);
		}


		if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Idle/Player%d.png"
			, L"PlayerIdle", TEX_MULTI, L"Idle", 3)) 
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Move/Player%d.png"
			, L"PlayerMove", TEX_MULTI, L"Move", 6))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Bullet/Blue/Blue%d.png"
			, L"BulletBlue", TEX_MULTI, L"BulletBlue", 10))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Bullet/Red/Red%d.png"
			, L"BulletRed", TEX_MULTI, L"BulletRed", 10))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Bullet/Green/Green%d.png"
			, L"BulletGreen", TEX_MULTI, L"BulletGreen", 10))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Bullet/Yellow/Yellow%d.png"
			, L"BulletYellow", TEX_MULTI, L"BulletYellow", 10))
			|| FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Number/Number%d.png"
			, L"Number", TEX_MULTI, L"Number", 10)))
		{
			MessageBox(g_hWnd, L"다중 이미지 로드 실패!", L"다중 이미지 로드 실패!", MB_OK);
		}

		break;

	case SCENE_ENDING:
		break;
	}

}