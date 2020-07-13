#pragma once
#include "scene.h"

class CSelect :
	public CScene
{
private:
	int	m_iFrameX;

public:
	CSelect(void);
	~CSelect(void);

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(HDC hDc);
	virtual void Release(void);
};
