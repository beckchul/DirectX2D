#include "StdAfx.h"
#include "CollisionMgr.h"

#include "Obj.h"
#include "NomalMonster.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

bool CCollisionMgr::CollisionPointInRect( OBJLIST* pDstList, OBJLIST* pSrcList )
{
	OBJITER dstIter_begin = pDstList->begin();
	OBJITER dstIter_end = pDstList->end();

	for(; dstIter_begin != dstIter_end; ++dstIter_begin)
	{
		OBJITER srcIter_begin = pSrcList->begin();
		OBJITER srcIter_end = pSrcList->end();

		for(; srcIter_begin != srcIter_end; ++srcIter_begin)
		{
			if((*srcIter_begin)->GetDeadState() || (*dstIter_begin)->GetDeadState())
				continue;

			INFO* dstInfo = (*dstIter_begin)->GetInfo();

			float dstfX = dstInfo->vPos.x + dstInfo->vSize.x / 2 - 5.f;
			float dstfY = dstInfo->vPos.y + dstInfo->vSize.y / 2;

			float srcLeft = (*srcIter_begin)->GetInfo()->vPos.x - (*srcIter_begin)->GetInfo()->vSize.x / 1.5f;
			float srcTop = (*srcIter_begin)->GetInfo()->vPos.y - (*srcIter_begin)->GetInfo()->vSize.y / 1.5f;
			float srcRight = (*srcIter_begin)->GetInfo()->vPos.x + (*srcIter_begin)->GetInfo()->vSize.x / 1.5f;
			float srcBottom = (*srcIter_begin)->GetInfo()->vPos.y + (*srcIter_begin)->GetInfo()->vSize.y / 1.5f;

			if(dstfX >= srcLeft && dstfX <= srcRight
				&& dstfY >= srcTop && dstfY <= srcBottom)
			{
				// Ãæµ¹
				g_vCollision = (*srcIter_begin)->GetInfo()->vPos;

				(*dstIter_begin)->SetHp(40); // ¸ó½ºÅÍ
				(*srcIter_begin)->SetHp(1); // ÆøÅº
				//(*dstIter_begin)->IsDead(); 
				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::CollisionRect( OBJLIST* pDstList, OBJLIST* pSrcList )
{
	OBJITER dstIter_begin = pDstList->begin();
	OBJITER dstIter_end = pDstList->end();

	for(; dstIter_begin != dstIter_end; ++dstIter_begin)
	{
		OBJITER srcIter_begin = pSrcList->begin();
		OBJITER srcIter_end = pSrcList->end();

		for(; srcIter_begin != srcIter_end; ++srcIter_begin)
		{
			if(true == (*srcIter_begin)->GetDeadState())
				continue;

			INFO* dstInfo = (*dstIter_begin)->GetInfo();
			INFO* srcInfo = (*srcIter_begin)->GetInfo();

			float dstfX = dstInfo->vPos.x + dstInfo->vSize.x / 2 - 5.f;
			float dstfY = dstInfo->vPos.y + dstInfo->vSize.y / 2;
			float dstfCX = dstInfo->vSize.x;
			float dstfCY = dstInfo->vSize.y;

			float srcfX = srcInfo->vPos.x + srcInfo->vSize.x / 2;
			float srcfY = srcInfo->vPos.y + srcInfo->vSize.y / 2;
			float srcfCX = srcInfo->vSize.x;
			float srcfCY = srcInfo->vSize.y;

			
			float fWidth = (srcfCX/2) + (dstfCX/2);
			float fHeight = (srcfCY/2) + (srcfCY/2);

			float fDistanceX = fabs(dstfX - srcfX);
			float fDistanceY = fabs(dstfY - srcfY);

			if(fDistanceX < fWidth && fDistanceY < fHeight)
			{
				// Ãæµ¹
				g_vCollision = (*srcIter_begin)->GetInfo()->vPos;
				g_pObjCollision = (*srcIter_begin);

				(*dstIter_begin)->SetHp(1);
				CSoundMgr::GetInstance()->PlaySound(L"graze.wav", CHANNEL_EFF, 1.0f);
				(*srcIter_begin)->IsDead();
				return true;
			}
		}
	}
	return false;
}
