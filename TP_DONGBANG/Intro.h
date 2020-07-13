#pragma once
#include "scene.h"

class CIntro :
	public CScene
{
private:
	HWND	m_hVideo;

public:
	CIntro(void);
	virtual ~CIntro(void);

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(HDC hDc);
	virtual void Release(void);
};
