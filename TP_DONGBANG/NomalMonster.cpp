#include "StdAfx.h"
#include "NomalMonster.h"
#include "Effect.h"

#include "Item.h"
#include "DeadEffect.h"
#include "SmallEffect.h"
#include "Player.h"

CNomalMonster::CNomalMonster(void)
{
}

CNomalMonster::~CNomalMonster(void)
{
	Release();
}

void CNomalMonster::Initialize( void )
{
	switch(m_eMonsterType)
	{
	case MONSTER_EASY:
		m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0.f);
		m_fAngle = 30.f;
		m_fSpeed = 3.f;
		m_iHp	 = 3;
		break;
	case MONSTER_NOMAL:
		m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0.f);
		m_fSpeed = 2.f;
		m_iHp	 = 7;
		break;
	}

	m_tFrame = FRAME(0, 7, 100);
	m_dwCurFrameTime	= GetTickCount();
	m_dwOldFrameTime	= GetTickCount();
	m_dwCurPattonCount	= GetTickCount();
	m_iPattonCount		= 0;
	m_fTime				= 1.f;
	m_bTurn				= false;
	
}

RETURN_TYPE CNomalMonster::Update( void )
{
	if(m_bDeadCheck)
	{
		OBJLIST* m_pPlayerList = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYER);
		CObj* pPlayer = m_pPlayerList->front();

		// Player 점수 증가
		dynamic_cast<CPlayer*>(pPlayer)->PlusScore(100);

		CSoundMgr::GetInstance()->PlaySound(L"enep00.wav", CHANNEL_MONSTER, 1.0f);
		// 죽는 이펙트
		CObj* pEffect = new CDeadEffect;
		pEffect->Initialize();
		pEffect->SetPos(m_tInfo.vPos + m_tInfo.vSize/2.f);

		CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

		for(int i = 0; i < 8; ++i)
		{
			int iRnd = rand() % 2;

			CObj* pEffect2 = new CSmallEffect;
			pEffect2->Initialize();
			pEffect2->SetPos(m_tInfo.vPos + m_tInfo.vSize/2.f);
			dynamic_cast<CSmallEffect*>(pEffect2)->SetType(iRnd);

			CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
		}
		

		// 아이템 생성 ( 일정 확률로 )
		int rnd = rand() % 10;
		if(rnd == 0)
		{
			CObj* pItem = new CItem;
			dynamic_cast<CItem*>(pItem)->SetItemType(ITEM_BIGPOWER);
			pItem->Initialize();
			pItem->SetPos(m_tInfo.vPos + m_tInfo.vSize/2.f);
			dynamic_cast<CItem*>(pItem)->SetTargetY(m_tInfo.vPos.y - 20.f);

			CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
		}

		rnd = rand() % 2;
		if(rnd == 0)
		{	
			CObj* pItem = new CItem;
			dynamic_cast<CItem*>(pItem)->SetItemType(ITEM_POWER);
			pItem->Initialize();
			pItem->SetPos(m_tInfo.vPos + m_tInfo.vSize/2.f);
			dynamic_cast<CItem*>(pItem)->SetTargetY(m_tInfo.vPos.y - 20.f);

			CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
		}
		

		return RETURN_DEAD;
	}

	if(m_iHp <= 0)
		m_bDeadCheck = true;

	SetFrame();
	Patton();

	if(m_tInfo.vPos.y < -100
		|| m_tInfo.vPos.y > 480
		|| m_tInfo.vPos.x < 10
		|| m_tInfo.vPos.x > 415)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CNomalMonster::Render( HDC hDc )
{

	if(m_eMonsterType == MONSTER_EASY)
	{
		D3DXMATRIX matRotZ, matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"EasyMonster", L"EasyMonster", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else if(m_eMonsterType == MONSTER_NOMAL)
	{
		D3DXMATRIX matRotZ, matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matRotZ * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"NomalMonster", L"NomalMonster", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	
}

void CNomalMonster::Release( void )
{

}

void CNomalMonster::Patton( void )
{
	if(m_dwCurPattonCount + 500 < GetTickCount())
	{
		m_dwCurPattonCount = GetTickCount();

		++m_iPattonCount;
			
	}

	D3DXMATRIX matTrans;

	if(m_eMonsterType == MONSTER_EASY)
	{
		switch(m_eMonsterPatton)
		{
		case M_PATTON_ONE:
			if(m_iPattonCount < 3)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else
			{
				++m_fTime;
				m_tInfo.vPos.x += m_fSpeed / 1.5f;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		case M_PATTON_TWO:
			if(m_iPattonCount < 3)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else
			{ 
				++m_fTime;
				m_tInfo.vPos.x -= m_fSpeed / 1.5f;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		case M_PATTON_THREE:
			if(m_iPattonCount < 5)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else
			{
				++m_fTime;
				m_tInfo.vPos.x -= m_fSpeed;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		case M_PATTON_FOUR:
			if(m_iPattonCount < 5)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else
			{
				++m_fTime;
				m_tInfo.vPos.x += m_fSpeed;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		}

		if((m_iPattonCount % 2) == 1 && m_dwCurPattonCount == GetTickCount()
			&& (rand() % 2) == 0)
		{
			ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
				D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_NOMAL), OBJ_EFFECT);
		}
	}
	else if(m_eMonsterType == MONSTER_NOMAL)
	{
		switch(m_eMonsterPatton)
		{
		case M_PATTON_ONE:
			if(m_iPattonCount < 3)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else if(m_iPattonCount == 3 || m_iPattonCount == 4)
			{
				if(m_iPattonCount == 4 && m_dwCurPattonCount == GetTickCount())
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_MID), OBJ_EFFECT);
				}
			}
			else
			{
				++m_fTime;
				m_tInfo.vPos.x -= m_fSpeed;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		case M_PATTON_TWO:
			if(m_iPattonCount < 3)
			{
				m_tInfo.vPos.y += m_fSpeed;
			}
			else if(m_iPattonCount == 3 || m_iPattonCount == 4)
			{
				if(m_iPattonCount == 4 && m_dwCurPattonCount == GetTickCount())
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_MID), OBJ_EFFECT);
				}
			}
			else
			{
				++m_fTime;
				m_tInfo.vPos.x += m_fSpeed;
				m_tInfo.vPos.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed - powf(m_fTime, 2) * 0.00098f;
			}
			break;
		}
	}
}

void CNomalMonster::SetFrame( void )
{
	if(m_dwCurFrameTime + m_tFrame.dwFramespd < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();

		++m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;
	}
}	   