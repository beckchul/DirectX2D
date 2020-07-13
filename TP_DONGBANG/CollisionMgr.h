#pragma once

class CCollisionMgr
{
public:
	CCollisionMgr(void);
	~CCollisionMgr(void);

public:
	static bool CollisionPointInRect(OBJLIST* pDstList, OBJLIST* pSrcList);
	static bool CollisionRect(OBJLIST* pDstList, OBJLIST* pSrcList);
};
