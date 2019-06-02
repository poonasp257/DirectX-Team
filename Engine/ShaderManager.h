#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "ColorShader.h"
#include "TextureShader.h"
#include "FontShader.h"
#include "LightShader.h"

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
	bool RenderFontShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR4);
	bool RenderLightShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
		D3DXVECTOR3, D3DXVECTOR4, float);

private:
	ColorShader		*m_ColorShader;
	TextureShader	*m_TextureShader;
	FontShader		*m_FontShader;
	LightShader		*m_LightShader;
};
#endif