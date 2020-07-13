#include "StdAfx.h"
#include "NomalMonsterBullet.h"

CNomalMonsterBullet::CNomalMonsterBullet(void)
{
}

CNomalMonsterBullet::~CNomalMonsterBullet(void)
{
	Release();
}

void CNomalMonsterBullet::Initialize( void )
{
	m_fAngle = 0.f;

	switch(m_eBulletType)
	{
	case BULLET_TYPE_GUIDED:
		m_fSpeed = 5.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE:
		m_fSpeed = 6.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE_TWO:
		m_fSpeed = 4.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE_ALL:
		m_fSpeed = 4.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE_ALL_TWO:
		m_fSpeed = 4.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE_FAST:
		m_fSpeed = 7.f;
		SettingAngle();
		break;
	case BULLET_TYPE_ANGLE_FAST_TWO:
		m_fSpeed = 7.f;
		SettingAngle();
		break;
	case BULLET_TYPE_HELL:
		m_fSpeed = 3.f;
		SettingAngle();
		break;
	case BULLET_TYPE_HELL_TWO:
		m_fSpeed = 3.f;
		SettingAngle();
		break;
	case BULLET_TYPE_HELL_THREE:
		m_fSpeed = 3.f;
		m_fAngle = 0.f;
		break;
	}

	switch(m_eBulletNumber)
	{
	case BULLET_NUMBER_TWO:
		m_tInfo.vSize = D3DXVECTOR3(16.f, 16.f, 0.f);
		break;
	case BULLET_NUMBER_THREE:
		m_tInfo.vSize = D3DXVECTOR3(8.f, 16.f, 0.f);
		break;
	case BULLET_NUMBER_FIVE:
		m_tInfo.vSize = D3DXVECTOR3(12.f, 12.f, 0.f);
		break;
	case BULLET_NUMBER_EIGHT:
		m_tInfo.vSize = D3DXVECTOR3(8.f, 8.f, 0.f);
		break;
	}

	switch(m_eBulletColor)
	{
	case BULLET_COLOR_BLUE:
		lstrcpy(m_Key, L"BulletBlue");
		break;
	case BULLET_COLOR_RED:
		lstrcpy(m_Key, L"BulletRed");
		break;
	case BULLET_COLOR_YELLOW:
		lstrcpy(m_Key, L"BulletYellow");
		break;
	case BULLET_COLOR_GREEN:
		lstrcpy(m_Key, L"BulletGreen");
		break;
	}

	m_bHell = false;
	m_iAlpa = 255;
	m_dwCurFrameTime = GetTickCount();
	m_dwHellFrameTime = GetTickCount();
	m_tInfo.eRenderType = RENDER_EFFECT;
}

RETURN_TYPE CNomalMonsterBullet::Update( void )
{
	if(m_bDeadCheck)
		return RETURN_DEAD;

	if(g_iRGB == 100)
		return RETURN_DEAD;

	if(m_tInfo.vPos.x < 20 
		|| m_tInfo.vPos.x > 425 
		|| m_tInfo.vPos.y < 0 
		|| m_tInfo.vPos.y > 480)
		return RETURN_DEAD;

	if(m_bHell == false && m_eBulletType == BULLET_TYPE_HELL_THREE
		&& m_dwHellFrameTime + 1000 < GetTickCount())
	{
		m_bHell = true;
		SettingAngle();
		m_fSpeed = 15.f;
	}

	if(m_bHell == false 
		&& (m_eBulletType == BULLET_TYPE_HELL || m_eBulletType == BULLET_TYPE_HELL_TWO)
		&& m_dwHellFrameTime + 2000 < GetTickCount())
	{
		

		if(m_eBulletType == BULLET_TYPE_HELL_TWO)
			m_fAngle += D3DXToRadian(90);
		else if(m_eBulletType == BULLET_TYPE_HELL)
			m_fAngle -= D3DXToRadian(90);
		m_bHell = true;
	}

	if(BULLET_TYPE_ANGLE == m_eBulletType
		|| m_eBulletType == BULLET_TYPE_ANGLE_TWO
		|| m_eBulletType == BULLET_TYPE_ANGLE_ALL
		|| m_eBulletType == BULLET_TYPE_ANGLE_ALL_TWO
		|| m_eBulletType == BULLET_TYPE_ANGLE_FAST
		|| m_eBulletType == BULLET_TYPE_ANGLE_FAST_TWO
		|| m_eBulletType == BULLET_TYPE_HELL
		|| m_eBulletType == BULLET_TYPE_HELL_TWO
		|| m_eBulletType == BULLET_TYPE_HELL_THREE)
	{
		m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
		m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;
	}
	else
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if((m_eBulletType == BULLET_TYPE_ANGLE || m_eBulletType == BULLET_TYPE_ANGLE_TWO || BULLET_TYPE_ANGLE_FAST_TWO)
		&& m_dwCurFrameTime + 100 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();
		--m_fSpeed;

		if(m_fSpeed < 2)
			m_fSpeed = 2;
	}

	if((m_eBulletType == BULLET_TYPE_ANGLE_ALL_TWO || m_eBulletType == BULLET_TYPE_ANGLE_FAST)
		&& m_dwCurFrameTime + 200 < GetTickCount())
	{
		m_dwCurFrameTime = GetTickCount();
		--m_fSpeed;

		if(m_fSpeed < 2)
			m_fSpeed = 2;
	}


	return RETURN_NULL;
}

void CNomalMonsterBullet::Render( HDC hDc )
{

	D3DXMATRIX matRotZ, matScale, matTrans;

	D3DXMatrixIdentity(&(m_tInfo.matWorld));
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, -m_fAngle + D3DXToRadian(90));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vSize.x / 2.f + m_tInfo.vPos.x, m_tInfo.vSize.y / 2.f + m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&(m_tInfo.matWorld));

	CDevice::GetInstance()->GetSprite()->Draw(
		CTextureMgr::GetInstance()->GetTexture(m_Key, m_Key, m_eBulletNumber)->pTexture
		, NULL
		, &D3DXVECTOR3(m_tInfo.vSize.x / 2.f, m_tInfo.vSize.y / 2.f, 0.f)
		, NULL
		, D3DCOLOR_ARGB(m_iAlpa, 255, 255, 255));
}

void CNomalMonsterBullet::Release( void )
{

}

void CNomalMonsterBullet::SettingAngle( void )
{
	m_tInfo.vDir = m_pPlayerInfo->vPos + m_pPlayerInfo->vSize / 2.f - m_tInfo.vPos;

	float fDist = sqrt( pow(m_tInfo.vDir.x, 2) +  pow(m_tInfo.vDir.y, 2));

	if(BULLET_TYPE_ANGLE == m_eBulletType
		|| m_eBulletType == BULLET_TYPE_ANGLE_TWO
		|| m_eBulletType == BULLET_TYPE_ANGLE_FAST
		|| m_eBulletType == BULLET_TYPE_HELL_THREE)
	{
		float fAngle = acos(m_tInfo.vDir.x / fDist);

		if(m_pPlayerInfo->vPos.y > m_tInfo.vPos.y)
		{
			fAngle *= -1;
		}

		if(BULLET_TYPE_ANGLE_FAST != m_eBulletType)
			fAngle += D3DXToRadian(m_iDirCount * 6);
		else
			fAngle += D3DXToRadian(m_iDirCount * 3);
		
		m_fAngle = fAngle;
	}
	else if(BULLET_TYPE_ANGLE_ALL == m_eBulletType
		|| BULLET_TYPE_ANGLE_ALL_TWO == m_eBulletType
		|| m_eBulletType == BULLET_TYPE_ANGLE_FAST_TWO
		|| m_eBulletType == BULLET_TYPE_HELL
		|| m_eBulletType == BULLET_TYPE_HELL_TWO)
	{
		if(m_eBulletType != BULLET_TYPE_ANGLE_FAST_TWO 
			&& m_eBulletType != BULLET_TYPE_HELL 
			&& m_eBulletType != BULLET_TYPE_HELL_TWO)
			m_fAngle += D3DXToRadian(m_iDirCount * 360 / 36);
		else
			m_fAngle += D3DXToRadian(m_iDirCount * 360 / 64);
	}
	else
	{
		m_tInfo.vDir /= fDist;
	}
}