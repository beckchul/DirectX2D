#pragma once
#include "obj.h"

class CEffectPower2 :
	public CObj
{
private:
	float m_fscaleX;
	float m_fscaleY;

	int m_iAlpha;
public:
	CEffectPower2(void);
	virtual ~CEffectPower2(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
