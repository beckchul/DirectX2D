#pragma once

class CDevice
{
private:
	static CDevice*	m_pInstance;

public:
	static CDevice* GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CDevice;
		}
		return m_pInstance;
	}

	void Destroy(void)
	{
		Safe_Delete(m_pInstance);
	}
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3dDevice;
	LPD3DXSPRITE		m_pSprite;

public:
	HRESULT InitD3D(void);
	void SetParameters(D3DPRESENT_PARAMETERS& d3dp);
	void Render_Begin(void);
	void Render_End(void);
	void Release(void);

public:
	LPDIRECT3DDEVICE9 GetDevice(void)
	{
		return m_pD3dDevice;
	}

	LPD3DXSPRITE GetSprite(void)
	{
		return m_pSprite;
	}


private:
	CDevice(void);
public:
	~CDevice(void);
};

//##ÀåÄ¡
//-> Com°´Ã¼ : Component Object Model
