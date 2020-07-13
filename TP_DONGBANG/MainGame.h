#pragma once

class CMainGame
{
private:
	HDC m_hDc;

public:
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
