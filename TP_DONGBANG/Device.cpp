#include "StdAfx.h"
#include "Device.h"

CDevice* CDevice::m_pInstance;

HRESULT CDevice::InitD3D(void)
{
	//##D3D 오브젝트를 생성한다.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//##장치의 성능을 조사. -> m_pD3dDevice를 만들기 위해서.
	//성능은 이후에 다시 언급.

	//장치의 성능을 조사하고 저장하는 변수.
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if( FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)) )
	{
		//장치 초기화 실패시 여기에 들어온다.
		MessageBox(g_hWnd, L"장치 초기화 실패", L"장치 초기화 실패", MB_OK);

		return E_FAIL;
		//##장치 초기화?
		//1.장치를 조사한다(특정성능에 대한 조사를 한다)
		//2.장치를 대표하는 객체를 생성한다.
		//3.장치를 대표하는 객체가 존재할수 있도록 클래스로 디자인한다.
		//4.장치에 명령을 내리기 위해서는 3번 클래스(객체)를 이용한다.
		//5.전역적으로 사용할것이기 때문에 싱글톤패턴을 사용한다.

		//##특정성능?
		//1.버텍스 프로세싱이라는 것이다.
		//2.다이렉트에서는 실사와 비슷하게 출력하기 위해서
		//  어떤객체의 반사하는 색상을 정의해놓는다.
		//3.초기화 이후에 랜더링을 할경우에 사용자 만든 디폴트에 해당하는 조명이 반드시 존재하게 된다.
		//4.이런 조명처리를 "장치(HARDWARE)"에서 할지? "Cpu(Soft)"에서 할지 결정지어주는것이 버텍스프로세싱 초기화 구문.

		//버텍스란?
		//하나의 점.

		//버텍스 프로세싱 : 점의 변환 + 조명
	}

	DWORD vp;

	//초기화 결과값에 따라서 
	//버텍스와 조명에 대한 연산을 어디서 처리할지 판단해주게 된다.
	if(DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//그래픽 카드를 지원해준다면 여기로.
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	//지원하지 않는다면.

	
	//장치를 생성할때 개발자가 설정(셋팅)해줘야하는 구조체(장치 설정)
	D3DPRESENT_PARAMETERS  d3dpp;

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);			//함수의 기능으로 처리하자.
	//이 함수 목적 : 디바이스 초기화가 목적이다.

	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp,
								&d3dpp, &m_pD3dDevice) ))
	{
		MessageBox(g_hWnd, L"디바이스 초기화 실패", L"디바이스 초기화 실패", MB_OK);

		return E_FAIL;
	}


	if(FAILED(D3DXCreateSprite(m_pD3dDevice, &m_pSprite)))
	{
		MessageBox(g_hWnd, L"스프라이트 객체 생성 실패", L"스프라이트 객체 생성 실패", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dp)
{
	d3dp.BackBufferWidth  = WINCX;		//백버퍼 가로 사이즈.
	d3dp.BackBufferHeight = WINCY;		//백버퍼 세로 사이즈.
	d3dp.BackBufferCount  = 1;			//추가할 백버퍼 개수.
	d3dp.BackBufferFormat = D3DFMT_A8R8G8B8;
	//백버퍼는 픽셀로 이루어져 있다.
	//32비트-> A8, R8, G8, B8

	d3dp.MultiSampleType = D3DMULTISAMPLE_NONE;		//다중 샘플링 사용하지 않음.
	d3dp.MultiSampleQuality = 0;					//사용하지 않기 때문에 0.

	d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//백버퍼의 더블 버퍼링 방식 설정.

	//버퍼 : 그림을 저장하는 공간.
	//	     버퍼는 무조건 기본버퍼가 하나 생긴다.
	
	//화면보이는 버퍼      : 전면버퍼
	//사용자가 그리는 퍼버 : 후면버퍼

	//내부적으로 각자의 버퍼에 포인터가 존재한다.
	//내부적으로는 포인터의 변화로 그림을 출력하게 된다.
	//장치는 반드시 전면버퍼를 가리키는 포인터를 통해서만 그림을 출력할수 있다.

	//이 변환과정을 "스왑 체인"리고 한다.
	//포인터의 대상을 교체하는 것은 "페이지 플리핑"이라고 한다.

	
	d3dp.hDeviceWindow = g_hWnd;	//윈도우 핸들.
	d3dp.Windowed	   = TRUE;		//TRUE -> 창모드, FALSE -> 전체화면.

	d3dp.EnableAutoDepthStencil = TRUE;
	//다이렉트가 자동으로 깊이버퍼를 만들고 관리하는 옵션.

	//스텐실 버퍼.
	//깊이버퍼, 백버퍼와 같은 크기를 갖는 오프스크린 버퍼이다.

	d3dp.AutoDepthStencilFormat = D3DFMT_D24S8;		//32비트중 24깊이, 8스텐실

	d3dp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//주사율 -> 60Hz
	//전체화면으로 출력을 할때 모디터 주사율을 따라가도록 설정하는 옵션.

	d3dp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//주사율과 프레임사이의 간견을 어떤방식으로 처리를 할것인지

	//D3DPRESENT_INTERVAL_IMMEDIATE : 즉시 화면에 시연(보여)한다.

	//D3DPRESENT_INTERVAL_DEFAULT : 다이렉트에서 시연간격을 설정하게 된다.
}

void CDevice::Render_Begin(void)
{
	//랜더링.
	//1.버퍼 지워준다 -> 2.그림을 그린다 -> 3.전면버퍼를 보여준다.

	m_pD3dDevice->Clear(0
						,NULL		//위치 주소값 : 특정위치만 제거하고 지워주고 싶을때
						,D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER	//후면버퍼, 스텐실, 깊이버퍼
						,D3DCOLOR_ARGB(255, 0, 0, 255)		//화면에 보여지는 색상.
						,1.f	//삭제한후에 깊이버퍼 초기화 값.
						,0		//스텐실 
						);

	m_pD3dDevice->BeginScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::Render_End(void)
{
	m_pSprite->End();
	m_pD3dDevice->EndScene();
	m_pD3dDevice->Present(NULL, NULL, NULL, NULL);
	//1,2인자 : 각각렉트값을 요구하고 있다.
	//        ->앞렉트 작고, 뒤렉트 크다 -> 확대
	//		  ->앞렉트 크도, 뒤렉트 작다 -> 축소

	//3인자 : 윈도우 핸들

	//4인자 : 화면출력이 되지 않는 공간을 설정할수 있다.
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
