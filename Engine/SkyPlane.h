#ifndef _SKYPLANE_H_
#define _SKYPLANE_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Texture.h"

class SkyPlane
{
private:
	struct SkyPlaneType
	{
		float x, y, z;
		float tu, tv;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	SkyPlane();
	SkyPlane(const SkyPlane&);
	~SkyPlane();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Frame();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetCloudTexture();
	ID3D11ShaderResourceView* GetPerturbTexture();
	
	float GetScale();
	float GetBrightness();
	float GetTranslation();

private:
	bool InitializeSkyPlane(int, float, float, float, int);
	void ShutdownSkyPlane();

	bool InitializeBuffers(ID3D11Device*, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();

private:
	SkyPlaneType	*m_skyPlane;
	ID3D11Buffer	*m_vertexBuffer, *m_indexBuffer;
	Texture			*m_CloudTexture, *m_PerturbTexture;
	int				m_vertexCount, m_indexCount;
	float			m_scale, m_brightness, m_translation;
};
#endif