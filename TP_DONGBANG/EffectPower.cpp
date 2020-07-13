#include "StdAfx.h"
#include "EffectPower.h"

CEffectPower::CEffectPower(void)
{
}

CEffectPower::~CEffectPower(void)
{
}

void CEffectPower::Initialize( void )
{
	m_tInfo.vSize.x = 63.f;
	m_tInfo.vSize.y = 64.f;

	m_fscaleX = 1.f;
	m_fscaleY = 1.f;
	m_iAlpha = 255;

	m_dwCurFrameTime = GetTickCount();
}

RETURN_TYPE CEffectPower::Update( void )
{
	if(m_iAlpha == 0)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CEffectPower::Render( HDC hDc )
{
	if(m_dwCurFrameTime + 30 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();

		m_fscaleX += 0.6f;
		m_fscaleY += 0.6f;

		m_iAlpha -= 20;

		if(m_iAlpha < 0)
			m_iAlpha = 0;

	}
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Orora")->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

}

void CEffectPower::Release( void )
{
}
