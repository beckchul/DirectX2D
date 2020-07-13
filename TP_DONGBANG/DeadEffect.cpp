#include "StdAfx.h"
#include "DeadEffect.h"

CDeadEffect::CDeadEffect(void)
{
}

CDeadEffect::~CDeadEffect(void)
{
}

void CDeadEffect::Initialize( void )
{
	m_tInfo.vSize.x = 30.f;
	m_tInfo.vSize.y = 30.f;
	
	m_fscaleX = 0.f;
	m_fscaleY = 0.f;
	m_iAlpha = 200;
	m_fAngle = 0.f;

	m_dwCurFrameTime = GetTickCount();
}	

RETURN_TYPE CDeadEffect::Update( void )
{
	if(m_iAlpha <= 0)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CDeadEffect::Render( HDC hDc )
{
	if(m_dwCurFrameTime + 30 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();

		m_fscaleX += 0.4f;
		m_fscaleY += 0.4f;

		m_iAlpha -= 15;

		m_fAngle += 25.f;

		if(m_fscaleX > 3.0f)
		{
			m_fscaleX = 3.0f;
			m_fscaleY = 3.0f;
		}

		if(m_iAlpha < 0)
			m_iAlpha = 0;
	}

	D3DXMATRIX matRotZ, matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"Effect0")->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));


}

void CDeadEffect::Release( void )
{
}
