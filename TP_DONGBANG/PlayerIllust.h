#pragma once
#include "obj.h"

class CPlayerIllust :
	public CObj
{
private:
	float m_fscaleX;
	float m_fscaleY;

	bool m_bStart;

	int m_iAlpha;

public:
	CPlayerIllust(void);
	virtual ~CPlayerIllust(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
