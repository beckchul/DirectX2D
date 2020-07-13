#pragma once
#include "obj.h"

class CPlayerBullet :
	public CObj
{
private:
	PLAYERBULLET_TYPE	m_eType;
	float				m_fNormalAngle;

	float m_OriginalfScaleX;
	float m_OriginalfScaleY;

	int m_iOriginalAlpha;

	float m_dwTime;
	float m_fBombAngle;

	float m_fscaleX;
	float m_fscaleY;

	int m_iAlpha;

	float m_fTAngle;

public:
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

public:
	void SetNormalAngle(float fAngle) { m_fNormalAngle = fAngle; }
public:
	void SetBulletType(PLAYERBULLET_TYPE eType) { m_eType = eType; }

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

public:
	CPlayerBullet(void);
	virtual ~CPlayerBullet(void);
};
