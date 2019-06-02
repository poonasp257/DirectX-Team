#include "PCH.h"
#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_Input = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Text = 0;
	m_Bitmap = 0;
	m_Light = 0;
	m_ShaderManager = 0;
	m_SkyDome = 0;
	m_SkyPlane = 0;
	rotation = 0;
}

Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, Input* input)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	m_Input = input;

	// Create the Direct3D object.
	m_D3D = new Direct3D;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -20.0f);
	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);
	
	// Create the terrain object.
	m_Terrain = new Terrain;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Engine/data/setup.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new Text;
	if (!m_Text)
	{
		return false;
	}
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
		screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}	// Create the bitmap object.
	m_Bitmap = new Bitmap;
	if (!m_Bitmap)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		L"../Engine/data/crosshair.png", screenHeight /10, screenHeight/10);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}	// Create the light object.
	m_Light = new Light;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-0.5f, -1.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(5.0f);	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
	{
		return false;
	}
	
	WCHAR* terrainTextures[1] = {
		L"../Engine/data/ice.dds"
	};

	// Create the texture manager object.
	m_TerrainTextures = new TextureManager;
	if (!m_TerrainTextures)
	{
		return false;
	}

	// Initialize the texture manager object.
	result = m_TerrainTextures->Initialize(1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture manager object.", L"Error", MB_OK);
		return false;
	}
	
	// Load textures into the texture manager.
	for (int i = 0; i < 1; ++i) {
		result = m_TerrainTextures->LoadTexture(m_D3D->GetDevice(), terrainTextures[i], i);
		if (!result)
		{
			return false;
		}
	}

	const int NumOfModel = 4;
	WCHAR* modelTextures[NumOfModel] = {
		L"../Engine/data/earth.dds",
		L"../Engine/data/13908_Neptune_planet_diff.dds",
		L"../Engine/data/Jupiter_diff.dds",
		L"../Engine/data/cp1.dds"
	};
	WCHAR*	models[NumOfModel] = {
		L"../Engine/data/Earth.obj",
		L"../Engine/data/Neptune.obj",
		L"../Engine/data/Jupiter.obj",
		L"../Engine/data/GX7 interceptor.obj"
	};

	// Create the model object.
	for (int i = 0; i < 2; ++i)
	{
		Model* newModel = new Model;
		result = newModel->Initialize(m_D3D->GetDevice(), models[i], modelTextures[i]);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_Models.push_back(newModel);
	}	// Create the skydome object.
	m_SkyDome = new SkyDome;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the skydome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}
	// Create the sky plane object.
	m_SkyPlane = new SkyPlane;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_D3D->GetDevice(), L"../Engine/data/cloud001.dds", L"../Engine/data/perturb001.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}
		m_Camera->GetViewMatrix(baseViewMatrix);

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}	// Set wire frame rendering initially to enabled.
	m_wireFrame = false;	
	return true;
}

void Graphics::Shutdown()
{
	// Release the sky plane object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	// Release the skydome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the model object.
	for (auto it = m_Models.begin(); it != m_Models.end(); )
	{
		if (*it)
		{
			(*it)->Shutdown();
			delete (*it);
			it = m_Models.erase(it);
		}
		else ++it;
	}

	// Release the texture manager object.
	if (m_TerrainTextures)
	{
		m_TerrainTextures->Shutdown();
		delete m_TerrainTextures;
		m_TerrainTextures = 0;
	}

	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	
	return;
}

bool Graphics::Frame(int fps, float frameTime, int cpu, int screenWidth, int screenHeight)
{
	bool result;
	const float cameraSpeed = 20.0f;

	int deltaX, deltaY;
	m_Input->GetMouseDeltaPosition(deltaX, deltaY);

	m_Camera->Yaw(deltaX * frameTime * 0.00018f);
	m_Camera->Pitch(deltaY * frameTime * 0.00018f);

	if (m_Input->GetKey(KeyCode::W)) m_Camera->MoveForward(cameraSpeed * frameTime);
	if (m_Input->GetKey(KeyCode::A)) m_Camera->Strafe(-cameraSpeed * frameTime);
	if (m_Input->GetKey(KeyCode::S)) m_Camera->MoveForward(-cameraSpeed * frameTime);
	if (m_Input->GetKey(KeyCode::D)) m_Camera->Strafe(cameraSpeed * frameTime);
	if (m_Input->GetKey(KeyCode::LSHFIT)) {}

	if (m_Input->GetKeyDown(KeyCode::F1)) m_Text->TurnOnOffRenderInfo();
	if (m_Input->GetKeyDown(KeyCode::F2)) m_wireFrame = !m_wireFrame;

	// Set the frames per second.
	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetNumOfObjects(m_Models.size(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	int numOfPolygons = 0;
	for (auto model : m_Models) numOfPolygons += model->GetPolygonsCount();

	result = m_Text->SetNumOfPolygons(numOfPolygons, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetScreenSize(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();

	// Render the graphics scene.
	result = Render(screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}

	return true;
}

bool Graphics::Render(int screenWidth, int screenHeight)
{
	bool result;
	const size_t NumOfObject = m_Models.size();
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXVECTOR3 cameraPosition;
	vector<D3DXMATRIX> objectMatrices(m_Models.size());
	vector<D3DXVECTOR3> positions({
		{ -840.0f, +204.0f, 820.0f},
		{ 740.0f, 130.0f, -340.0f},
		{ 1100.0f, -331.0f, 120.0f},
		{ 0.0f, 800.0f, 20.0f},
	});
		
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);


	// 카메라 위치를 얻는다.
	cameraPosition = m_Camera->GetPosition();
	// 스카이 돔을 카메라 위치를 중심으로 변환합니다.
	D3DXMatrixTranslation(&worldMatrix,
		cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// 표면 컬링을 끕니다.
	m_D3D->DisableCulling();
	//// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->DisableZBuffer();

	// 스카이 돔 셰이더를 사용하여 하늘 돔을 렌더링합니다.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyDomeShader(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result) return false;

	// 다시 표면 컬링을 되돌립니다.
	m_D3D->EnableCulling();
	// Enable additive blending so the clouds blend with the sky dome color.
	m_D3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyPlaneShader(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), 
		m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(), m_SkyPlane->GetBrightness());
	if (!result) return false;
	
	// Turn off alpha blending after rendering the text.
	m_D3D->DisableAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->EnableZBuffer();
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	   
	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame) m_D3D->EnableWireframe();

	// Render the terrain buffers.
	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_TerrainTextures->GetTexture(0), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame) m_D3D->DisableWireframe();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (int i = 0; i < m_Models.size(); ++i)
	{
		D3DXMATRIX mat, rot;
		rotation += 0.002f;
		D3DXMatrixScaling(&mat, 0.1f, 0.1f, 0.1f);
		objectMatrices[i] = worldMatrix;
		D3DXMatrixRotationY(&rot, rotation);
		D3DXMatrixTranslation(&objectMatrices[i],
			positions[i].x, positions[i].y, positions[i].z);

		objectMatrices[i] = rot * objectMatrices[i] * mat;

		m_Models[i]->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			objectMatrices[i], viewMatrix, projectionMatrix,
			m_Models[i]->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
			m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		if (!result) return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->DisableZBuffer();
	// Turn on the alpha blending before rendering the text.
	m_D3D->EnableAlphaBlending();

	//Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), screenWidth / 2 - screenHeight / 20, screenHeight / 2 - screenHeight / 20);
	if (!result)
	{
		return false;
	}

	//Render the bitmap with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
		worldMatrix,  orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}
	
	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->DisableAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->EnableZBuffer();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}