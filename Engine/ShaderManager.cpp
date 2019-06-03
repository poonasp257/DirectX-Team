#include "PCH.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_FontShader = 0;
}

ShaderManager::ShaderManager(const ShaderManager& other)
{
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd, D3DXMATRIX	baseViewMatrix)
{
	bool result;


	// Create the color shader object.
	m_ColorShader = new ColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShader;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(device, hwnd, baseViewMatrix);
	if (!result)
	{
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShader;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the font shader object.
	m_LightShader = new LightShader;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the skydome shader object.
	m_SkyDomeShader = new SkyDomeShader;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the skydome shader object.
	result = m_SkyDomeShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the sky plane shader object.
	m_SkyPlaneShader = new SkyPlaneShader;
	if (!m_SkyPlaneShader)
	{
		return false;
	}

	// Initialize the sky plane shader object.
	result = m_SkyPlaneShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	// Release the sky plane shader object.
	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	// Release the skydome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	return;
}

bool ShaderManager::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, 
	D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	return m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix,
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	return m_TextureShader->Render(deviceContext, indexCount, worldMatrix, projectionMatrix, texture);
}

bool ShaderManager::RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, D3DXVECTOR4 color)
{
	return m_FontShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
}

bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix,
	D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture,
	D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor,
	D3DXVECTOR3 cameraPosition, D3DXVECTOR4 specularColor, float specularPower)
{
	return m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection,
		ambientColor, diffuseColor, cameraPosition, specularColor, specularPower);
}

bool ShaderManager::RenderSkyDomeShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
	D3DXMATRIX projectionMatrix, D3DXVECTOR4 apexColor, D3DXVECTOR4 centerColor)
{
	return m_SkyDomeShader->Render(deviceContext, indexCount, 
		worldMatrix, viewMatrix, projectionMatrix, 
		apexColor, centerColor);
}

bool ShaderManager::RenderSkyPlaneShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
	D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* cloudTexture, ID3D11ShaderResourceView* perturbTexture,
	float translation, float scale, float brightness)
{
	return m_SkyPlaneShader->Render(deviceContext, indexCount,
		worldMatrix, viewMatrix, projectionMatrix, 
		cloudTexture, perturbTexture, translation, scale, brightness);
}