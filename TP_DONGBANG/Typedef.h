#pragma once

class CObj;
typedef list<CObj*>			OBJLIST;
typedef OBJLIST::iterator	OBJITER;

class CBitMap;
typedef map<const TCHAR*, CBitMap*> BITMAP_MAP;
typedef map<const TCHAR*, CBitMap*>::iterator BITMAP_MAPITER;