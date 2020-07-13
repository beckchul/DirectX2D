#pragma once
#include "obj.h"

class CItem :
	public CObj
{
private:
	ITEM_TYPE	m_eType;
	float		m_fTargetY;
	bool		m_bIsArrived;

public:
	ITEM_TYPE GetItemType(void) { return m_eType; }

public:
	void SetItemType(ITEM_TYPE eType) { m_eType = eType; }
	void SetTargetY(float fTargetY) { m_fTargetY = fTargetY; }

public:
	CItem(void);
	virtual ~CItem(void);

public:
	virtual void Initialize( void );
	virtual RETURN_TYPE Update( void );
	virtual void Render( HDC hDc );
	virtual void Release( void );
};
