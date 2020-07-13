#pragma once
#include "obj.h"

class CNomalMonster :
	public CObj
{
private:
	DWORD			m_dwCurPattonCount;
	int				m_iPattonCount;
	bool			m_bTurn;
	float			m_fTime;
	float			m_fAngle;
	eMONSTER_TYPE	m_eMonsterType;
	eMONSTER_PATTON m_eMonsterPatton;

public:
	void SetMonsterType(eMONSTER_TYPE _eType) { m_eMonsterType = _eType; }
	void SetMonsterPatton(eMONSTER_PATTON _ePatton) { m_eMonsterPatton = _ePatton; }
public:
	void Patton(void);
	void SetFrame(void);
public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

public:
	CNomalMonster(void);
	virtual ~CNomalMonster(void);
};
