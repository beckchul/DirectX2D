#pragma once
#include "obj.h"

class CEffectPower :
	public CObj
{
private:
	float m_fscaleX;
	float m_fscaleY;

	int m_iAlpha;

public:
	CEffectPower(void);
	virtual ~CEffectPower(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
