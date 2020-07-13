#pragma once

class CObj;

class CObjMgr	// 메디에이터 패턴(중재자 패턴)
{
	DECLARE_SINGLETON(CObjMgr)

private:
	OBJLIST m_ObjList[OBJ_END];
	vector<CObj*> m_vecRender[RENDER_END];

public:
	OBJLIST* GetObjList(OBJ_TYPE eID) { return &(m_ObjList[eID]); }

public:
	void AddObject(CObj* pObj, OBJ_TYPE eID);
	RETURN_TYPE UpdateObj(void);
	void RenderObj(HDC hDc);
	void ReleaseObj(void);
public:
	CObj* AimTarget(CObj* pObj, OBJ_TYPE eTargetID);

public:
	static bool CompareX(CObj* pSour, CObj* pDest);
	static bool CompareY(CObj* pSour, CObj* pDest);

private:
	CObjMgr(void);
	~CObjMgr(void);
};