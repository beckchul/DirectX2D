#pragma once

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	bool	m_bKeyDown[KEYMAX];	// Ű�� ���ȴ��� üũ�� �迭
	bool	m_bKeyUp[KEYMAX];	// Ű�� �������� üũ�� �迭

private:
	CKeyMgr(void);
	~CKeyMgr(void);

public:
	bool StayKeyDown(INT nKey); // Ű�� ������ �ִ��� üũ
	bool OnceKeyDown(INT nKey); // Ű�� �ѹ� ���ȴ��� üũ
	bool OnceKeyUp(INT nKey);	// Ű�� �ѹ� ���ȴ� �������� üũ
	bool IsToggleKey(INT nKey);	// �ѹ� ���������� on off�� �ٲٵ���
};