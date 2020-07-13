#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
private:
	PLAYERSTATE m_eCurState;
	PLAYERSTATE m_ePreState;

	PLAYERDIR	m_eDir;

	PlayerInfo  m_tPlayerInfo;

	int			m_iSearchBulletDelay;

	CObj*		m_pSubWeapon1;
	CObj*		m_pSubWeapon2;

	DWORD		m_dwNormalBulletOldTime;
	DWORD		m_dwNormalBulletCurTime;

	DWORD		m_dwSearchBulletOldTime;
	DWORD		m_dwSearchBulletCurTime;

	DWORD		m_dwBombCountTime;

	DWORD		m_dwRevivalTime;

	DWORD		m_dwBlendingTime;

	bool		m_bBlend;
	int			m_iRGB;
	bool		m_bARGB;

	DWORD		m_dwAlphaOld;
	DWORD		m_dwAlphaCur;

	float		m_fScaleX;
	float		m_fScaleY;

public:
	PlayerInfo* GetPlayerInfo(void) { return &m_tPlayerInfo; }

public:
	void MinusLife(void) 
	{ 
		// 0. ¸ñ¼û ÁÙÀÌ°í
		if(m_tPlayerInfo.iLife > 0)
			m_tPlayerInfo.iLife --;
	}

public:
	void MinusBomb(void)
	{
		if( m_tPlayerInfo.iBomb > 0 )
			m_tPlayerInfo.iBomb --;
	}

public:
	void PlusScore(int iScore)
	{
		m_tPlayerInfo.iScore += iScore;
	}

public:
	void SetbPower(bool bPower) { m_tPlayerInfo.bPower = bPower; }
	bool GetbPower(void) { return m_tPlayerInfo.bPower; }

public:
	void DeadEffect(void);

public:
	void RevivalTimeStart(void) { m_dwRevivalTime = GetTickCount(); }

public:
	void SetPowerCount(int iCount) 
	{ 
		if(m_tPlayerInfo.iPower < 99)
			m_tPlayerInfo.iPower += iCount; 
		else
			m_tPlayerInfo.iPower = 99;
	}

private:
	void FrameMove(void);
	void KeyInput(void);

	CObj* CreateSearchBullet( D3DXVECTOR3 vPos );
	CObj* CreateSubWeapon(void);
	

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
