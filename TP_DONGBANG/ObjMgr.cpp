#include "StdAfx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	ReleaseObj();
}

void CObjMgr::ReleaseObj( void )
{
	for(int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::AddObject( CObj* pObj, OBJ_TYPE eID )
{
	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::RenderObj( HDC hDc )
{
	OBJITER	iter_begin;
	OBJITER iter_end;

	for(int i = 0; i < OBJ_END; ++i)
	{
		iter_begin = m_ObjList[i].begin();
		iter_end = m_ObjList[i].end();

		for( ; iter_begin != iter_end; ++iter_begin)
		{
			// 리스트를 순회하면서 m_vecRender에 우선 넣고 출력한다.
			if(RENDER_END == (*iter_begin)->GetInfo()->eRenderType)
			{
				(*iter_begin)->Render(hDc);
				continue;
			}

			m_vecRender[(*iter_begin)->GetInfo()->eRenderType].push_back(*iter_begin);
		}	
	}

	sort(m_vecRender[RENDER_OBJ].begin(), m_vecRender[RENDER_OBJ].end(), CObjMgr::CompareX);

	for(int i = 0; i < RENDER_END; ++i)
	{
		for(size_t j = 0; j < m_vecRender[i].size(); ++j)
			m_vecRender[i][j]->Render(hDc);

		m_vecRender[i].clear();
	}
}

RETURN_TYPE CObjMgr::UpdateObj( void )
{
	OBJITER	iter_begin;
	OBJITER iter_end;

	RETURN_TYPE eReturn = RETURN_NULL;

	for(int i = 0; i < OBJ_END; ++i)
	{
		iter_begin = m_ObjList[i].begin();
		iter_end = m_ObjList[i].end();

		for(; iter_begin != iter_end; )
		{
			eReturn = (*iter_begin)->Update();

			if(RETURN_DEAD == eReturn)
			{
				Safe_Delete<CObj*>(*iter_begin);
				iter_begin = m_ObjList[i].erase(iter_begin);
			}
			else if(RETURN_SCENECHANGE == eReturn)
				return eReturn;
			else
				++iter_begin;
		}
	}

	return RETURN_NULL;
}

bool CObjMgr::CompareX( CObj* pSour, CObj* pDest )
{
	return pSour->GetInfo()->vPos.x < pDest->GetInfo()->vPos.x;
}

bool CObjMgr::CompareY( CObj* pSour, CObj* pDest )
{
	return pSour->GetInfo()->vPos.y < pDest->GetInfo()->vPos.y;
}

CObj* CObjMgr::AimTarget( CObj* pObj, OBJ_TYPE eTargetID )
{
	CObj* pTarget = NULL;

	if(m_ObjList[eTargetID].empty())
		return pTarget;

	OBJITER iter_begin = m_ObjList[eTargetID].begin();
	OBJITER iter_end = m_ObjList[eTargetID].end();

	pTarget = (*iter_begin);

	float fWidth = fabs(pObj->GetInfo()->vPos.x - pTarget->GetInfo()->vPos.x);
	float fHeight = fabs(pObj->GetInfo()->vPos.y - pTarget->GetInfo()->vPos.y);

	float fDistance = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

	for(; iter_begin != iter_end; ++iter_begin)
	{
		float fWidth = fabs(pObj->GetInfo()->vPos.x - (*iter_begin)->GetInfo()->vPos.x);
		float fHeight = fabs(pObj->GetInfo()->vPos.y - (*iter_begin)->GetInfo()->vPos.y);

		float fTempDist = sqrtf((fWidth * fWidth) + (fHeight * fHeight));
		
		if(fTempDist < fDistance)
		{
			fDistance = fTempDist;
			pTarget = *iter_begin;
		}
	}

	return pTarget;
}
