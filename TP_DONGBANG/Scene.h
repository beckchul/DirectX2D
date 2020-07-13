#pragma once

class CScene
{
protected:
	SCENE_TYPE m_eSceneType;

public:
	SCENE_TYPE GetSceneType(void) { return m_eSceneType; }

public:
	CScene(void);
	virtual ~CScene(void);

public:
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(HDC hDc) = 0;
	virtual void Release(void) = 0;
};
