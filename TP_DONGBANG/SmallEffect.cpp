#include "StdAfx.h"
#include "SmallEffect.h"

CSmallEffect::CSmallEffect(void)
{
}

CSmallEffect::~CSmallEffect(void)
{
}

void CSmallEffect::Initialize( void )
{
	m_iType = 0;

	m_tInfo.vSize.x = 14.f;
	m_tInfo.vSize.y = 13.f;

	m_fSpeed = float(rand() % 5) + 5;

	if(rand() % 3 == 1)
	{
		m_fscaleX = 3.f;
		m_fscaleY = 3.f;
		m_fMinusScale = 0.15f;
	}
	else
	{
		m_fscaleX = 1.f;
		m_fscaleY = 1.f;
		m_fMinusScale = 0.05f;
	}
	m_iAlpha = 100;
	m_fAngle = float(rand() % 360);

	m_dwCurFrameTime = GetTickCount();
}

RETURN_TYPE CSmallEffect::Update( void )
{
	if(m_fscaleX <= 0 || m_fscaleY <= 0)
		return RETURN_DEAD;

	m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y += -sinf(m_fAngle) * m_fSpeed;

	return RETURN_NULL;
}

void CSmallEffect::Render( HDC hDc )
{
	if(m_dwCurFrameTime + 30 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();

		m_fscaleX -= m_fMinusScale;
		m_fscaleY -= m_fMinusScale;

		/*m_iAlpha -= 10;

		if(m_iAlpha < 0)
			m_iAlpha = 0;*/

	}
	D3DXMATRIX matRotZ, matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	D3DXMatrixScaling(&matScale, m_fscaleX, m_fscaleY, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matScale *  matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	if(m_iType == 1)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Effect1")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
	}
	else if(m_iType == 2)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Effect2")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
	}
	else if(m_iType == 3)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Effect3")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(200, 255, 255, 255));
	}
	else if(m_iType == 4)
	{
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Effect4")->pTexture
			, NULL
			, &D3DXVECTOR3(SMALL_EFFECT_BOMB_4_CX / 2, SMALL_EFFECT_BOMB_4_CY / 2, 0.f)
			, NULL
			, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
	}
	
}

void CSmallEffect::Release( void )
{
}
