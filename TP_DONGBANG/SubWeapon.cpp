#include "StdAfx.h"
#include "SubWeapon.h"

#include "PlayerBullet.h"

CSubWeapon::CSubWeapon(void)
{
}

CSubWeapon::~CSubWeapon(void)
{
	Release();
}

void CSubWeapon::Initialize( void )
{
	m_pPlayer = NULL;
	m_tInfo.vSize.x = 14.f;
	m_tInfo.vSize.y = 14.f;

	m_tInfo.eRenderType = RENDER_OBJ;

	m_dwNormalBulletOldTime = GetTickCount();
	m_dwNormalBulletCurTime = 0;
}

RETURN_TYPE CSubWeapon::Update( void )
{
	if(m_bDeadCheck)
		return RETURN_DEAD;

	if(m_eDir == PLAYERSUBWEPAON_LEFT)
		m_tInfo.vPos = m_pPlayer->GetInfo()->vPos + D3DXVECTOR3(-20.f, 10.f, 0.f);
	else if(m_eDir == PLAYERSUBWEPAON_RIGHT)
		m_tInfo.vPos = m_pPlayer->GetInfo()->vPos + D3DXVECTOR3(30.f, 10.f, 0.f);


	return RETURN_NULL;
}

void CSubWeapon::Render( HDC hDc )
{
	D3DXMATRIX matRotZ, matTrans;

	if(m_eDir == PLAYERSUBWEPAON_LEFT)
		m_fAngle = GetTickCount() * -0.004f;
	else if(m_eDir == PLAYERSUBWEPAON_RIGHT)
		m_fAngle = GetTickCount() * 0.004f;
	D3DXToRadian(m_fAngle);

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matRotZ * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(L"SubWeapon")->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSubWeapon::Release( void )
{
}