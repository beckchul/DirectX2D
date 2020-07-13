#pragma once

class CTextureLoadMgr
{
DECLARE_SINGLETON(CTextureLoadMgr)

private:
	CTextureLoadMgr(void);
public:
	~CTextureLoadMgr(void);

public:
	void LoadImageByScene(SCENE_TYPE eSceneType);
	void Release(void);
};
