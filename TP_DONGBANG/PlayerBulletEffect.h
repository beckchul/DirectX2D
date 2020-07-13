#pragma once
#include "obj.h"

class CPlayerBulletEffect :
	public CObj
{
private:
	PLAYERBULLETEFF_TYPE m_eType;
	float	m_fTargetY;
	

public:
	void SetBulletEffType(PLAYERBULLETEFF_TYPE eType) { m_eType = eType; }

public:
	void SetTargetY(float fTargetY) { m_fTargetY = fTargetY; }

public:
	CPlayerBulletEffect(void);
	virtual ~CPlayerBulletEffect(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

};
