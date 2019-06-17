#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "ColorShader.h"
#include "TextureShader.h"
#include "FontShader.h"
#include "LightShader.h"
#include "TerrainShader.h"
#include "SkyDomeShader.h"
#include "SkyPlaneShader.h"
#include "DepthShader.h"
#include "ShadowShader.h"

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND, D3DXMATRIX);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderFontShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR4);
	bool RenderLightShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
		D3DXVECTOR3, D3DXVECTOR4, float);
	bool RenderTerrainShader(ID3D11DeviceContext*, int);
	bool RenderSkyDomeShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR4, D3DXVECTOR4);
	bool RenderSkyPlaneShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, float, float);
	bool RenderDepthShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	bool RenderShadowShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4);

	TerrainShader* GetTerrainShader() { return m_TerrainShader; }
private:
	ColorShader		*m_ColorShader;
	TextureShader	*m_TextureShader;
	FontShader		*m_FontShader;
    LightShader		*m_LightShader;
	TerrainShader	*m_TerrainShader;
	SkyDomeShader	*m_SkyDomeShader;
	SkyPlaneShader	*m_SkyPlaneShader;
	DepthShader		*m_DepthShader;
	ShadowShader	*m_ShadowShader;
};
#endif