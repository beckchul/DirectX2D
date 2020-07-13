#pragma once
#include "obj.h"

class CNomalMonsterBullet :
	public CObj
{
private:
	int				m_iAlpa;
	int				m_iDirCount;
	float			m_fAngle;
	TCHAR			m_Key[MIN_STR];
	eBULLET_TYPE	m_eBulletType;
	eBULLET_COLOR	m_eBulletColor;
	eBULLET_NUMBER	m_eBulletNumber;
	INFO*			m_pPlayerInfo;
public:
	void SetBulletNumber(eBULLET_NUMBER _eNumber) { m_eBulletNumber = _eNumber; }
	void SetBulletColor(eBULLET_COLOR _eColor) { m_eBulletColor = _eColor; }
	void SetBulletType(eBULLET_TYPE _eType) { m_eBulletType = _eType; }
	void SetPlayerInfo(INFO* _pInfo) { m_pPlayerInfo = _pInfo; }
	void SetDirCount(int _iCount) { m_iDirCount = _iCount; }
	void SetAngle(float _fAngle) { m_fAngle += D3DXToRadian(_fAngle); }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
public:
	void SettingAngle(void);
public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

public:
	CNomalMonsterBullet(void);
	virtual ~CNomalMonsterBullet(void);
};
