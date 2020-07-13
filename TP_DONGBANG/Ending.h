#pragma once
#include "scene.h"

class CEnding :
	public CScene
{
public:
	CEnding(void);
	~CEnding(void);

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(HDC hDc);
	virtual void Release(void);

};
