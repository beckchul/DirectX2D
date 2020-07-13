#include "StdAfx.h"
#include "Player.h"

#include "PlayerBullet.h"
#include "SubWeapon.h"
#include "EffectPower.h"
#include "PlayerIllust.h"
#include "SmallEffect.h"

CPlayer::CPlayer(void)
:m_pSubWeapon1(NULL)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize( void )
{
	ZeroMemory(&m_tPlayerInfo, sizeof(PlayerInfo));
	m_tPlayerInfo.iLife = 4;
	m_tPlayerInfo.iBomb = 3;
	m_tPlayerInfo.bBombIsReady = true;

	m_tInfo.vPos.x = 200.f;
	m_tInfo.vPos.y = 400.f;

	m_tInfo.vSize.x = 25.f;
	m_tInfo.vSize.y = 45.f;

	m_eCurState = PLAYER_IDLE;
	m_eDir = PLAYER_LEFT;

	m_tInfo.eRenderType = RENDER_OBJ;

	m_fSpeed = 5.f;

	m_fScaleX = 1.f;
	m_fScaleY = 1.f;

	m_dwAlphaOld = 0;
	m_dwAlphaCur = 0;

	m_dwRevivalTime = 0;

	m_bARGB = false;
	m_bBlend = false;
	m_dwBlendingTime = 0;
	m_iRGB = 255;

	m_dwBombCountTime = 0;

	m_dwSearchBulletOldTime = GetTickCount();
	m_dwSearchBulletCurTime = 0;

	m_dwNormalBulletOldTime = GetTickCount();
	m_dwNormalBulletCurTime = 0;
}

RETURN_TYPE CPlayer::Update( void )
{
	if(m_bDeadCheck)
	{
		// 점점 줄어듬
		if(m_fScaleX > 0)
			m_fScaleX -= 0.2f;
		else
			m_fScaleX = 0;

		if(m_fScaleY < 3)
			m_fScaleY += 0.5f;
		else
			m_fScaleY = 3.f;

		// 3. 서브 무기 없애야함
		if(!(CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERSUBWEAPON)->empty()))
		{
			OBJITER iter_begin = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERSUBWEAPON)->begin();
			OBJITER iter_end = CObjMgr::GetInstance()->GetObjList(OBJ_PLAYERSUBWEAPON)->end();

			for(; iter_begin != iter_end; ++iter_begin)
				(*iter_begin)->IsDead();
		}

		// 부활 딜레이
		if(m_dwRevivalTime + 2500 < GetTickCount())
		{
			// 다시 나타나면

			// 1. 위치 다시 잡고
			m_tInfo.vPos.x = 200.f;
			m_tInfo.vPos.y = 400.f;

			// 2. 파워 카운트 초기화
			m_tPlayerInfo.iPower = 0;
			m_tPlayerInfo.iBulletCount = 0;
			m_tPlayerInfo.bIsSubWeapon = false;

			// 3. bomb 사용 가능
			m_tPlayerInfo.iBomb = 3;
			m_tPlayerInfo.bBombIsReady = true;

			// 나타나면 깜빡임 시작
			m_bBlend = true;
			m_dwBlendingTime = GetTickCount();

			m_bDeadCheck = false;
		}
	}

	//5. 다시 나타날때 rgb값 검은색->원래색 깜빡깜빡 간격있어야함
	if(m_bBlend)
	{
		// 이때 다시 늘어남
		if(m_fScaleX < 1.f)
			m_fScaleX += 0.2f;
		else
			m_fScaleX = 1.f;

		if(m_fScaleY > 1.f)
			m_fScaleY -= 0.5f;
		else
			m_fScaleY = 1.f;

		if(m_dwBlendingTime + 2500 > GetTickCount())
		{
			// 이때 동안 무적
			m_tPlayerInfo.bPower = true;		

			m_dwAlphaCur = GetTickCount();

			if(m_dwAlphaOld + 100 < m_dwAlphaCur)
			{
				m_dwAlphaOld = m_dwAlphaCur;
				if(!m_bARGB)
				{
					m_bARGB = true;
					m_iRGB = 50;
				}
				else
				{
					m_bARGB = false;
					m_iRGB = 255;
				}
			}
		}
		else
		{
			m_tPlayerInfo.bPower = false;
			m_iRGB = 255;
			m_bBlend = false;
		}
	}


	if(m_eCurState == PLAYER_MOVE)
		m_eCurState = PLAYER_IDLE;

	KeyInput();

	FrameMove();

	if(!m_tPlayerInfo.bIsSubWeapon)
	{
		if(m_tPlayerInfo.iPower >= 8)
		{
			CObj* m_pSubWeapon1 = new CSubWeapon;
			m_pSubWeapon1->Initialize();
			m_pSubWeapon1->SetPos(m_tInfo.vPos + D3DXVECTOR3(-20.f, 10.f, 0.f));
			dynamic_cast<CSubWeapon*>(m_pSubWeapon1)->SetPlayer(this);
			dynamic_cast<CSubWeapon*>(m_pSubWeapon1)->SetDir(PLAYERSUBWEPAON_LEFT);

			CObjMgr::GetInstance()->AddObject(m_pSubWeapon1, OBJ_PLAYERSUBWEAPON);

			CObj* m_pSubWeapon2 = new CSubWeapon;
			m_pSubWeapon2->Initialize();
			m_pSubWeapon2->SetPos(m_tInfo.vPos + D3DXVECTOR3(30.f, 10.f, 0.f));
			dynamic_cast<CSubWeapon*>(m_pSubWeapon2)->SetPlayer(this);
			dynamic_cast<CSubWeapon*>(m_pSubWeapon2)->SetDir(PLAYERSUBWEPAON_RIGHT);

			CObjMgr::GetInstance()->AddObject(m_pSubWeapon2, OBJ_PLAYERSUBWEAPON);

			m_tPlayerInfo.bIsSubWeapon = true;
		}
	}

	if(m_tPlayerInfo.iPower >= 32)
	{
		m_tPlayerInfo.iBulletCount = 3;
	}
	else if(m_tPlayerInfo.iPower >= 24)
	{
		m_tPlayerInfo.iBulletCount = 2;
		m_iSearchBulletDelay = 100;
	}
	else if(m_tPlayerInfo.iPower >= 16)
	{
		m_tPlayerInfo.iBulletCount = 1;
		m_iSearchBulletDelay = 300;
	}
	else if(m_tPlayerInfo.iPower >= 8)
	{
		m_tPlayerInfo.iBulletCount = 0;
		m_iSearchBulletDelay = 500;
	}


	return RETURN_NULL;
}

void CPlayer::Render( HDC hDc )
{
	if(m_eCurState == PLAYER_IDLE)
	{
		D3DXMATRIX matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"PlayerIdle", L"Idle", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, m_iRGB, m_iRGB, m_iRGB));


	}
	else if(m_eCurState == PLAYER_MOVE)
	{
		D3DXMATRIX matScale, matTrans;

		D3DXMatrixIdentity(&(m_tInfo.matWorld));

		if(m_eDir == PLAYER_LEFT)
		{
			D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, 0.f);
		}
		else if(m_eDir == PLAYER_RIGHT)
		{
			D3DXMatrixScaling(&matScale, -m_fScaleX, m_fScaleY, 0.f);
		}

		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, m_tInfo.vPos.z);

		m_tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"PlayerMove", L"Move", m_tFrame.iFrameStart)->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, m_iRGB, m_iRGB, m_iRGB));

	}
}

void CPlayer::Release( void )
{
}

void CPlayer::KeyInput( void )
{
	if(m_bDeadCheck)
		return;

	/*제한 범위
	좌 : 10
	우 : 400
	상 : 10
	하 : 440*/


	if(CKeyMgr::GetInstance()->StayKeyDown(VK_UP))
	{

		m_eCurState = PLAYER_IDLE;
		m_tInfo.vPos.y -= m_fSpeed;

		if(m_tInfo.vPos.y <= 10 )
		{
			m_tInfo.vPos.y += m_fSpeed;
		}
	}
	if(CKeyMgr::GetInstance()->StayKeyDown(VK_DOWN))
	{
		m_eCurState = PLAYER_IDLE;
		m_tInfo.vPos.y += m_fSpeed;

		if(m_tInfo.vPos.y >= 440)
		{
			m_tInfo.vPos.y -= m_fSpeed;
		}
	}
	if(CKeyMgr::GetInstance()->StayKeyDown(VK_LEFT))
	{
		m_eCurState = PLAYER_MOVE;
		m_eDir = PLAYER_LEFT;
		m_tInfo.vPos.x -= m_fSpeed;

		if(m_tInfo.vPos.x <= 10)
		{
			m_tInfo.vPos.x += m_fSpeed;
		}
	}
	if(CKeyMgr::GetInstance()->StayKeyDown(VK_RIGHT))
	{
		m_eCurState = PLAYER_MOVE;
		m_eDir = PLAYER_RIGHT;
		m_tInfo.vPos.x += m_fSpeed;

		if(m_tInfo.vPos.x >= 400)
		{
			m_tInfo.vPos.x -= m_fSpeed;
		}
	}

	// 총알발사
	if(CKeyMgr::GetInstance()->StayKeyDown('Z'))
	{
		CSoundMgr::GetInstance()->PlaySound(L"plst00.wav", CHANNEL_PLAYER, 1.0f);

		m_dwNormalBulletCurTime = GetTickCount();
		if(m_dwNormalBulletOldTime + 100 < m_dwNormalBulletCurTime)
		{
			m_dwNormalBulletOldTime = m_dwNormalBulletCurTime;

			if(m_tPlayerInfo.iBulletCount == 0)
			{
				CObj* pBullet = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet->Initialize();
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));

				CObjMgr::GetInstance()->AddObject(pBullet, OBJ_PLAYERNORMALBULLET);
			}
			else if(m_tPlayerInfo.iBulletCount == 1)
			{
				CObj* pBullet = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet->Initialize();
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(0.f, 0.f, 0.f));

				CObj* pBullet2 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet2)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet2->Initialize();
				pBullet2->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-10.f, 0.f, 0.f));

				CObjMgr::GetInstance()->AddObject(pBullet, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet2, OBJ_PLAYERNORMALBULLET);
			}
			else if(m_tPlayerInfo.iBulletCount == 2)
			{
				CObj* pBullet = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet->Initialize();
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet)->SetNormalAngle(95.f);

				CObj* pBullet2 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet2)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet2->Initialize();
				pBullet2->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet2)->SetNormalAngle(90.f);

				CObj* pBullet3 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet3)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet3->Initialize();
				pBullet3->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet3)->SetNormalAngle(85.f);

				CObjMgr::GetInstance()->AddObject(pBullet, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet2, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet3, OBJ_PLAYERNORMALBULLET);
			}
			else if(m_tPlayerInfo.iBulletCount == 3)
			{
				CObj* pBullet = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet->Initialize();
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet)->SetNormalAngle(96.f);

				CObj* pBullet2 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet2)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet2->Initialize();
				pBullet2->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet2)->SetNormalAngle(92.f);

				CObj* pBullet3 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet3)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet3->Initialize();
				pBullet3->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet3)->SetNormalAngle(88.f);

				CObj* pBullet4 = new CPlayerBullet;
				dynamic_cast<CPlayerBullet*>(pBullet4)->SetBulletType(PLAYERBULLET_NORMAL);
				pBullet4->Initialize();
				pBullet4->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-5.f, 0.f, 0.f));
				dynamic_cast<CPlayerBullet*>(pBullet4)->SetNormalAngle(84.f);

				CObjMgr::GetInstance()->AddObject(pBullet, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet2, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet3, OBJ_PLAYERNORMALBULLET);
				CObjMgr::GetInstance()->AddObject(pBullet4, OBJ_PLAYERNORMALBULLET);
			}
		}

		if(m_tPlayerInfo.bIsSubWeapon)
		{
			m_dwSearchBulletCurTime = GetTickCount();
			if(m_dwSearchBulletOldTime + m_iSearchBulletDelay < m_dwSearchBulletCurTime)
			{
				m_dwSearchBulletOldTime = m_dwSearchBulletCurTime;

				CObjMgr::GetInstance()->AddObject(CreateSearchBullet( m_tInfo.vPos + D3DXVECTOR3(-20.f, 10.f, 0.f) ), OBJ_PLAYERSEARCHBULLET);
				CObjMgr::GetInstance()->AddObject(CreateSearchBullet( m_tInfo.vPos + D3DXVECTOR3(30.f, 10.f, 0.f) ), OBJ_PLAYERSEARCHBULLET);
			}
		}
	}

	// 폭탄발사
	if(CKeyMgr::GetInstance()->OnceKeyDown('X') && m_tPlayerInfo.iBomb > 0 && m_tPlayerInfo.bBombIsReady)
	{
		MinusBomb();
		m_tPlayerInfo.bBombIsReady = false;

		// 0. 어두워짐
		g_iRGB = 100;

		// 1. 일러스트 나오고
		CObj* pIllust = new CPlayerIllust;
		pIllust->Initialize();

		CObjMgr::GetInstance()->AddObject(pIllust, OBJ_EFFECT);

		// 2. 오로라 나오고
		CObj* pEffect = new CEffectPower;
		pEffect->SetPos((m_tInfo.vPos + D3DXVECTOR3(-5.f, 0.f, 0)) - (m_tInfo.vSize / 2.f) );
		pEffect->Initialize();

		CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

		// 3. 폭탄 나감 ( 4개 정도 시간간격 나눠서 )
		m_dwBombCountTime = GetTickCount();
		m_tPlayerInfo.bIsBomb = true;
	}
	if(m_tPlayerInfo.bIsBomb)
	{
		if(m_dwBombCountTime + 600 < GetTickCount())
		{
			m_dwBombCountTime = GetTickCount();

			CObj* pBullet = new CPlayerBullet;
			dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_BOMB);
			pBullet->Initialize();

			int iRnd = rand() % 2;

			if(iRnd == 1)
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(30.f, 20.f, 0.f));
			else
				pBullet->SetPos(m_tInfo.vPos + m_tInfo.vSize / 2 + D3DXVECTOR3(-40.f, 20.f, 0.f));

			CObjMgr::GetInstance()->AddObject(pBullet, OBJ_PLAYERBOMB);

			m_tPlayerInfo.iBombCount ++;
		}
	}

	if(m_tPlayerInfo.iBombCount >= 5)
	{
		g_iRGB = 255;
		m_tPlayerInfo.iBombCount = 0;
		m_tPlayerInfo.bBombIsReady = true;
		m_tPlayerInfo.bIsBomb = false;
	}
}

void CPlayer::FrameMove( void )
{
	if(m_eCurState != m_ePreState)
	{
		switch(m_eCurState)
		{
		case PLAYER_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFramespd = 100;
			break;

		case PLAYER_MOVE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFramespd = 50;
			break;
		}

		m_ePreState = m_eCurState;
	}

	m_dwCurFrameTime = GetTickCount();

	if(m_dwOldFrameTime + m_tFrame.dwFramespd < m_dwCurFrameTime)
	{
		m_dwOldFrameTime = m_dwCurFrameTime;

		++(m_tFrame.iFrameStart);
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd - 1)
	{
		if(m_eCurState == PLAYER_MOVE)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd - 1;
		else
			m_tFrame.iFrameStart = 0;
	}
}

CObj* CPlayer::CreateSearchBullet( D3DXVECTOR3 vPos )
{
	CObj* pBullet = new CPlayerBullet;
	dynamic_cast<CPlayerBullet*>(pBullet)->SetBulletType(PLAYERBULLET_SEARCH);
	pBullet->Initialize();

	if(m_tPlayerInfo.iPower >= 24)
	{
		dynamic_cast<CPlayerBullet*>(pBullet)->SetSpeed(20.f);
	}
	else if(m_tPlayerInfo.iPower >= 16)
	{
		dynamic_cast<CPlayerBullet*>(pBullet)->SetSpeed(15.f);
	}
	else if(m_tPlayerInfo.iPower <= 8)
	{
		dynamic_cast<CPlayerBullet*>(pBullet)->SetSpeed(10.f);
	}
	pBullet->SetPos(vPos);

	return pBullet;
}



CObj* CPlayer::CreateSubWeapon( void )
{
	CObj* pSubWeapon = new CSubWeapon;
	pSubWeapon->Initialize();
	pSubWeapon->SetPos(m_tInfo.vPos);
	dynamic_cast<CSubWeapon*>(pSubWeapon)->SetPlayer(this);

	return pSubWeapon;
}

void CPlayer::DeadEffect( void )
{
	//1. power 이펙트
	CObj* pEffect = new CEffectPower;
	pEffect->SetPos((m_tInfo.vPos + D3DXVECTOR3(-5.f, 0.f, 0)) - (m_tInfo.vSize / 2.f) );
	pEffect->Initialize();

	CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);

	//2. small 이펙트
	for(int i = 0; i < 8; ++i)
	{
		CObj* pEffect2 = new CSmallEffect;
		pEffect2->Initialize();
		pEffect2->SetPos(m_tInfo.vPos);
		dynamic_cast<CSmallEffect*>(pEffect2)->SetType(4);

		CObjMgr::GetInstance()->AddObject(pEffect2, OBJ_EFFECT);
	}

}

