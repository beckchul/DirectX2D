#include "StdAfx.h"
#include "SceneMgr.h"
#include "Intro.h"
#include "Title.h"
#include "Ending.h"
#include "Select.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
: m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::SetScene( SCENE_TYPE eType )
{
	// 기존 Scene 해제
	if(NULL != m_pScene)
		Safe_Delete<CScene*>(m_pScene);

	switch(eType)
	{
	case SCENE_INTRO:
		m_pScene = new CIntro;
		break;

	case SCENE_TITLE:
		m_pScene = new CTitle;
		break;

	case SCENE_SELECT:
		m_pScene = new CSelect;
		break;

	case SCENE_STAGE:
		m_pScene = new CStage;
		break;

	case SCENE_ENDING:
		m_pScene = new CEnding;
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Update( void )
{
	m_pScene->Update();
}

void CSceneMgr::Render( HDC hDc )
{
	m_pScene->Render(hDc);
}

void CSceneMgr::Release( void )
{
	if(NULL != m_pScene)
		Safe_Delete<CScene*>(m_pScene);
}


