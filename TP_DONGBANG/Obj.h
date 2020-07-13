#pragma once

class CObj
{
protected:
	INFO	m_tInfo;
	FRAME	m_tFrame;
	int		m_iHp;
	bool	m_bDeadCheck;
	float	m_fSpeed;
	float	m_fAngle;

	DWORD	m_dwOldFrameTime;
	DWORD	m_dwCurFrameTime;
	DWORD	m_dwHellFrameTime;
	bool	m_bHell;

public:
	void SetHp(int _Hp)	{ m_iHp -= _Hp; }
public:
	INFO* GetInfo(void) { return &m_tInfo; }

public:
	bool GetDeadState(void) { return m_bDeadCheck; }
	void IsDead(void) { m_bDeadCheck = true; }
	void SetPos(D3DXVECTOR3 _vPos) { m_tInfo.vPos.x = _vPos.x, m_tInfo.vPos.y = _vPos.y; }

public:
	virtual void Initialize(void)	= 0;
	virtual RETURN_TYPE Update(void)= 0;
	virtual void Render(HDC hDc)	= 0;
	virtual void Release(void)		= 0;

public:
	CObj(void);
	~CObj(void);
};
