#ifndef _DIRECT3D_H_
#define _DIRECT3D_H_

class Direct3D
{
public:
	Direct3D();
	Direct3D(const Direct3D&);
	~Direct3D();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

	void EnableZBuffer();
	void DisableZBuffer();

	void EnableAlphaBlending();
	void DisableAlphaBlending();

	void EnableWireframe();
	void DisableWireframe();

private:
	IDXGISwapChain			*m_swapChain;
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_deviceContext;
	ID3D11RenderTargetView	*m_renderTargetView;
	ID3D11Texture2D			*m_depthStencilBuffer;
	ID3D11DepthStencilState *m_depthStencilState;
	ID3D11DepthStencilView  *m_depthStencilView;
	ID3D11RasterizerState   *m_rasterState;
	ID3D11RasterizerState	*m_rasterStateWireframe;
	D3DXMATRIX				 m_projectionMatrix;
	D3DXMATRIX				 m_worldMatrix;
	D3DXMATRIX				 m_orthoMatrix;
	ID3D11DepthStencilState	*m_depthDisabledStencilState;
	ID3D11BlendState		*m_alphaEnableBlendingState;
	ID3D11BlendState		*m_alphaDisableBlendingState;
	bool					 m_vsync_enabled;
	int						 m_videoCardMemory;
	char					 m_videoCardDescription[128];
};
#endif