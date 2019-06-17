#include "PCH.h"
#include "Graphics.h"

Graphics::Graphics()
{
	m_D3D = 0;
	m_Input = 0;
	m_gunShot = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Text = 0;
	m_Bitmap = 0;
	m_UI = 0;
	m_Light = 0;
	m_ShaderManager = 0;
	m_SkyDome = 0;
	m_SkyPlane = 0;
	m_Frustum = 0;
	m_RenderTexture = 0;
	m_QuadTree = 0;
	m_MiniMap = 0;
	m_ParticleSystem = 0;
	m_PointLight = 0;
	m_numOfPolygons = 0;
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

	m_gunShot = new Sound;
	if (!m_gunShot)
	{
		return false;
	}
	result = m_gunShot->Initialize(hwnd, "../Engine/data/gunshot.wav");
	if (!result)
	{
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
	//m_Camera->SetPosition(100.0f, 0.0f, 200.0f);
	m_Camera->SetPosition(200.0f, 14.0f, 208.0f);

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystem;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/snow.dds");//star
	if (!result)
	{
		return false;
	}

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
	}

	// Create the bitmap object.
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
	}

	// Create the bitmap object.
	m_UI = new Bitmap;
	if (!m_UI)
	{
		return false;
	}
	// Initialize the bitmap object.
	result = m_UI->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		L"../Engine/data/UI.dds", screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
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
	m_Light->SetSpecularPower(30.0f);
//	m_Light->SetLookAt(0.0f, 0.0f, 0.0f);
//	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	m_PointLight = new PointLight;
	if (!m_PointLight)
	{
		return false;
	}

	m_PointLight->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_PointLight->SetPosition(308.0f, 15.0f, 182.0f); 

	// Create the render to texture object.
	m_RenderTexture = new RenderTexture;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}
	
	WCHAR* terrainTextures[2] = {
		L"../Engine/data/ice.dds",
		L"../Engine/data/ice_bump.dds"
	};

	// Create the texture manager object.
	m_TerrainTextures = new TextureManager;
	if (!m_TerrainTextures) return false; 

	// Initialize the texture manager object.
	result = m_TerrainTextures->Initialize(2);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture manager object.", L"Error", MB_OK);
		return false;
	}
	
	// Load textures into the texture manager.
	for (int i = 0; i < 2; ++i) {
		result = m_TerrainTextures->LoadTexture(m_D3D->GetDevice(), terrainTextures[i], i);
		if (!result) return false;
	}

	const int NumOfModel = 13;
	WCHAR*	models[NumOfModel] = {
		L"../Engine/data/Earth.obj",
		L"../Engine/data/Jupiter.obj",
		L"../Engine/data/military container.obj",
		L"../Engine/data/military container.obj",
		L"../Engine/data/antena.obj",
		L"../Engine/data/floor.obj", 
		L"../Engine/data/Lampe.obj",
		L"../Engine/data/train.obj",
		L"../Engine/data/spaceship01.obj",
		L"../Engine/data/spaceship02.obj",
		L"../Engine/data/spaceship02.obj",
		L"../Engine/data/spaceship02.obj",
		L"../Engine/data/spaceship03.obj",
	};
	WCHAR* modelTextures[NumOfModel] = {
		L"../Engine/data/earth.dds",
		L"../Engine/data/Jupiter_diff.dds",
		L"../Engine/data/floor.dds",
		L"../Engine/data/floor.dds",
		L"../Engine/data/antena.dds",
		L"../Engine/data/floor.dds",
		L"../Engine/data/Lampe.dds",
		L"../Engine/data/train.dds",
		L"../Engine/data/spaceship01.dds",
		L"../Engine/data/spaceship02.dds",
		L"../Engine/data/spaceship02.dds",
		L"../Engine/data/spaceship02.dds",
		L"../Engine/data/spaceship03.dds",
	};
	D3DXVECTOR3 positions[] = {
		{ 0.0f, 150.0f, -700.0f},
		{ 0.0f, 150.0f, -700.0f},
		{ 286.0f, 12.5f, 208.0f },
		{ 300.0f, 13.5f, 180.0f },
		{ 230.0f, 42.5f, 76.0f },
		{ 309.0f, 6.0f, 300.0f},
		{ 308.0f, 15.0f, 182.0f }, 
		{ 330.0f, 13.0f, 190.0f },
		{ -250.0f, 750.0f, -200.0f },
		{ -250.0f, 460.0f, 320.0f },
		{ -300.0f, 460.0f, 280.0f },
		{ -200.0f, 460.0f, 280.0f },
		{ 309.0f, 5.0f, 300.0f},
	};
	D3DXVECTOR3 scales[] = {
		{ 0.5f, 0.5f, 0.5f},
		{ 1.0f, 1.0f, 1.0f},
		{ 0.04f, 0.04f, 0.04f },
		{ 0.03f, 0.03f, 0.03f },
		{ 0.1f, 0.1f, 0.1f },
		{ 15.0f, 15.0f, 15.0f},
		{ 0.01f, 0.01f, 0.01f},
		{ 1.0f, 1.0f, 1.0f},
		{ 0.3f, 0.3f, 0.3f},
		{ 10.0f, 10.0f, 10.0f},
		{ 10.0f, 10.0f, 10.0f},
		{ 10.0f, 10.0f, 10.0f},
		{ 1.0f, 1.0f, 1.0f},
	};

	m_Gun = new Model;
	result = m_Gun->Initialize(m_D3D->GetDevice(),
		L"../Engine/data/gun.obj", L"../Engine/data/gun.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	   
	D3DXMATRIX objMat, scaleMat;
	// Create the model object.
	for (int i = 0; i < NumOfModel; ++i)
	{ 
		Model* newModel = new Model;
		result = newModel->Initialize(m_D3D->GetDevice(), models[i], modelTextures[i]);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_D3D->GetWorldMatrix(objMat);
		D3DXMatrixIdentity(&scaleMat);
		D3DXMatrixTranslation(&objMat, positions[i].x, positions[i].y, positions[i].z);
		D3DXMatrixScaling(&scaleMat, scales[i].x, scales[i].y, scales[i].z);
		D3DXMatrixMultiply(&objMat, &scaleMat, &objMat);

		m_Models.push_back(newModel);
		m_objMatrices.push_back(objMat);
	}

	// Create the skydome object.
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
	result = m_SkyPlane->Initialize(m_D3D->GetDevice(), L"../Engine/data/cloud.dds", L"../Engine/data/perturb.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}
	
	// Set wire frame rendering initially to enabled.
	m_wireFrame = false;
	
	// Create the frustum object.
	m_Frustum = new Frustum;
	if (!m_Frustum)
	{
		return false;
	}

	m_QuadTree = new QuadTree;
	if (!m_QuadTree)
	{
		return false;
	}

	// Initialize the quad tree object.
	result = m_QuadTree->Initialize(m_Terrain, m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the quad tree object.", L"Error", MB_OK);
		return false;
	}
	
	int terrainWidth, terrainHeight;	

	// Get the size of the terrain as the minimap will require this information.
	m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);
	
	// Create the mini map object.
	m_MiniMap = new MiniMap;
	if (!m_MiniMap)
	{
		return false;
	}

	// Initialize the mini map object.
	result = m_MiniMap->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1),
		(float)(terrainHeight - 1));
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void Graphics::Shutdown()
{
	// Release the mini map object.
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}

	// Release the quad tree object.
	if (m_QuadTree)
	{
		m_QuadTree->Shutdown();
		delete m_QuadTree;
		m_QuadTree = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

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

	// Release the light objects. 
	if(m_PointLight) 
	{ 
		delete m_PointLight;
		m_PointLight = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the bitmap object.
	if (m_UI)
	{
		m_UI->Shutdown();
		delete m_UI;
		m_UI = 0;
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

	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_gunShot)
	{
		m_gunShot->Shutdown();
		delete m_gunShot;
		m_gunShot = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
}

bool Graphics::Frame(int fps, float frameTime, int cpu, int screenWidth, int screenHeight)
{
	bool result;
	int dir = 1;
	int deltaX, deltaY;
	const int cameraSpeed = m_Camera->GetSpeed();
	static float delay = 0.0f;

	// Run the frame processing for the particle system.
	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	m_Input->GetMouseDeltaPosition(deltaX, deltaY);
	m_Camera->Yaw(deltaX * frameTime * 0.00018f);
	m_Camera->Pitch(deltaY * frameTime * 0.00018f);

	if (m_Input->GetLBMouseDown() && delay >= 100.0f) {
		m_gunShot->PlayWaveFile(-2000, false);
		delay = 0.0f;
	}
	else { 
		m_gunShot->StopWaveFile(); 
		delay += frameTime;
	}

	if (m_Input->GetKey(KeyCode::LSHFIT)) { m_Camera->SetSpeed(cameraSpeed * 1.2f); }
	else { m_Camera->SetSpeed(cameraSpeed); }

	if (m_Input->GetKey(KeyCode::W)) m_Camera->MoveForward(dir * frameTime);
	if (m_Input->GetKey(KeyCode::A)) m_Camera->Strafe(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::S)) m_Camera->MoveForward(-dir * frameTime);
	if (m_Input->GetKey(KeyCode::D)) m_Camera->Strafe(dir * frameTime);

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

	m_numOfPolygons = 0;
	m_numOfPolygons += m_Gun->GetPolygonsCount();
	for (auto model : m_Models) m_numOfPolygons += model->GetPolygonsCount();

	result = m_Text->SetScreenSize(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();
	
	// Get the current position of the camera.
	D3DXVECTOR3 position = m_Camera->GetPosition();
	float height;

	result = m_Text->SetPosition(position, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Get the height of the triangle that is directly underneath the given camera position.
	bool foundHeight = m_QuadTree->GetHeightAtPosition(position.x, position.z, height);
	if (foundHeight)
	{
		// If there was a triangle under the camera then position the camera just above it by two units.
		m_Camera->SetPosition(position.x, height + 2.0f, position.z);
	}
	
	// Update the location of the camera on the mini map.
	m_MiniMap->PositionUpdate(position.x, position.z);

	// Render the graphics scene.
	result = Render(screenWidth, screenHeight);
	if(!result)
	{
		return false;
	}

	return true;
}

bool Graphics::RenderSceneToTexture()
{
	D3DXMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	bool result;
	
	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());
	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (int i = 0; i < m_Models.size(); ++i)
	{
		// Set the radius of the sphere to 1.0 since this is already known.
		const float radius = 1.0f;
		// Check if the sphere model is in the view frustum.
		bool renderModel = true;//m_Frustum->CheckSphere(m_objMatrices[i]._41, m_objMatrices[i]._42, m_objMatrices[i]._43, radius);
		// If it can be seen then render it, if not skip this model and check the next sphere.
		if (renderModel)
		{
			D3DXMATRIX objMat, rotMat;
			static float rotX = 0.0f, rotY = 0.0f;
			objMat = m_objMatrices[i];
			rotX += 0.002f;
			rotY += 0.002f;
			D3DXMatrixIdentity(&rotMat);
			D3DXMatrixRotationX(&rotMat, rotX);
			D3DXMatrixRotationY(&rotMat, rotY);

			if (i < 2) {
				D3DXMatrixMultiply(&objMat, &objMat, &rotMat);
			}

			m_Models[i]->Render(m_D3D->GetDeviceContext());
			// Render the model using the light shader.
			result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
				m_objMatrices[i], lightViewMatrix, lightProjectionMatrix);
			if (!result) return false;
		}
	}
					
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool Graphics::Render(int screenWidth, int screenHeight)
{
	bool result;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR4 diffuseColor[1];
	D3DXVECTOR4 lightPosition[1];

	diffuseColor[0] = m_PointLight->GetDiffuseColor();
	lightPosition[0] = m_PointLight->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Get the light's view and projection matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&worldMatrix,	cameraPosition.x, cameraPosition.y, cameraPosition.z);

	m_D3D->DisableCulling();
	//// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->DisableZBuffer();

	m_SkyDome->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyDomeShader(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	if (!result) return false;
	 
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

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	//First render the scene to a texture.
	//result = RenderSceneToTexture();
	//if (!result)
	//{
	//	return false;
	//}
	
	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame) m_D3D->EnableWireframe();

	// Set the terrain shader parameters that it will use for rendering.
	m_ShaderManager->GetTerrainShader()->SetShaderParameters(m_D3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, 
		m_TerrainTextures->GetTexture(0), m_TerrainTextures->GetTexture(1), m_Light->GetDiffuseColor(), m_Light->GetDirection());

	// Render the terrain using the quad tree and terrain shader.
	m_QuadTree->Render(m_Frustum, m_D3D->GetDeviceContext(), m_ShaderManager);	
	m_numOfPolygons += m_QuadTree->GetDrawCount();
	result = m_Text->SetNumOfPolygons(m_numOfPolygons, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame) m_D3D->DisableWireframe();

	//set gun position
	D3DXMATRIX gunMatrix;
	D3DXMATRIX mat, gunView;
	D3DXMatrixScaling(&mat, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationYawPitchRoll(&gunView, m_Camera->GetYaw(), -m_Camera->GetPitch(), 0);
	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&gunMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	gunMatrix = mat * gunView *gunMatrix;

	//Render the player gun
	m_Gun->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Gun->GetIndexCount(),
		gunMatrix, viewMatrix, projectionMatrix, m_Gun->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (int i = 0; i < m_Models.size(); ++i)
	{
		// Set the radius of the sphere to 1.0 since this is already known.
		const float radius = 1.0f;
		// Check if the sphere model is in the view frustum.
		bool renderModel = true;//m_Frustum->CheckSphere(m_objMatrices[i]._41, m_objMatrices[i]._42, m_objMatrices[i]._43, radius);
		// If it can be seen then render it, if not skip this model and check the next sphere.
		if (renderModel)
		{
			D3DXMATRIX objMat, rotMatX, rotMatY;
			static float rotX = 0.0f, rotY = 0.0f;
			objMat = m_objMatrices[i];
			rotX += 0.0006f;
			rotY += 0.0006f;
			D3DXMatrixIdentity(&rotMatX);
			D3DXMatrixIdentity(&rotMatY);
			D3DXMatrixRotationX(&rotMatX, rotX);
			D3DXMatrixRotationY(&rotMatY, rotY);

			if (i == 0) {
				D3DXMatrixMultiply(&objMat, &rotMatX, &objMat);
				D3DXMatrixMultiply(&objMat, &objMat, &rotMatY);
			}

			if ( i == 1)
			{
				D3DXMatrixMultiply(&objMat, &rotMatY, &objMat);
			}

			m_Models[i]->Render(m_D3D->GetDeviceContext());
			//Render the model using the light shader.
			//result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			//	objMat, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix,
			//	m_Models[i]->GetTexture(), m_RenderTexture->GetShaderResourceView(),
			//	m_Light->GetPosition(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

			//result = m_ShaderManager->RenderPointLightShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
			//	worldMatrix, viewMatrix, projectionMatrix, m_Models[i]->GetTexture(), diffuseColor, lightPosition);
			//if (!result) { return false; }

			result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(),
				objMat, viewMatrix, projectionMatrix,
				m_Models[i]->GetTexture(), m_Light->GetDirection(),
				m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
				m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			if (!result) return false;
		}
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
		worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}
	   
	//Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_UI->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}

	//Render the bitmap with the texture shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_UI->GetIndexCount(),
		worldMatrix, viewMatrix, orthoMatrix, m_UI->GetTexture());
	if (!result)
	{
		return false;
	}
	
	// Render the mini map.
	result = m_MiniMap->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_ShaderManager);
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

	cameraPosition = m_Camera->GetPosition();
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z + 5.0f);
	worldMatrix = gunView * worldMatrix;
	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ShaderManager->RenderParticleShader(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
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