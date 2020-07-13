#include "StdAfx.h"
#include "Effect.h"
#include "NomalMonsterBullet.h"

CEffect::CEffect(void)
{
}

CEffect::~CEffect(void)
{
	Release();
}

void CEffect::Initialize( void )
{
	switch(m_eEffectType)
	{
	case EFFECT_NOMAL:
		m_tInfo.vSize = D3DXVECTOR3(16.f, 16.f, 0.f);
		lstrcpy(m_Key, L"BulletBlue");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 1.f;
		break;
	case EFFECT_MID:
		m_tInfo.vSize = D3DXVECTOR3(16.f, 16.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 1.f;
		break;
	case EFFECT_16_B:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletBlue");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_A_1:
	case EFFECT_PATTON_I_1:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletBlue");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_A_2:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_A_3:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletGreen");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_A_4:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletYellow");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_A_5:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_B_1:
	case EFFECT_PATTON_H_2:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletGreen");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_B_2:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletYellow");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_C_1:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletYellow");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_B_3:
	case EFFECT_PATTON_G_2:
	case EFFECT_PATTON_H_1:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletBlue");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_B_4:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_D_1:
	case EFFECT_PATTON_D_2:
	case EFFECT_PATTON_D_3:
	case EFFECT_PATTON_D_4:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_E_1:
	case EFFECT_PATTON_E_2:
	case EFFECT_PATTON_E_3:
	case EFFECT_PATTON_J_1:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletBlue");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_F_1:
	case EFFECT_PATTON_I_2:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletGreen");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	case EFFECT_PATTON_G_1:
	case EFFECT_PATTON_I_3:
		m_tInfo.vSize = D3DXVECTOR3(24.f, 24.f, 0.f);
		lstrcpy(m_Key, L"BulletRed");
		m_eBulletNumber = BULLET_NUMBER_SEVEN;
		m_fSize				= 2.f;
		break;
	}

	
	m_iAlpa				= 80;
	m_iCount			= 0;
	m_dwCurFrameTime	= GetTickCount();
	m_tInfo.eRenderType = RENDER_EFFECT;
}

RETURN_TYPE CEffect::Update( void )
{
	if(m_dwCurFrameTime + 100 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();
		m_iAlpa += 80;

		if(m_iAlpa > 255)
			m_iAlpa = 255;

		++m_iCount;
		m_fSize -= 0.2f;
	}

	if(m_iCount > 2 && 
		(m_eEffectType == EFFECT_NOMAL 
		|| m_eEffectType == EFFECT_MID 
		|| m_eEffectType == EFFECT_PATTON_A_5
		|| m_eEffectType == EFFECT_PATTON_B_1
		|| m_eEffectType == EFFECT_PATTON_B_2
		|| m_eEffectType == EFFECT_PATTON_C_1
		|| m_eEffectType == EFFECT_PATTON_B_3
		|| m_eEffectType == EFFECT_PATTON_B_4
		|| m_eEffectType == EFFECT_PATTON_D_1
		|| m_eEffectType == EFFECT_PATTON_D_2
		|| m_eEffectType == EFFECT_PATTON_D_3
		|| m_eEffectType == EFFECT_PATTON_D_4
		|| m_eEffectType == EFFECT_PATTON_E_1
		|| m_eEffectType == EFFECT_PATTON_E_2
		|| m_eEffectType == EFFECT_PATTON_E_3
		|| m_eEffectType == EFFECT_PATTON_F_1
		|| m_eEffectType == EFFECT_PATTON_G_1
		|| m_eEffectType == EFFECT_PATTON_G_2
		|| m_eEffectType == EFFECT_PATTON_H_1
		|| m_eEffectType == EFFECT_PATTON_H_2
		|| m_eEffectType == EFFECT_PATTON_I_1
		|| m_eEffectType == EFFECT_PATTON_I_2
		|| m_eEffectType == EFFECT_PATTON_I_3
		|| m_eEffectType == EFFECT_PATTON_J_1))
		m_bDeadCheck = true;

	if(m_iCount > 3 && m_eEffectType == EFFECT_16_B)
		m_bDeadCheck = true;

	if(m_iCount > 14 && m_eEffectType == EFFECT_PATTON_A_1)
		m_bDeadCheck = true;

	if(m_iCount > 11 && m_eEffectType == EFFECT_PATTON_A_2)
		m_bDeadCheck = true;

	if(m_iCount > 8 && m_eEffectType == EFFECT_PATTON_A_3)
		m_bDeadCheck = true;

	if(m_iCount > 5 && m_eEffectType == EFFECT_PATTON_A_4)
		m_bDeadCheck = true;


	if(m_bDeadCheck)
	{
		switch(m_eEffectType)
		{
		case EFFECT_NOMAL:
			ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBullet(m_tInfo.vPos, BULLET_TYPE_GUIDED
				, BULLET_COLOR_BLUE, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo()), OBJ_MONSTER_BULLET);
			break;

		case EFFECT_MID:
			if((rand() % 3) == 0)
			{
				for(int i = -3; i < 3; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBullet(m_tInfo.vPos, BULLET_TYPE_ANGLE
						, BULLET_COLOR_RED, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i), OBJ_MONSTER_BULLET);
				}
			}
			else
			{
				for(int i = -6; i < 6; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBullet(m_tInfo.vPos, BULLET_TYPE_ANGLE
						, BULLET_COLOR_RED, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBullet(m_tInfo.vPos, BULLET_TYPE_ANGLE_TWO
						, BULLET_COLOR_RED, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_16_B:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBullet(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_A_1:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_BLUE, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 5), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_A_2:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_RED, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 8), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_A_3:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_GREEN, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 11), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_A_4:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_YELLOW, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 14), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_A_5:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_RED, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 17), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_B_1:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_GREEN, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_B_2:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_YELLOW, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, -20), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_C_1:

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_BLUE, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 5, 10.f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 10, 9.2f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_BLUE, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 15, 8.3f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_YELLOW, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 12, 7.6f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_GREEN, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 15, 7.f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_RED, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 18, 6.9f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_YELLOW, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 5, 6.3f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_GREEN, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 6, 5.8f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_RED, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 8, 5.f), OBJ_MONSTER_BULLET);

			for(int i = 0; i < 36; ++i)
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
				, BULLET_COLOR_YELLOW, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 5, 3.8f), OBJ_MONSTER_BULLET);

			break;

		case EFFECT_PATTON_B_3:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 10), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_B_4:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL
					, BULLET_COLOR_RED, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, -10), OBJ_MONSTER_BULLET);
			}
			break;

		case EFFECT_PATTON_D_1:
			{
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 14.f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 13.5f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 13.f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 12.5f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 12.f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 11.5f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 11.f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 10.5f), OBJ_MONSTER_BULLET);

				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
					, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 10.f), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_D_2:
			{
				for(int i = -1; i < 1; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 14.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_D_3:
			{
				for(int i = -1; i < 2; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 14.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_D_4:
			{
				for(int i = -2; i < 2; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 14.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_TWO, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.f), OBJ_MONSTER_BULLET);
				}
			}
			break;

		case EFFECT_PATTON_E_1:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 5, 7.f), OBJ_MONSTER_BULLET);

				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 20, 6.f), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_E_2:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 7.f), OBJ_MONSTER_BULLET);

				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_EIGHT, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 10, 6.f), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_E_3:
			{
				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 10, 5.f), OBJ_MONSTER_BULLET);

				for(int i = 0; i < 36; ++i)
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_ALL_TWO
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 15, 4.f), OBJ_MONSTER_BULLET);
			}
			break;
		case EFFECT_PATTON_F_1:
			{
				for(int i = 0; i < 11; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST_TWO
						, BULLET_COLOR_GREEN, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, -130, 7.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_G_1:
			{
				for(int i = -2; i < 2; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 13.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 12.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 11.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 10.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 9.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 9.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 8.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 8.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 7.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 7.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 6.5f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 6.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_G_2:
			{
				for(int i = 0; i < 64; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST_TWO
						, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 7.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_H_1:
			{
				for(int i = -5; i < 5; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0.f + rand() % 160 / 4, 5.f + float(rand() % 200) / 80.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_H_2:
			{
				for(int i = -5; i < 5; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_ANGLE_FAST
						, BULLET_COLOR_GREEN, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0.f - rand() % 160 / 4, 5.f + float(rand() % 200) / 80.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_I_1:
			{
				for(int i = 0; i < 64; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL
						, BULLET_COLOR_BLUE, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 3.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL_TWO
						, BULLET_COLOR_BLUE, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 3.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_I_2:
			{
				for(int i = 0; i < 64; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL
						, BULLET_COLOR_GREEN, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 2, 3.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL_TWO
						, BULLET_COLOR_GREEN, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 2, 3.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_I_3:
			{
				for(int i = 0; i < 64; ++i)
				{
					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 3.f), OBJ_MONSTER_BULLET);

					ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL_TWO
						, BULLET_COLOR_RED, BULLET_NUMBER_THREE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), i, 0, 3.f), OBJ_MONSTER_BULLET);
				}
			}
			break;
		case EFFECT_PATTON_J_1:
			{
				ObjMgr->AddObject(CAbstractFactory<CNomalMonsterBullet>::CreateMonsterBulletAngle(m_tInfo.vPos, BULLET_TYPE_HELL_THREE
					, BULLET_COLOR_BLUE, BULLET_NUMBER_FIVE, (ObjMgr->GetObjList(OBJ_PLAYER)->front())->GetInfo(), 0, 0, 3.f), OBJ_MONSTER_BULLET);
			}
			break;
		}

		return RETURN_DEAD;
	}

	return RETURN_NULL;
}

void CEffect::Render( HDC hDc )
{

	D3DXMATRIX matRotZ, matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, 0.f);
	D3DXMatrixRotationZ(&matRotZ, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&(m_tInfo.matWorld));

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(m_Key, m_Key, m_eBulletNumber)->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpa, 255, 255, 255));
}

void CEffect::Release( void )
{

}