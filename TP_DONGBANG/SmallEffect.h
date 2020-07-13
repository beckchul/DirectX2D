#pragma once
#include "obj.h"

class CSmallEffect :
	public CObj
{
private:
	float m_fscaleX;
	float m_fscaleY;

	float m_fMinusScale;

	int m_iAlpha;

	int m_iType;

public:
	void SetType(int iType) { m_iType = iType; }

public:
	CSmallEffect(void);
	virtual ~CSmallEffect(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
