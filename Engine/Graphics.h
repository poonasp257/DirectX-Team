#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

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
#include "Frustum.h"
#include "RenderTexture.h"
#include "QuadTree.h" 
#include "Minimap.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

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
	bool RenderSceneToTexture();
	bool Render(int, int);
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
	vector<D3DXMATRIX>	 m_objMatrices;
	Model				*m_Gun;
	SkyDome				*m_SkyDome;
	SkyPlane			*m_SkyPlane;
	Frustum				*m_Frustum;
	RenderTexture		*m_RenderTexture;
	QuadTree			*m_QuadTree;
	MiniMap				*m_MiniMap;
	bool				 m_wireFrame;
	int					 m_numOfPolygons;
};
#endif