#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::~CItem(void)
{
	Release();
}

void CItem::Initialize( void )
{
	switch(m_eType)
	{
	case ITEM_BIGPOWER:
		m_tInfo.vSize.x = 16.f;
		m_tInfo.vSize.y = 16.f;
		break;

	case ITEM_LIFE:
		m_tInfo.vSize.x = 16.f;
		m_tInfo.vSize.y = 16.f;
		break;

	case ITEM_POWER:
		m_tInfo.vSize.x = 10.f;
		m_tInfo.vSize.y = 10.f;
		break;
	}
	m_fSpeed = 1.5f;
	m_bIsArrived = false;

	m_tInfo.eRenderType = RENDER_OBJ;
}

RETURN_TYPE CItem::Update( void )
{
	if(m_bDeadCheck)
		return RETURN_DEAD;

	if(m_tInfo.vPos.y > m_fTargetY && !m_bIsArrived)
	{
		m_fSpeed = 1.5;
		m_tInfo.vPos.y -= m_fSpeed;
	}
	else
		m_bIsArrived = true;
	
	if(m_bIsArrived)
	{
		m_fSpeed = 5.5f;
		m_tInfo.vPos.y += m_fSpeed;
	}

	if(m_tInfo.vPos.y > 440)
		return RETURN_DEAD;

	return RETURN_NULL;
}

void CItem::Render( HDC hDc )
{
	D3DXMATRIX matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	switch(m_eType)
	{
	case ITEM_BIGPOWER:
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"BigPower")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case ITEM_LIFE:
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Life")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;

	case ITEM_POWER:
		CDevice::GetInstance()->GetSprite()->Draw(
			CTextureMgr::GetInstance()->GetTexture(L"Power")->pTexture
			, NULL
			, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
			, NULL
			, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	
}

void CItem::Release( void )
{

}
