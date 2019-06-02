#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Input.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Light.h"
#include "Text.h"
#include "Bitmap.h"
#include "Terrain.h"
#include "Model.h"
#include "SkyDome.h"
#include "SkyPlane.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND, Input*);
	void Shutdown();
	bool Frame(int, float, int, int, int);

private:
	bool Render();

private:
	Direct3D			*m_D3D;
	Input				*m_Input;
	Camera				*m_Camera;
	Terrain				*m_Terrain;
	Text				*m_Text;
	Bitmap				*m_Bitmap;
	Light				*m_Light;
	ShaderManager		*m_ShaderManager;
	TextureManager		*m_TerrainTextures;
	vector<Model*>		 m_Models;
	SkyDome				*m_SkyDome;
	SkyPlane			*m_SkyPlane;
	bool				 m_wireFrame;
};
#endif