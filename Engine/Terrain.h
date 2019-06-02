#ifndef _TERRAIN_H_
#define _TERRAIN_H_

class Terrain
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	Terrain();
	Terrain(const Terrain&);
	~Terrain();	

	bool Initialize(ID3D11Device*, const char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool LoadSetupFile(const char*);
	bool LoadBitmapHeightMap();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();
	bool BuildTerrainModel();
	void ShutdownTerrainModel();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	int a;
private:
	ID3D11Buffer   *m_vertexBuffer, *m_indexBuffer;
	HeightMapType  *m_heightMap;
	ModelType	   *m_terrainModel;
	int				m_vertexCount, m_indexCount;
	int 			m_terrainHeight, m_terrainWidth;
	float 			m_heightScale;
	char		   *m_terrainFilename;
};

#endif