#pragma once
#include "obj.h"

#include "Player.h"

class CSubWeapon :
	public CObj
{
private:
	CObj*					m_pPlayer;
	PLAYERSUBWEPAON_DIR		m_eDir;

	DWORD					m_dwNormalBulletCurTime;
	DWORD					m_dwNormalBulletOldTime;

public:
	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	void SetDir(PLAYERSUBWEPAON_DIR eDir) { m_eDir = eDir; }

public:
	CSubWeapon(void);
	virtual ~CSubWeapon(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
