////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "Terrain.h"
#include "colorshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "InputClass.h"

#include <vector>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, InputClass*);
	void Shutdown();
	bool Frame(int, float, int, int, int);

private:
	bool Render();

private:
	D3DClass*				 m_D3D;
	InputClass*				 m_Input;
	CameraClass*			 m_Camera;
	TerrainClass*			 m_Terrain;
	TextClass*				 m_Text;
	BitmapClass*			 m_Bitmap;
	LightClass*				 m_Light;
	LightShaderClass*		 m_LightShader;
	ColorShaderClass*		 m_ColorShader;
	TextureShaderClass*		 m_TextureShader;
	std::vector<ModelClass*> m_Models;
};
#endif