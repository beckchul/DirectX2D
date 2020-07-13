#pragma once
#include "scene.h"

class CStage :
	public CScene
{
private:
	DWORD	m_dwCount;
	int		m_iCount;
	int		m_iStartCount;

	bool	m_bCreateBoss;
	DWORD	m_dwStageCount;
	int		m_iStageCount;
	int		m_iAlph;
	int		m_iAlphCount;

	DWORD	m_dwScoreBounsOldTime;
	DWORD	m_dwScoreBounsCurTime;

public:
	void StagePatton(void);

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Render(HDC hDc);
	virtual void Release(void);

public:
	CStage(void);
	virtual ~CStage(void);
};
