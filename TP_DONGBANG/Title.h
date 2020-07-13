#pragma once
#include "scene.h"

class CTitle :
	public CScene
{
private:
	int m_iStartFrameX;
	int m_iQuitFrameX;
public:
	CTitle(void);
	virtual ~CTitle(void);

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(HDC hDc);
	virtual void Release(void);
};
