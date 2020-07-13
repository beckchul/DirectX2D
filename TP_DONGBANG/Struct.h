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

	int iFrameStart;	// 스프라이트 스프라이트 번호
	int iFrameEnd;		// 스프라이트 마지막 스프라이트 번호

	DWORD dwFramespd;	// 애니메이션 재생 속도.
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
	LPDIRECT3DTEXTURE9	pTexture;		//이미지 한장을 저장.
	D3DXIMAGE_INFO		ImageInfo;	//이미지 정보를 저장.
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