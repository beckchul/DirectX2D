#pragma once

typedef struct tagInfo 
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;

	D3DXMATRIX matWorld;

	RENDER_TYPE eRenderType;

}INFO, *PINFO, *pINFO;


typedef struct tagFrame
{
	tagFrame(void) {}

	tagFrame(int _iFrameStart, int _iFrameEnd, DWORD _dwFramespd)
		: iFrameStart(_iFrameStart), iFrameEnd(_iFrameEnd), dwFramespd(_dwFramespd) {}

	int iFrameStart;	// ��������Ʈ ��������Ʈ ��ȣ
	int iFrameEnd;		// ��������Ʈ ������ ��������Ʈ ��ȣ

	DWORD dwFramespd;	// �ִϸ��̼� ��� �ӵ�.
} FRAME, *PFRAME, *pFRAME;

typedef struct tagSringCmp
{
	const TCHAR* m_pString;

	template<class T>
	bool operator () (T data)
	{
		return !lstrcmp(data.first, m_pString);
	}

	tagSringCmp(const TCHAR* pKey)
		:m_pString(pKey){}

}STRING_CMP;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9	pTexture;		//�̹��� ������ ����.
	D3DXIMAGE_INFO		ImageInfo;	//�̹��� ������ ����.
}TEX_INFO;


typedef struct tagTile 
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;

	BYTE byOption;
	BYTE byDrawID;

}TILE;

typedef struct tagPlayerInfo
{
	int  iScore;
	int  iLife;
	int  iBomb;
	int  iPower;
	int  iBulletCount;
	int  iBombCount;
	bool bIsSubWeapon;
	bool bIsBomb;
	bool bPower;
	bool bBombIsReady;
}PlayerInfo;