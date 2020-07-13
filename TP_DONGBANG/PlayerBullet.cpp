#include "StdAfx.h"
#include "PlayerBullet.h"

CPlayerBullet::CPlayerBullet(void)
{
}

CPlayerBullet::~CPlayerBullet(void)
{
	Release();
}

void CPlayerBullet::Initialize( void )
{
	if(m_eType == PLAYERBULLET_NORMAL)
	{
		m_tInfo.vSize.x = 12.f;
		m_tInfo.vSize.y = 12.f;

		m_fSpeed = 20.f;
		m_fNormalAngle = 90.f;
	}
	else if(m_eType == PLAYERBULLET_SEARCH)
	{	
		m_tInfo.vSize.x = 12.f;
		m_tInfo.vSize.y = 12.f;

		m_fSpeed = 10.f;
		m_fAngle = 0.f;
	}
	else if(m_eType == PLAYERBULLET_BOMB)
	{
		m_tInfo.vSize.x = 30.f;
		m_tInfo.vSize.y = 30.f;

		m_fSpeed = 10.f;
		m_fAngle = 0.f;

		m_OriginalfScaleX = 0.f;
		m_OriginalfScaleY = 0.f;

		m_fscaleX = 0.5f;
		m_fscaleY = 0.5f;

		m_iAlpha = 255;
		m_iOriginalAlpha = 255;
	}
	
	m_iHp = 4;
	m_fTAngle = 0;
	m_dwTime = 0;
	m_fBombAngle = 0.f;

	m_tInfo.eRenderType = RENDER_OBJ;
}

RETURN_TYPE CPlayerBullet::Update( void )
{
	/*제한 범위
	좌 : 10
	우 : 415
	상 : 10
	하 : 440*/

	if(m_bDeadCheck)
		return RETURN_DEAD;

	if(m_iHp <= 0)
		return RETURN_DEAD;

	if(m_eType == PLAYERBULLET_NORMAL)
	{
		m_tInfo.vPos.x += cosf(D3DXToRadian(m_fNormalAngle)) * m_fSpeed;
		m_tInfo.vPos.y += -sinf(D3DXToRadian(m_fNormalAngle)) * m_fSpeed;
	}
	else if(m_eType == PLAYERBULLET_SEARCH )
	{
		CObj* pTarget = CObjMgr::GetInstance()->AimTarget(this, OBJ_MONSTER);

		if(NULL != pTarget)
		{
			float fWidth =  fabs(pTarget->GetInfo()->vPos.x - m_tInfo.vPos.x);
			float fHeight = fabs(pTarget->GetInfo()->vPos.y - m_tInfo.vPos.y);

			float fDistance = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

			//float fAngle = acosf(fDistance);
			float fAngle = atan2f(fHeight, fWidth);

			if(pTarget->GetInfo()->vPos.x > m_tInfo.vPos.x)
			{
				m_tInfo.vPos.x += cosf(fAngle) * m_fSpeed;
				m_tInfo.vPos.y += -sinf(fAngle) * m_fSpeed;
			}
			else
			{
				m_tInfo.vPos.x -= cosf(fAngle) * m_fSpeed;
				m_tInfo.vPos.y += -sinf(fAngle) * m_fSpeed;
			}
		}
		else
		{
			m_tInfo.vPos.y -= m_fSpeed;
		}
	}
	else if(m_eType == PLAYERBULLET_BOMB)
	{
		CObj* pTarget = CObjMgr::GetInstance()->AimTarget(this, OBJ_MONSTER);

		float fTempAngle = 90.f;

		if(NULL != pTarget)
		{
			m_fSpeed += 0.3f;
			if(m_fSpeed >= 20)
				m_fSpeed = 20;

			float fWidth =  fabs(pTarget->GetInfo()->vPos.x - m_tInfo.vPos.x);
			float fHeight = fabs(pTarget->GetInfo()->vPos.y - m_tInfo.vPos.y);

			float fDistance = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

			m_fBombAngle = atan2f(fHeight, fWidth);
			fTempAngle = D3DXToDegree(m_fBombAngle);

			if(pTarget->GetInfo()->vPos.x > m_tInfo.vPos.x)
			{
				m_tInfo.vPos.x += cosf(m_fBombAngle) * m_fSpeed;
				m_tInfo.vPos.y += -sinf(m_fBombAngle) * m_fSpeed;
			}
			else
			{
				m_tInfo.vPos.x -= cosf(m_fBombAngle) * m_fSpeed;
				m_tInfo.vPos.y += -sinf(m_fBombAngle) * m_fSpeed;
			}
		}
		else
		{

			m_tInfo.vPos.x += cosf(D3DXToRadian(fTempAngle)) * m_fSpeed;
			m_tInfo.vPos.y += -sinf(D3DXToRadian(fTempAngle)) * m_fSpeed;
		}
	}
	

	if(m_tInfo.vPos.x <= 10 || m_tInfo.vPos.x >= 415
		|| m_tInfo.vPos.y <= 10 || m_tInfo.vPos.y >= 440)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CPlayerBullet::Render( HDC hDc )
{

	if(m_eType == PLAYERBULLET_NORMAL)
	{
		D3DXMATRIX matRotZ, matTrans;

		m_fAngle = GetTickCount() * 0.008f;
		D3DXToRadian(m_fAngle);

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matRotZ * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Bullet0")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(100, 255, 255, 255));
	}
	else if(m_eType == PLAYERBULLET_SEARCH)
	{	
		D3DXMATRIX matRotZ, matTrans;

		m_fAngle = GetTickCount() * 0.008f;
		D3DXToRadian(m_fAngle);

		D3DXMatrixIdentity(&(m_tInfo.matWorld));
		D3DXMatrixRotationZ(&matRotZ, m_fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

		m_tInfo.matWorld = matRotZ * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Bullet1")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(100, 255, 255, 255));
	}
	else if(m_eType == PLAYERBULLET_BOMB)
	{
		if(m_OriginalfScaleX >= 1.0f)
		{
			D3DXMATRIX matScale, matTrans;

			D3DXMatrixIdentity(&(m_tInfo.matWorld));
			D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);
			D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);

			m_tInfo.matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			m_fscaleX += 0.1f;
			m_fscaleY += 0.1f;

			m_iAlpha -= 10;

			if(m_iAlpha < 50)
				m_iAlpha = 50;

			if(m_fscaleX > 4.f)
			{
				m_fscaleX = 4.f;
				m_fscaleY = 4.f;
			}

			CDevice::GetInstance()->GetSprite()->Draw(
				CTextureMgr::GetInstance()->GetTexture(L"Bomb1")->pTexture
				, NULL
				, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f + 5.f, m_tInfo.vSize.y / 2.f, 0.f)
				, NULL
				, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

			CDevice::GetInstance()->GetSprite()->Draw(
				CTextureMgr::GetInstance()->GetTexture(L"Bomb2")->pTexture
				, NULL
				, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f - 5.f, m_tInfo.vSize.y / 2.f, 0.f)
				, NULL
				, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

			CDevice::GetInstance()->GetSprite()->Draw(
				CTextureMgr::GetInstance()->GetTexture(L"Bomb3")->pTexture
				, NULL
				, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f - 12.f, 0.f)
				, NULL
				, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
		}
		else
		{
			D3DXMATRIX matScale, matTrans;

			D3DXMatrixIdentity(&(m_tInfo.matWorld));
			D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);
			D3DXMatrixScaling(&matScale, m_OriginalfScaleX, m_OriginalfScaleY, 0.f);

			m_tInfo.matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			m_OriginalfScaleX += 0.1f;
			m_OriginalfScaleY += 0.1f;

			m_iOriginalAlpha -= 15;

			if(m_iOriginalAlpha < 0)
				m_iOriginalAlpha = 0;

			CDevice::GetInstance()->GetSprite()->Draw(
				CTextureMgr::GetInstance()->GetTexture(L"Bomb0")->pTexture
				, NULL
				, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
				, NULL
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPlayerBullet::Release( void )
{

}
