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
	m_Camera->SetPosition(0.0f, 0.0f, 0.0f);
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
		L"../Engine/data/background.dds", screenWidth, screenHeight);
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
	m_Light->SetDirection(-0.5f, -1.0f, -0.5f);
	m_Light->SetSpecularColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetSpecularPower(1.0f);	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}	
	const int NumOfTexture = 1;
	const int NumOfModel = 1;
	WCHAR* textures[NumOfTexture] = {
		L"../Engine/data/ice.dds"
	};
	WCHAR*	models[NumOfModel] = {
		L""
	};

	// Create the shader manager object.
	m_TextureManager = new TextureManager;
	if (!m_TextureManager)
	{
		return false;
	}

	// Initialize the texture manager object.
	result = m_TextureManager->Initialize(NumOfTexture);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture manager object.", L"Error", MB_OK);
		return false;
	}

	// Load textures into the texture manager.
	for (int i = 0; i < NumOfTexture; ++i) {
		result = m_TextureManager->LoadTexture(m_D3D->GetDevice(), textures[i], i);
		if (!result)
		{
			return false;
		}
	}

	// Create the model object.
	for (int i = 0; i < 0; ++i)
	{
		Model* newModel = new Model;
		result = newModel->Initialize(m_D3D->GetDevice(), models[i], textures[i]);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		m_Models.push_back(newModel);
	}	// Set wire frame rendering initially to enabled.
	m_wireFrame = true;	
	return true;
}

void Graphics::Shutdown()
{
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
	if (m_TextureManager)
	{
		m_TextureManager->Shutdown();
		delete m_TextureManager;
		m_TextureManager = 0;
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

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool Graphics::Render()
{
	bool result;
	const size_t NumOfObject = m_Models.size();
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	vector<D3DXMATRIX> objectMatrices(m_Models.size());
	vector<D3DXVECTOR3> positions({
		{ 1.0f, 1.0f, 1.0f},
		{ 400.0f, 1.0f, 1.0f},
		{ 1000.0f, 1.0f, 0.0f},
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

	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame) m_D3D->EnableWireframe();

	// Render the terrain buffers.
	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_TextureManager->GetTexture(0), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result) return false;

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame) m_D3D->DisableWireframe();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (int i = 0; i < m_Models.size(); ++i)
	{
		objectMatrices[i] = worldMatrix;
		D3DXMatrixTranslation(&objectMatrices[i],
			positions[i].x, positions[i].y, positions[i].z);

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

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	//if (!result)
	//{
	//	return false;
	//}

	// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(),
	//	worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	// Turn on the alpha blending before rendering the text.
	m_D3D->EnableAlphaBlending();

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