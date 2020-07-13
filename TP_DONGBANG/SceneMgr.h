#pragma once

class CScene;

class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	CScene*	m_pScene;

public:
	CScene* GetScene(void) { return m_pScene; }

private:
	CSceneMgr(void);
	~CSceneMgr(void);

public:
	void SetScene(SCENE_TYPE eType);

public:
	void Update(void);
	void Render(HDC hDc);
	void Release(void);
};
