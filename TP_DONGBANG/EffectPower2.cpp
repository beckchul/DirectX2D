#include "StdAfx.h"
#include "EffectPower2.h"

CEffectPower2::CEffectPower2(void)
{
}

CEffectPower2::~CEffectPower2(void)
{
}

void CEffectPower2::Initialize( void )
{
	m_tInfo.vSize.x = 30.f;
	m_tInfo.vSize.y = 30.f;

	m_fscaleX = 2.f;
	m_fscaleY = 2.f;
	m_iAlpha = 255;
}

RETURN_TYPE CEffectPower2::Update( void )
{
	if(m_iAlpha <= 0)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CEffectPower2::Render( HDC hDc )
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Orora2")->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	m_fscaleX += 1.4f;
	m_fscaleY += 1.4f;

	m_iAlpha -= 20;

	if(m_iAlpha < 0)
		m_iAlpha = 0;
}

void CEffectPower2::Release( void )
{
}
