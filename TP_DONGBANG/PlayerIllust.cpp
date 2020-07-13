#include "StdAfx.h"
#include "PlayerIllust.h"

CPlayerIllust::CPlayerIllust(void)
{
}

CPlayerIllust::~CPlayerIllust(void)
{
}

void CPlayerIllust::Initialize( void )
{
	m_tInfo.vPos.x = -100.f;
	m_tInfo.vPos.y = 185.f;

	m_tInfo.vSize.x = 128.f;
	m_tInfo.vSize.y = 256.f;

	m_fscaleX = 1.f;
	m_fscaleY = 1.f;
	m_iAlpha = 255;

	m_fSpeed = 15.f;

	m_bStart = false;

	m_dwCurFrameTime = GetTickCount();

	m_tInfo.eRenderType = RENDER_EFFECT;
}

RETURN_TYPE CPlayerIllust::Update( void )
{
	if(m_iAlpha <= 0)
		return RETURN_DEAD;

	// 타겟위치로 이동...
	if(m_tInfo.vPos.x <= 40)
	{
		m_tInfo.vPos.x += m_fSpeed;
	}
	else
	{
		if(m_dwCurFrameTime + 1500 < GetTickCount())
			m_bStart = true;

		if(m_bStart)
		{
			m_fscaleX += 0.1f;
			m_fscaleY += 0.1f;

			m_iAlpha -= 10;

			if(m_iAlpha < 0)
				m_iAlpha = 0;
		}
	}

	return RETURN_NULL;
}

void CPlayerIllust::Render( HDC hDc )
{
	

	D3DXMATRIX matRotZ, matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"PlayerIllust")->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
}

void CPlayerIllust::Release( void )
{
}
