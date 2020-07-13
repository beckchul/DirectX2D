#pragma once
#include "obj.h"

class CBossMonster :
	public CObj
{
private:
	DWORD			m_dwCurPattonCount;
	bool			m_bBossOn;
	int				m_iPattonCount;
	int				m_iAddCount;
	float			m_fLookLeft;
	bool			m_bTurn;
	float			m_fTime;
	DWORD			m_dwState;
	DWORD			m_dwPreState;
	eMONSTER_TYPE	m_eMonsterType;
	eMONSTER_PATTON m_eMonsterPatton;

	bool			m_bBossBoom;
public:
	void SetMonsterType(eMONSTER_TYPE _eType) { m_eMonsterType = _eType; }
	void SetMonsterPatton(eMONSTER_PATTON _ePatton) { m_eMonsterPatton = _ePatton; }

public:
	bool GetBossBoom(void) { return m_bBossBoom; }
public:
	void Patton(void);
	void SetFrame(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );

public:
	CBossMonster(void);
	virtual ~CBossMonster(void);
};
