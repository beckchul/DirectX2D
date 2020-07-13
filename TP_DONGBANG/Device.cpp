#include "StdAfx.h"
#include "Device.h"

CDevice* CDevice::m_pInstance;

HRESULT CDevice::InitD3D(void)
{
	//##D3D ������Ʈ�� �����Ѵ�.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//##��ġ�� ������ ����. -> m_pD3dDevice�� ����� ���ؼ�.
	//������ ���Ŀ� �ٽ� ���.

	//��ġ�� ������ �����ϰ� �����ϴ� ����.
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if( FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)) )
	{
		//��ġ �ʱ�ȭ ���н� ���⿡ ���´�.
		MessageBox(g_hWnd, L"��ġ �ʱ�ȭ ����", L"��ġ �ʱ�ȭ ����", MB_OK);

		return E_FAIL;
		//##��ġ �ʱ�ȭ?
		//1.��ġ�� �����Ѵ�(Ư�����ɿ� ���� ���縦 �Ѵ�)
		//2.��ġ�� ��ǥ�ϴ� ��ü�� �����Ѵ�.
		//3.��ġ�� ��ǥ�ϴ� ��ü�� �����Ҽ� �ֵ��� Ŭ������ �������Ѵ�.
		//4.��ġ�� ����� ������ ���ؼ��� 3�� Ŭ����(��ü)�� �̿��Ѵ�.
		//5.���������� ����Ұ��̱� ������ �̱��������� ����Ѵ�.

		//##Ư������?
		//1.���ؽ� ���μ����̶�� ���̴�.
		//2.���̷�Ʈ������ �ǻ�� ����ϰ� ����ϱ� ���ؼ�
		//  ���ü�� �ݻ��ϴ� ������ �����س��´�.
		//3.�ʱ�ȭ ���Ŀ� �������� �Ұ�쿡 ����� ���� ����Ʈ�� �ش��ϴ� ������ �ݵ�� �����ϰ� �ȴ�.
		//4.�̷� ����ó���� "��ġ(HARDWARE)"���� ����? "Cpu(Soft)"���� ���� ���������ִ°��� ���ؽ����μ��� �ʱ�ȭ ����.

		//���ؽ���?
		//�ϳ��� ��.

		//���ؽ� ���μ��� : ���� ��ȯ + ����
	}

	DWORD vp;

	//�ʱ�ȭ ������� ���� 
	//���ؽ��� ���� ���� ������ ��� ó������ �Ǵ����ְ� �ȴ�.
	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//�׷��� ī�带 �������شٸ� �����.
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	//�������� �ʴ´ٸ�.

	
	//��ġ�� �����Ҷ� �����ڰ� ����(����)������ϴ� ����ü(��ġ ����)
	D3DPRESENT_PARAMETERS  d3dpp;

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);			//�Լ��� ������� ó������.
	//�� �Լ� ���� : ����̽� �ʱ�ȭ�� �����̴�.

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp,
								&d3dpp, &m_pD3dDevice) ))
	{
		MessageBox(g_hWnd, L"����̽� �ʱ�ȭ ����", L"����̽� �ʱ�ȭ ����", MB_OK);

		return E_FAIL;
	}


	if(FAILED(D3DXCreateSprite(m_pD3dDevice, &m_pSprite)))
	{
		MessageBox(g_hWnd, L"��������Ʈ ��ü ���� ����", L"��������Ʈ ��ü ���� ����", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dp)
{
	d3dp.BackBufferWidth  = WINCX;		//����� ���� ������.
	d3dp.BackBufferHeight = WINCY;		//����� ���� ������.
	d3dp.BackBufferCount  = 1;			//�߰��� ����� ����.
	d3dp.BackBufferFormat = D3DFMT_A8R8G8B8;
	//����۴� �ȼ��� �̷���� �ִ�.
	//32��Ʈ-> A8, R8, G8, B8

	d3dp.MultiSampleType = D3DMULTISAMPLE_NONE;		//���� ���ø� ������� ����.
	d3dp.MultiSampleQuality = 0;					//������� �ʱ� ������ 0.

	d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//������� ���� ���۸� ��� ����.

	//���� : �׸��� �����ϴ� ����.
	//	     ���۴� ������ �⺻���۰� �ϳ� �����.
	
	//ȭ�麸�̴� ����      : �������
	//����ڰ� �׸��� �۹� : �ĸ����

	//���������� ������ ���ۿ� �����Ͱ� �����Ѵ�.
	//���������δ� �������� ��ȭ�� �׸��� ����ϰ� �ȴ�.
	//��ġ�� �ݵ�� ������۸� ����Ű�� �����͸� ���ؼ��� �׸��� ����Ҽ� �ִ�.

	//�� ��ȯ������ "���� ü��"���� �Ѵ�.
	//�������� ����� ��ü�ϴ� ���� "������ �ø���"�̶�� �Ѵ�.

	
	d3dp.hDeviceWindow = g_hWnd;	//������ �ڵ�.
	d3dp.Windowed	   = TRUE;		//TRUE -> â���, FALSE -> ��üȭ��.

	d3dp.EnableAutoDepthStencil = TRUE;
	//���̷�Ʈ�� �ڵ����� ���̹��۸� ����� �����ϴ� �ɼ�.

	//���ٽ� ����.
	//���̹���, ����ۿ� ���� ũ�⸦ ���� ������ũ�� �����̴�.

	d3dp.AutoDepthStencilFormat = D3DFMT_D24S8;		//32��Ʈ�� 24����, 8���ٽ�

	d3dp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//�ֻ��� -> 60Hz
	//��üȭ������ ����� �Ҷ� ����� �ֻ����� ���󰡵��� �����ϴ� �ɼ�.

	d3dp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//�ֻ����� �����ӻ����� ������ �������� ó���� �Ұ�����

	//D3DPRESENT_INTERVAL_IMMEDIATE : ��� ȭ�鿡 �ÿ�(����)�Ѵ�.

	//D3DPRESENT_INTERVAL_DEFAULT : ���̷�Ʈ���� �ÿ������� �����ϰ� �ȴ�.
}

void CDevice::Render_Begin(void)
{
	//������.
	//1.���� �����ش� -> 2.�׸��� �׸��� -> 3.������۸� �����ش�.

	m_pD3dDevice->Clear(0
						,NULL		//��ġ �ּҰ� : Ư����ġ�� �����ϰ� �����ְ� ������
						,D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER	//�ĸ����, ���ٽ�, ���̹���
						,D3DCOLOR_ARGB(255, 0, 0, 255)		//ȭ�鿡 �������� ����.
						,1.f	//�������Ŀ� ���̹��� �ʱ�ȭ ��.
						,0		//���ٽ� 
						);

	m_pD3dDevice->BeginScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(void)
{
	m_pSprite->End();
	m_pD3dDevice->EndScene();
	m_pD3dDevice->Present(NULL, NULL, NULL, NULL);
	//1,2���� : ������Ʈ���� �䱸�ϰ� �ִ�.
	//        ->�շ�Ʈ �۰�, �ڷ�Ʈ ũ�� -> Ȯ��
	//		  ->�շ�Ʈ ũ��, �ڷ�Ʈ �۴� -> ���

	//3���� : ������ �ڵ�

	//4���� : ȭ������� ���� �ʴ� ������ �����Ҽ� �ִ�.
}

void CDevice::Release(void)
{
	m_pSprite->Release();
	m_pD3dDevice->Release();
	m_pD3D->Release();
}

CDevice::CDevice(void)
:m_pD3D(NULL)
,m_pD3dDevice(NULL)
{
}

CDevice::~CDevice(void)
{
}
