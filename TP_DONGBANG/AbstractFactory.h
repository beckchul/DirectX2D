#pragma once

class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj(void)
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* CreateEffect(D3DXVECTOR3 _vPos, eEFFECT_TYPE _eType)
	{
		CObj* pObj = new T;
		dynamic_cast<T*>(pObj)->SetEffectType(_eType);
		pObj->SetPos(_vPos);
		pObj->Initialize();
		return pObj;
	}

	static CObj* CreateNomalMonster(D3DXVECTOR3 _vPos, eMONSTER_TYPE _eType, eMONSTER_PATTON _Patton)
	{
		CObj* pObj = new T;
		pObj->SetPos(_vPos);
		dynamic_cast<T*>(pObj)->SetMonsterType(_eType);
		dynamic_cast<T*>(pObj)->SetMonsterPatton(_Patton);
		pObj->Initialize();
		return pObj;
	}

	static CObj* CreateMonsterBullet(D3DXVECTOR3 _vPos, eBULLET_TYPE _eType, eBULLET_COLOR _eColor, eBULLET_NUMBER _eNumber,INFO* _tInfo)
	{
		CObj* pObj = new T;
		dynamic_cast<T*>(pObj)->SetBulletType(_eType);
		dynamic_cast<T*>(pObj)->SetBulletNumber(_eNumber);
		dynamic_cast<T*>(pObj)->SetBulletColor(_eColor);
		dynamic_cast<T*>(pObj)->SetPlayerInfo(_tInfo);
		pObj->SetPos(_vPos);
		pObj->Initialize();
		return pObj;
	}

	static CObj* CreateMonsterBullet(D3DXVECTOR3 _vPos, eBULLET_TYPE _eType, eBULLET_COLOR _eColor, eBULLET_NUMBER _eNumber,INFO* _tInfo, int _iCount)
	{
		CObj* pObj = new T;
		dynamic_cast<T*>(pObj)->SetBulletType(_eType);
		dynamic_cast<T*>(pObj)->SetBulletNumber(_eNumber);
		dynamic_cast<T*>(pObj)->SetBulletColor(_eColor);
		dynamic_cast<T*>(pObj)->SetPlayerInfo(_tInfo);
		dynamic_cast<T*>(pObj)->SetDirCount(_iCount);
		pObj->SetPos(_vPos);
		pObj->Initialize();
		return pObj;
	}

	static CObj* CreateMonsterBulletAngle(D3DXVECTOR3 _vPos, eBULLET_TYPE _eType, eBULLET_COLOR _eColor
		, eBULLET_NUMBER _eNumber,INFO* _tInfo, int _iCount, float _fAngle)
	{
		CObj* pObj = new T;
		dynamic_cast<T*>(pObj)->SetBulletType(_eType);
		dynamic_cast<T*>(pObj)->SetBulletNumber(_eNumber);
		dynamic_cast<T*>(pObj)->SetBulletColor(_eColor);
		dynamic_cast<T*>(pObj)->SetPlayerInfo(_tInfo);
		dynamic_cast<T*>(pObj)->SetDirCount(_iCount);
		pObj->SetPos(_vPos);
		pObj->Initialize();
		dynamic_cast<T*>(pObj)->SetAngle(_fAngle);
		return pObj;
	}

	static CObj* CreateMonsterBulletAngle(D3DXVECTOR3 _vPos, eBULLET_TYPE _eType, eBULLET_COLOR _eColor
		, eBULLET_NUMBER _eNumber,INFO* _tInfo, int _iCount, float _fAngle, float _fSpeed)
	{
		CObj* pObj = new T;
		dynamic_cast<T*>(pObj)->SetBulletType(_eType);
		dynamic_cast<T*>(pObj)->SetBulletNumber(_eNumber);
		dynamic_cast<T*>(pObj)->SetBulletColor(_eColor);
		dynamic_cast<T*>(pObj)->SetPlayerInfo(_tInfo);
		dynamic_cast<T*>(pObj)->SetDirCount(_iCount);
		pObj->SetPos(_vPos);
		pObj->Initialize();
		dynamic_cast<T*>(pObj)->SetAngle(_fAngle);
		dynamic_cast<T*>(pObj)->SetSpeed(_fSpeed);
		return pObj;
	}
};