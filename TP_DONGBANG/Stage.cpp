#include "StdAfx.h"
#include "Stage.h"
#include "Player.h"
#include "NomalMonster.h"
#include "PlayerBulletEffect.h"
#include "Item.h"
#include "BossMonster.h"
#include "EffectPower2.h"
#include "SmallEffect.h"
#include "Player.h"

CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize( void )
{
	CSoundMgr::GetInstance()->PlayBGM(L"Stage.mid", CHANNEL_BGM, 1.0f);

	CTextureLoadMgr::GetInstance()->LoadImageByScene(SCENE_STAGE);

	m_eSceneType = SCENE_STAGE;

	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(), OBJ_PLAYER);

	m_dwCount = GetTickCount();
	m_iCount = 0;
	m_iAlph  = 0;
	m_iAlphCount = 0;
	m_iStartCount = 255;
	m_bCreateBoss = false;
	m_dwStageCount = GetTickCount();
	m_iStageCount = 0;

	m_dwScoreBounsOldTime = GetTickCount();
	m_dwScoreBounsCurTime = 0;
}

void CStage::Update( void )
{
	if(m_bCreateBoss)
	{
		m_iAlph += 20;

		if(m_iAlph > 255)
			m_iAlph = 255;
	}
	else
	{
		m_iAlph -= 20;

		if(m_iAlph < 0)
			m_iAlph = 0;
	}

	if(m_dwCount + 100 < GetTickCount())
	{
		m_dwCount = GetTickCount();
		++m_iCount;
		m_iStartCount -= 20;
		if(m_iCount > 900)
			m_iCount = 900;

		if(m_iStartCount < 0)
			m_iStartCount = 0;

		if(m_iAlph == 255)
		{
			++m_iAlphCount;

			if(m_iAlphCount > 900)
				m_iAlphCount = 900;
		}
	}
	StagePatton();

	OBJLIST* m_pPlayerList = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
	CObj* pPlayer = m_pPlayerList->front();

	m_dwScoreBounsCurTime = GetTickCount();
	if(m_dwScoreBounsOldTime + 150 < m_dwScoreBounsCurTime)
	{
		m_dwScoreBounsOldTime = m_dwScoreBounsCurTime;

		// Player 점수 증가
		dynamic_cast<CPlayer*>(pPlayer)->PlusScore(1);
	}

	CObjMgr::GetInstance()->UpdateObj();

	// 충돌체크

	// 플레이어와 몬스터 총알
	if(!CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER_BULLET)->empty())
	{
		OBJITER dstIter_begin = m_pPlayerList->begin();
		OBJITER dstIter_end = m_pPlayerList->end();

		for(; dstIter_begin != dstIter_end; ++dstIter_begin)
		{
			OBJITER srcIter_begin = CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER_BULLET)->begin();
			OBJITER srcIter_end = CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER_BULLET)->end();

			for(; srcIter_begin != srcIter_end; ++srcIter_begin)
			{
				if((*srcIter_begin)->GetDeadState() || (*dstIter_begin)->GetDeadState()
					|| dynamic_cast<CPlayer*>((*dstIter_begin))->GetbPower() )
					continue;

				INFO* dstInfo = (*dstIter_begin)->GetInfo();

				float dstfX = dstInfo->vPos.x + dstInfo->vSize.x / 2 - 5.f;
				float dstfY = dstInfo->vPos.y + dstInfo->vSize.y / 2;

				float srcLeft = (*srcIter_begin)->GetInfo()->vPos.x - (*srcIter_begin)->GetInfo()->vSize.x / 1.5f;
				float srcTop = (*srcIter_begin)->GetInfo()->vPos.y - (*srcIter_begin)->GetInfo()->vSize.y / 1.5f;
				float srcRight = (*srcIter_begin)->GetInfo()->vPos.x + (*srcIter_begin)->GetInfo()->vSize.x / 1.5f;
				float srcBottom = (*srcIter_begin)->GetInfo()->vPos.y + (*srcIter_begin)->GetInfo()->vSize.y / 1.5f;

				if(dstfX >= srcLeft && dstfX <= srcRight
					&& dstfY >= srcTop && dstfY <= srcBottom)
				{
					// 충돌
					(*srcIter_begin)->IsDead();

					(*dstIter_begin)->IsDead(); // 플레이어
					dynamic_cast<CPlayer*>((*dstIter_begin))->SetbPower(true);
					dynamic_cast<CPlayer*>((*dstIter_begin))->MinusLife();

					// 죽을때 이펙트 나오고 부활시작
					dynamic_cast<CPlayer*>(m_pPlayerList->front())->DeadEffect();
					dynamic_cast<CPlayer*>(m_pPlayerList->front())->RevivalTimeStart();
				}
			}
		}
	}

	// 몬스터와 플레이어 normal총알
	if(!CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERNORMALBULLET)->empty())
	{
		if(CCollisionMgr::CollisionRect
			(CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER)
			,CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERNORMALBULLET)))
		{
			// Player의 bullet타입에 따라 .. 
			// 빨간 원 이펙트
			CObj* pEffect = new CPlayerBulletEffect;
			pEffect->Initialize();
			pEffect->SetPos(g_vCollision);
			dynamic_cast<CPlayerBulletEffect*>(pEffect)->SetTargetY(g_vCollision.y - 20.f);
			dynamic_cast<CPlayerBulletEffect*>(pEffect)->SetBulletEffType(PLAYERBULLETEFF_RED);

			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_PLAYERBULLETEFFECT);

			for(int i = 0; i < 2; ++i)
			{
				CObj* pEffect2 = new CSmallEffect;
				pEffect2->Initialize();
				pEffect2->SetPos(g_vCollision);
				dynamic_cast<CSmallEffect*>(pEffect2)->SetType(1);

				CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
			}
		}
	}

	// 몬스터와 플레이어 search총알
	if(!CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERSEARCHBULLET)->empty())
	{
		if(CCollisionMgr::CollisionRect
			(CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER)
			,CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERSEARCHBULLET)))
		{
			// Player의 bullet타입에 따라 .. 
			// 파란 원 이펙트
			CObj* pEffect = new CPlayerBulletEffect;
			pEffect->Initialize();
			pEffect->SetPos(g_vCollision);
			dynamic_cast<CPlayerBulletEffect*>(pEffect)->SetTargetY(g_vCollision.y - 20.f);
			dynamic_cast<CPlayerBulletEffect*>(pEffect)->SetBulletEffType(PLAYERBULLETEFF_BLUE);

			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_PLAYERBULLETEFFECT);

			for(int i = 0; i < 2; ++i)
			{
				CObj* pEffect2 = new CSmallEffect;
				pEffect2->Initialize();
				pEffect2->SetPos(g_vCollision);
				dynamic_cast<CSmallEffect*>(pEffect2)->SetType(2);

				CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
			}
		}
	}

	// 몬스터와 플레이어 Bomb
	if(!CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERBOMB)->empty())
	{
		if(CCollisionMgr::CollisionPointInRect
			(CObjMgr::GetInstance()->GetObjList(OBJ_MONSTER)
			,CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERBOMB)))
		{
			// Player의 bullet타입에 따라 .. 이펙트 색..
			CObj* pEffect = new CEffectPower2;
			pEffect->Initialize();
			pEffect->SetPos(g_vCollision);
		
			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

			for(int i = 0; i < 5; ++i)
			{
				CObj* pEffect2 = new CSmallEffect;
				pEffect2->Initialize();
				pEffect2->SetPos(g_vCollision);
				dynamic_cast<CSmallEffect*>(pEffect2)->SetType(4);

				CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
			}

			for(int i = 0; i < 10; ++i)
			{
				CObj* pEffect2 = new CSmallEffect;
				pEffect2->Initialize();
				pEffect2->SetPos(g_vCollision);
				dynamic_cast<CSmallEffect*>(pEffect2)->SetType(3);

				CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
			}
		}
	}

	// 플레이어와 아이템
	if(!CObjMgr::GetInstance()->GetObjList(OBJ_ITEM)->empty())
	{
		if(CCollisionMgr::CollisionRect
			(m_pPlayerList
			,CObjMgr::GetInstance()->GetObjList(OBJ_ITEM)))
		{

			CSoundMgr::GetInstance()->PlaySound(L"item00.wav", CHANNEL_EFF, 1.0f);

			if(dynamic_cast<CItem*>(g_pObjCollision)->GetItemType() == ITEM_POWER)
			{
				dynamic_cast<CPlayer*>(m_pPlayerList->front())->SetPowerCount(1);
			}
			else if(dynamic_cast<CItem*>(g_pObjCollision)->GetItemType() == ITEM_BIGPOWER)
			{
				dynamic_cast<CPlayer*>(m_pPlayerList->front())->SetPowerCount(8);
			}
		}
	}
	
	//return RETURN_NULL;
}

void CStage::Render( HDC hDc )
{
	// 배경
	D3DXMATRIX matWorld, matScale, matTrans;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans,STAGE_SCREEN_CX / 2.f + 30.f, STAGE_SCREEN_CY / 2.f + 10.f, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"BackGround")->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_SCREEN_CX / 2.f, 1350 - (STAGE_SCREEN_CY / 2.f) - m_iCount, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, g_iRGB, g_iRGB, g_iRGB));

	D3DXMatrixTranslation(&matTrans,STAGE_SCREEN_CX / 2.f + 30.f, STAGE_SCREEN_CY / 2.f + 10.f, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"BossBoom")->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_SCREEN_CX / 2.f, 1350 - (STAGE_SCREEN_CY / 2.f) - m_iAlphCount, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlph, 255, 255, 255));


	// 객체들
	CObjMgr::GetInstance()->RenderObj(hDc);

	// UI BacGround
	D3DXMatrixTranslation(&matTrans,TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"UI_BackGround")->pTexture
		, NULL
		, &D3DXVECTOR3(TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	// Back
	D3DXMatrixTranslation(&matTrans,TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Back")->pTexture
		, NULL
		, &D3DXVECTOR3(TITLE_SCREEN_CX / 2.f, TITLE_SCREEN_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iStartCount, 255, 255, 255));

	// UI Logo
	D3DXMatrixTranslation(&matTrans,STAGE_UI_LOGO_CX / 2.f + 420, STAGE_UI_LOGO_CY / 2.f + 240, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"UI_LOGO")->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_LOGO_CX / 2.f, STAGE_UI_LOGO_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	// State UI
	D3DXMatrixTranslation(&matTrans,STAGE_UI_STATE_CX / 2.f + 420, STAGE_UI_STATE_CX / 2.f + 80, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"State")->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_STATE_CX / 2.f, STAGE_UI_STATE_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));






	CObj* pPlayer = (CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER))->front();
	PlayerInfo* pPlayerInfo = dynamic_cast<CPlayer*>(pPlayer)->GetPlayerInfo();

	for(int i = 0; i < pPlayerInfo->iLife; ++i)
	{
		// Life
		D3DXMatrixTranslation(&matTrans,STAGE_UI_LIFE_CX / 2.f + (425 + (i * (STAGE_UI_LIFE_CX + 3)))
			, STAGE_UI_LIFE_CY / 2.f + 100, 0.f);
		D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"LifeStar")->pTexture
			, NULL
			, &D3DXVECTOR3(STAGE_UI_LIFE_CX / 2.f, STAGE_UI_LIFE_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	for(int i = 0; i < pPlayerInfo->iBomb; ++i)
	{
		// Bomb
		D3DXMatrixTranslation(&matTrans,STAGE_UI_BOMB_CX / 2.f + (425 + (i * (STAGE_UI_BOMB_CX + 3)))
			, STAGE_UI_BOMB_CY / 2.f + 150, 0.f);
		D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"BombStar")->pTexture
			, NULL
			, &D3DXVECTOR3(STAGE_UI_BOMB_CX / 2.f, STAGE_UI_BOMB_CY / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
	// Score
	// 1. 몬스터 잡을 때마다 100씩 증가..
	// 2. 시간 간격을 두어서 해당 시간마다 스코어 1씩증가..
	// 첫번째 자리 숫자
	int iNumber1 = 0;

	int iScore = pPlayerInfo->iScore;
	iNumber1 = iScore / 100000;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber1)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 두번째 자리 숫자
	int iNumber2 = 0;

	iNumber2 = (iScore % 100000) / 10000;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 17, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber2)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 세번째 자리 숫자
	int iNumber3 = 0;

	iNumber3 = (iScore % 10000) / 1000;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 34, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber3)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 네번째 자리 숫자
	int iNumber4 = 0;

	iNumber4 = (iScore % 1000) / 100;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 48, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber4)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 다섯번째 자리 숫자
	int iNumber5 = 0;

	iNumber5 = (iScore % 100) / 10;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 62, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber5)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 여섯번째 자리 숫자
	int iNumber6 = 0;

	iNumber6 = (iScore % 100) % 10;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 76, STAGE_UI_NUMBER_CY / 2.f + 45, 0.f);
	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iNumber6)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	//power number
	int iPowerCount = pPlayerInfo->iPower;

	int iPowerNumber1 = 0;

	iPowerNumber1 = (iPowerCount % 100) / 10;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 70, STAGE_UI_NUMBER_CY / 2.f + 182, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iPowerNumber1)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	int iPowerNumber2 = 0;

	iPowerNumber2 = (iPowerCount % 100) % 10;

	D3DXMatrixTranslation(&matTrans,STAGE_UI_NUMBER_CX / 2.f + 425 + 84, STAGE_UI_NUMBER_CY / 2.f + 182, 0.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

	matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Number", L"Number", iPowerNumber2)->pTexture
		, NULL
		, &D3DXVECTOR3(STAGE_UI_NUMBER_CX / 2.f, STAGE_UI_NUMBER_CY / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	

}

void CStage::Release( void )
{
	CObjMgr::GetInstance()->DestroyInstance();
}

void CStage::StagePatton( void )
{
	if(m_dwStageCount + 200 < GetTickCount())
	{
		m_dwStageCount = GetTickCount();
		++m_iStageCount;
	}


	
	//첫번째 좌측
	if(m_iStageCount == 8 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(60.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}
	if(m_iStageCount == 10 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(70.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}
	if(m_iStageCount == 12 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}
	if(m_iStageCount == 14 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(90.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}
	if(m_iStageCount == 16 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	//첫번째 우측
	if(m_iStageCount == 28 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(355.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 30 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(345.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 32 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(335.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 34 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(325.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 36 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(315.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 38 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(305.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 40 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(295.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	if(m_iStageCount == 42 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(285.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}


	// 두번째 양쪽 
	if(m_iStageCount == 50 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(50.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(365.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 52 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(65.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(350.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 54 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(335.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 56 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(95.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(320.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 58 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(110.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(305.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 60 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(125.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(290.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 62 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(140.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(275.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 64 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(155.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(260.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 66 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(170.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(245.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}
	if(m_iStageCount == 68 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(185.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(230.f, -20.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}


	// 빨간놈
	if(m_iStageCount == 76 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(60.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 82 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(275.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 88 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(140.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 94 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(355.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 100 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(60.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 106 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(320.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 112 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(150.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 118 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(345.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 124 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(55.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 132 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(300.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 140 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(50.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 148 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 154 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(170.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 157 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(365.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 160 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(50.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 163 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(270.f, -20.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}


	// 파란놈 난사
	if(m_iStageCount == 164 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
	
	if(m_iStageCount == 165 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -30.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}

	if(m_iStageCount == 166 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -20.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}
	
	if(m_iStageCount == 167 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 168 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -30.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}

	if(m_iStageCount == 169 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}

	if(m_iStageCount == 170 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -35.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 171 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -25.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}

	if(m_iStageCount == 172 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -36.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 173 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 174 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}

	if(m_iStageCount == 175 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -27.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 176 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -34.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 177 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -34.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 178 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -27.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 179 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -39.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}

	if(m_iStageCount == 180 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -25.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}

	if(m_iStageCount == 181 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 182 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -33.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 183 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -39.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}

	if(m_iStageCount == 184 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -28.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 185 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 186 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -30.f, 0.f), MONSTER_EASY, M_PATTON_FOUR), OBJ_MONSTER);
	}

	if(m_iStageCount == 187 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -28.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 188 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 189 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -33.f, 0.f), MONSTER_EASY, M_PATTON_THREE), OBJ_MONSTER);
	}

	if(m_iStageCount == 190 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}


	// 2줄 파랭이
	if(m_iStageCount == 196 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 198 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 200 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 202 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 204 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 206 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 208 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 210 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 212 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(330.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(310.f, -70.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}


	//
	if(m_iStageCount == 218 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 220 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 222 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 224 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 226 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 228 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 230 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 232 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount == 234 && m_dwStageCount == GetTickCount())
	{
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(80.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(100.f, -60.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}
	
	if(m_iStageCount == 250 && m_dwStageCount == GetTickCount())
	{
		ObjMgr->AddObject(CAbstractFactory<CBossMonster>::CreateNomalMonster(D3DXVECTOR3(200.f , -40.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
	}

	if(m_iStageCount > 410 && m_iStageCount < 500 && (m_iStageCount % 3) == 2 && GetTickCount() == m_dwStageCount)
	{
		if((rand() % 2) == 0)
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_EASY, M_PATTON_ONE), OBJ_MONSTER);
		else
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount > 410 && m_iStageCount < 500 && (m_iStageCount % 5) == 4 && GetTickCount() == m_dwStageCount)
	{
		if((rand() % 2) == 0)
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_NOMAL, M_PATTON_ONE), OBJ_MONSTER);
		else
			CObjMgr::GetInstance()->AddObject(CAbstractFactory<CNomalMonster>::CreateNomalMonster(D3DXVECTOR3(float(rand() % 350 + 50), -43.f, 0.f), MONSTER_NOMAL, M_PATTON_TWO), OBJ_MONSTER);
	}

	if(m_iStageCount == 510 && m_dwStageCount == GetTickCount())
	{
		CSoundMgr::GetInstance()->StopSoundAll();
		CSoundMgr::GetInstance()->PlayBGM(L"th06_03.mid", CHANNEL_BGM, 1.0f);
		m_bCreateBoss = true;
		ObjMgr->AddObject(CAbstractFactory<CBossMonster>::CreateNomalMonster(D3DXVECTOR3(200.f , -40.f, 0.f), MONSTER_EASY, M_PATTON_TWO), OBJ_MONSTER);
	}
}