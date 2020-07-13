#include "StdAfx.h"
#include "PlayerBulletEffect.h"

CPlayerBulletEffect::CPlayerBulletEffect(void)
{
}

CPlayerBulletEffect::~CPlayerBulletEffect(void)
{
}

void CPlayerBulletEffect::Initialize( void )
{
	m_tInfo.vSize.x = 30.f;
	m_tInfo.vSize.y = 30.f;

	m_fSpeed = 4.f;

	m_eType = PLAYERBULLETEFF_RED;

	m_dwCurFrameTime = GetTickCount();
}

RETURN_TYPE CPlayerBulletEffect::Update( void )
{
	if(m_dwCurFrameTime + 30 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();
		m_fSpeed -= 1.5;

		if(m_fSpeed < 1.5f)
			m_fSpeed = 1.5f;
	}

	if(m_tInfo.vPos.y > m_fTargetY)
	{
		m_tInfo.vPos.y -= m_fSpeed;
	}
	else
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CPlayerBulletEffect::Render( HDC hDc )
{
	D3DXMATRIX matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	if(m_eType == PLAYERBULLETEFF_RED)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"RedEffect")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(50, 255, 255, 255));
	}
	else if(m_eType == PLAYERBULLETEFF_BLUE)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"BlueEffect")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(50, 255, 255, 255));
	}
	
}

void CPlayerBulletEffect::Release( void )
{
}
