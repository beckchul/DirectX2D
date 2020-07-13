#pragma once
#include "obj.h"

class CEffect :
	public CObj
{
private:
	eEFFECT_TYPE	m_eEffectType;
	TCHAR			m_Key[MIN_STR];
	eBULLET_NUMBER	m_eBulletNumber;
	float			m_fSize;
	int				m_iAlpa;
	int				m_iCount;

public:
	void SetEffectType(eEFFECT_TYPE _eType) { m_eEffectType = _eType; }
public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
public:
	CEffect(void);
	virtual ~CEffect(void);
};
