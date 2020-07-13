#include "StdAfx.h"
#include "BossMonster.h"
#include "Effect.h"
#include "DeadEffect.h"
#include "SmallEffect.h"

CBossMonster::CBossMonster(void)
{
}

CBossMonster::~CBossMonster(void)
{
	Release();
}

void CBossMonster::Initialize( void )
{
	switch(m_eMonsterPatton)
	{
	case M_PATTON_ONE:
		m_iHp = 600;
		break;
	case M_PATTON_TWO:
		m_iHp = 2000;
		break;
	}

	m_tInfo.vSize = D3DXVECTOR3(32.f, 50.f, 0.f);
	m_dwCurFrameTime	= GetTickCount();
	m_dwOldFrameTime	= GetTickCount();
	m_dwCurPattonCount	= GetTickCount();
	m_iPattonCount		= 0;
	m_fTime				= 1.f;
	m_bTurn				= false;
	m_fLookLeft			= 1.f;
	m_tFrame			= FRAME(0, 0, 100);
	m_dwState			= MONSTER_STAND;
	m_dwPreState		= m_dwState;
	m_bBossOn			= false;
	m_iAddCount			= 0;
	m_bBossBoom			= false;
}

RETURN_TYPE CBossMonster::Update( void )
{
	if(m_bDeadCheck)
	{
		switch(m_eMonsterPatton)
		{
		case M_PATTON_ONE:
			{
				m_dwState = MONSTER_STAND;
				m_tInfo.vPos.y -= 6.f;

				if(m_tInfo.vPos.y < - 50.f)
					return RETURN_DEAD;

				return RETURN_NULL;
			}
			break;
		case M_PATTON_TWO:
			{
				CSoundMgr::GetInstance()->PlaySound(L"enep01.wav", CHANNEL_MONSTER, 1.0f);
				CSoundMgr::GetInstance()->PlaySound(L"enep01.wav", CHANNEL_EFF, 1.0f);
				CSoundMgr::GetInstance()->PlaySound(L"enep01.wav", CHANNEL_PLAYER, 1.0f);

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
				return RETURN_DEAD;
			}
			break;
		}
	}

	if(m_iHp <= 0 || m_iAddCount > 1)
		m_bDeadCheck = true;

	SetFrame();
	Patton();
	return RETURN_NULL;
}

void CBossMonster::Render( HDC hDc )
{
	if(m_dwState != MONSTER_ATTACK)
	{
		D3DXMATRIX matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixScaling(&matScale, m_fLookLeft, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"BossMonsterMove", L"BossMonsterMove", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		D3DXMATRIX matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixScaling(&matScale, m_fLookLeft, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"BossMonsterAttack", L"BossMonsterAttack", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CBossMonster::Release( void )
{

}

void CBossMonster::Patton( void )
{
	if(m_dwCurPattonCount + 200 < GetTickCount())
	{
		m_dwCurPattonCount = GetTickCount();
		++m_iPattonCount;
	}

	switch(m_eMonsterPatton)
	{
	case M_PATTON_ONE:
		{
			if(m_iPattonCount < 5)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( 4.f, 4.f, 0.f);
			}
			if(m_iPattonCount > 5 &&
				m_iPattonCount < 10)
			{
				m_dwState = MONSTER_STAND;
			}
			if(m_iPattonCount == 11)
			{
				m_bBossOn = true;
			}

			if(m_bBossOn 
				&& (m_iPattonCount == 11 || m_iPattonCount == 13))
			{
				m_dwState = MONSTER_ATTACK;

				CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);

				if((GetTickCount() % 4) == 0)
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_16_B), OBJ_EFFECT);
			}

			if(m_bBossOn 
				&& (m_iPattonCount == 20 || m_iPattonCount == 21 || m_iPattonCount == 22))
			{
				m_fLookLeft = -1.f;
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( -7.f, -2.f, 0.f);
			}

			if(m_bBossOn 
				&& m_iPattonCount == 23
				&& m_dwCurPattonCount == GetTickCount())
			{
				CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
				m_dwState = MONSTER_ATTACK;
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_A_1), OBJ_EFFECT);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 24
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_A_2), OBJ_EFFECT);
			}

			if(m_bBossOn 
				&& m_iPattonCount == 25
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_A_3), OBJ_EFFECT);
			}

			if(m_bBossOn 
				&& m_iPattonCount == 26
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_A_4), OBJ_EFFECT);
			}

			if(m_bBossOn 
				&& m_iPattonCount == 27
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_A_5), OBJ_EFFECT);
			}

			//
			if(m_bBossOn 
				&& m_iPattonCount == 38)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( -7.f, 1.f, 0.f);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 39)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( -3.f, 1.f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_B_1), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_1), OBJ_EFFECT);
				}
			}
			if(m_bBossOn 
				&& m_iPattonCount == 40)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( -3.f, 1.f, 0.f);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 41)
			{
				m_tInfo.vPos += D3DXVECTOR3( -3.f, 1.f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_B_2), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_2), OBJ_EFFECT);
				}
			}
			if(m_bBossOn 
				&& m_iPattonCount == 42)
			{
				m_dwState = MONSTER_STAND;
			}
			if(m_bBossOn 
				&& (m_iPattonCount == 50 || m_iPattonCount == 51))
			{
				m_dwState = MONSTER_MOVE;
				m_fLookLeft = 1.f;
				m_tInfo.vPos += D3DXVECTOR3( 7.f, -2.f, 0.f);
			}

			if(m_bBossOn 
				&& m_iPattonCount == 52
				&& m_dwCurPattonCount == GetTickCount())
			{
				m_dwState = MONSTER_ATTACK;

				CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_C_1), OBJ_EFFECT);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 62)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( 7.f, 1.f, 0.f);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 63)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( 3.f, 1.f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_B_1), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_3), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_3), OBJ_EFFECT);
				}
			}
			if(m_bBossOn 
				&& m_iPattonCount == 64)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3( 7.f, 1.f, 0.f);
			}
			if(m_bBossOn 
				&& m_iPattonCount == 65)
			{
				m_tInfo.vPos += D3DXVECTOR3( 3.f, 1.f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_B_2), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_4), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f, m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f, 0.f), EFFECT_PATTON_B_4), OBJ_EFFECT);
				}
				m_dwState = MONSTER_STAND;
			}

			if(m_bBossOn 
				&& m_iPattonCount == 75)
			{
				++m_iAddCount;
				m_iPattonCount = 10;
			}
		}
		break;
	case M_PATTON_TWO:
		{
			if(m_iPattonCount < 3)
				m_tInfo.vPos.y += 5.f;

			if(m_iPattonCount > 3 &&
				m_iPattonCount < 11)
			{
				m_fLookLeft = 1.f;
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(2.5f, 0.5f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					if(m_iPattonCount == 4)
					{
						CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_1), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 5)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_1), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 6)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_2), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 7)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_2), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 8)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_3), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 9)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_3), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 10)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_4), OBJ_EFFECT);
					}
				}
			}

			if(m_iPattonCount == 11)
			{
				m_dwState = MONSTER_STAND;
			}

			if(m_iPattonCount == 16 
				|| m_iPattonCount == 17
				|| m_iPattonCount == 18)
			{
				if(m_iPattonCount == 16)
					m_dwState = MONSTER_MOVE;

				m_fLookLeft = -1.f;
				m_tInfo.vPos += D3DXVECTOR3(-6.f, -0.5f, 0.f);
			}

			if(m_iPattonCount == 22
				&& m_dwCurPattonCount == GetTickCount())
			{
				CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);
				m_dwState = MONSTER_ATTACK;
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_1), OBJ_EFFECT);
			}
			if(m_iPattonCount == 24
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_2), OBJ_EFFECT);
			}
			if(m_iPattonCount == 26
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_3), OBJ_EFFECT);
			}

			if(m_iPattonCount > 33 && m_iPattonCount < 41)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(-0.5f, -0.5f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
					if(m_iPattonCount == 34)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_1), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 35)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_1), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 36)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_2), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 37)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_2), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 38)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_3), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 39)
					{
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_3), OBJ_EFFECT);
					}
					else if(m_iPattonCount == 40)
					{
						m_dwState = MONSTER_STAND;
						ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
							D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_D_4), OBJ_EFFECT);
					}
				}
			}

			if(m_iPattonCount == 41)
			{
				m_dwState = MONSTER_STAND;
			}

			if(m_iPattonCount >= 47 && m_iPattonCount <= 49)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(-4.5f, 0.5f, 0.f);

				if(GetTickCount() == m_dwCurFrameTime)
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_F_1), OBJ_EFFECT);
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
				}
			}

			if(m_iPattonCount == 50)
				m_dwState = MONSTER_STAND;

			if(m_iPattonCount == 54 || m_iPattonCount == 55)
			{
				m_fLookLeft = 1.f;
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(2.5f, 0.5f, 0.f);
			}
			if(m_iPattonCount == 56)
				m_dwState = MONSTER_STAND;

			if(m_iPattonCount == 63 && GetTickCount() == m_dwCurPattonCount)
			{
				m_dwState = MONSTER_ATTACK;

				CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_G_1), OBJ_EFFECT);
			}

			if((m_iPattonCount == 61 || m_iPattonCount == 64 || m_iPattonCount == 67)
				&& GetTickCount() == m_dwCurPattonCount)
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_G_2), OBJ_EFFECT);
			}

			if(m_iPattonCount == 68)
				m_dwState = MONSTER_STAND;

			if(m_iPattonCount > 74 && m_iPattonCount < 77)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(7.f, 1.f, 0.f);
			}

			if(m_iPattonCount == 78 && m_dwCurPattonCount == GetTickCount())
			{
				CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
				m_dwState = MONSTER_STAND;
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_1), OBJ_EFFECT);
			}
			if(m_iPattonCount == 79
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_2), OBJ_EFFECT);
			}
			if(m_iPattonCount == 80
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_1), OBJ_EFFECT);
			}
			if(m_iPattonCount == 81
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_2), OBJ_EFFECT);
			}
			if(m_iPattonCount == 82
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_3), OBJ_EFFECT);
			}
			if(m_iPattonCount == 83 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_1), OBJ_EFFECT);
			}
			if(m_iPattonCount == 84
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_2), OBJ_EFFECT);
			}
			if(m_iPattonCount == 85
				&& m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_E_3), OBJ_EFFECT);
			}

			if(m_iPattonCount == 86
				&& m_dwCurPattonCount == GetTickCount())
				m_dwState = MONSTER_STAND;


			if(m_iPattonCount > 98 && m_iPattonCount < 102)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(2.5f, 1.f, 0.f);
			}

			if(m_iPattonCount == 104 && GetTickCount() == m_dwCurPattonCount)
			{
				m_dwState = MONSTER_ATTACK;

				CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_G_1), OBJ_EFFECT);
			}

			if((m_iPattonCount == 102 || m_iPattonCount == 105 || m_iPattonCount == 108)
				&& GetTickCount() == m_dwCurPattonCount)
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_G_2), OBJ_EFFECT);
			}

			if(m_iPattonCount == 109 && GetTickCount() == m_dwCurPattonCount)
				m_dwState = MONSTER_STAND;

			if(m_iPattonCount > 118 && m_iPattonCount < 122)
			{
				m_dwState = MONSTER_MOVE;
				m_tInfo.vPos += D3DXVECTOR3(-3.0f, -1.f, 0.f);
			}

			if(m_iPattonCount == 122)
			{
				m_bBossBoom = true;
				m_dwState = MONSTER_STAND;
			}
			if(m_bBossBoom && m_iPattonCount > 124 && m_iPattonCount < 162
				&& m_dwCurPattonCount == GetTickCount())
			{
				if((m_iPattonCount % 6) < 3)
				{
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_1), OBJ_EFFECT);
				}
				else
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_2), OBJ_EFFECT);
				}
			}

			if(m_iPattonCount > 169 && m_iPattonCount < 172)
			{
				m_dwState = MONSTER_MOVE;
				m_fLookLeft = -1.f;
				m_tInfo.vPos += D3DXVECTOR3(-3.0f, -1.f, 0.f);
			}
			if(m_iPattonCount == 172)
				m_dwState = MONSTER_STAND;


			if(m_bBossBoom && m_iPattonCount > 175 && m_iPattonCount < 213
				&& m_dwCurPattonCount == GetTickCount())
			{
				if((m_iPattonCount % 6) < 3)
				{
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_1), OBJ_EFFECT);
				}
				else
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_2), OBJ_EFFECT);
				}
			}

			if(m_iPattonCount > 220 && m_iPattonCount < 225)
			{

				m_dwState = MONSTER_MOVE;
				m_fLookLeft = 1.f;
				m_tInfo.vPos += D3DXVECTOR3(6.0f, 1.f, 0.f);
			}



			if(m_bBossBoom && m_iPattonCount > 225 && m_iPattonCount < 263
				&& m_dwCurPattonCount == GetTickCount())
			{
				m_dwState = MONSTER_STAND;
				if((m_iPattonCount % 6) < 3)
				{
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_1), OBJ_EFFECT);
				}
				else
				{
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_H_2), OBJ_EFFECT);
				}
			}

			if(m_iPattonCount > 277 && m_iPattonCount < 283)
			{
				m_dwState = MONSTER_MOVE;
				m_fLookLeft = -1.f;
				m_tInfo.vPos += D3DXVECTOR3(-3.0f, -1.f, 0.f);
			}


			if(m_bBossBoom && m_iPattonCount == 284 && m_dwCurPattonCount == GetTickCount())
			{
				CSoundMgr::GetInstance()->PlaySound(L"power1.wav", CHANNEL_MONSTER, 1.0f);
				m_dwState = MONSTER_STAND;
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_1), OBJ_EFFECT);
			}

			if(m_bBossBoom && m_iPattonCount == 294 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_1), OBJ_EFFECT);
			}


			if(m_bBossBoom && m_iPattonCount == 304 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_2), OBJ_EFFECT);
			}

			if(m_bBossBoom && m_iPattonCount == 314 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_2), OBJ_EFFECT);
			}

			if(m_bBossBoom && m_iPattonCount == 324 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_3), OBJ_EFFECT);
			}

			if(m_bBossBoom && m_iPattonCount == 334 && m_dwCurPattonCount == GetTickCount())
			{
				ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
					D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_I_3), OBJ_EFFECT);
			}

			if(m_bBossBoom && m_iPattonCount > 339 && m_iPattonCount < 345)
			{
				m_dwState = MONSTER_MOVE;
				m_fLookLeft = -1.f;
				m_tInfo.vPos += D3DXVECTOR3(-4.0f, 1.f, 0.f);

				if(m_dwCurPattonCount == GetTickCount())
				{
					CSoundMgr::GetInstance()->PlaySound(L"power0.wav", CHANNEL_MONSTER, 1.0f);
					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_J_1), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x - 10, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_J_1), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x - 20, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_J_1), OBJ_EFFECT);

					ObjMgr->AddObject(CAbstractFactory<CEffect>::CreateEffect(
						D3DXVECTOR3(m_tInfo.vPos.x - 30, m_tInfo.vPos.y, 0.f), EFFECT_PATTON_J_1), OBJ_EFFECT);
				}

			}

			if(m_iPattonCount == 345)
				m_dwState = MONSTER_STAND;

			if(m_iPattonCount > 355 && m_iPattonCount < 361)
			{
				m_dwState = MONSTER_MOVE;
				m_fLookLeft = 1.f;
				m_tInfo.vPos += D3DXVECTOR3(4.0f, -1.f, 0.f);
			}

			if(m_iPattonCount == 361)
				m_dwState = MONSTER_STAND;


			if(m_iPattonCount > 370)
				m_iPattonCount = 3;

		}
		break;
	}
}

void CBossMonster::SetFrame( void )
{
	if(m_dwState != m_dwPreState)
	{
		switch(m_dwState)
		{
		case MONSTER_STAND:
			m_tFrame = FRAME(0, 0, 100);
			break;
		case MONSTER_MOVE:
			m_tFrame = FRAME(0, 4, 100);
			break;
		case MONSTER_ATTACK:
			m_tFrame = FRAME(0, 4, 100);
			break;
		}

		m_dwPreState = m_dwState;
	}

	m_dwCurFrameTime = GetTickCount();

	if(m_dwOldFrameTime + m_tFrame.dwFramespd < m_dwCurFrameTime)
	{
		m_dwOldFrameTime = m_dwCurFrameTime;

		if(m_bTurn == false)
			++m_tFrame.iFrameStart;
		else
			--m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		if(m_dwState == MONSTER_STAND)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		else if(m_dwState == MONSTER_MOVE)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		else
		{
			m_bTurn = true;
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}
	}

	if(m_tFrame.iFrameStart < 0)
	{
		m_bTurn = false;
		m_dwState = MONSTER_STAND;
		m_tFrame.iFrameStart = 0;
	}
}