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
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
		D3DXVECTOR3 color;
	};

	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Terrain();
	Terrain(const Terrain&);
	~Terrain();	

	bool Initialize(ID3D11Device*, const char*);
	void Shutdown();

	int GetVertexCount();
	void CopyVertexArray(void*);

	void GetTerrainSize(int&, int&);

private:
	bool LoadSetupFile(const char*);
	bool LoadBitmapHeightMap();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();

	bool LoadColorMap();
	bool BuildTerrainModel();
	void ShutdownTerrainModel();

	void CalculateTerrainVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

private:
	HeightMapType	*m_heightMap;
	ModelType		*m_terrainModel;
	VertexType		*m_vertices;
	int				m_vertexCount;
	int 			m_terrainHeight, m_terrainWidth;
	float 			m_heightScale;
	char			*m_terrainFilename, *m_colorMapFilename;
};

#endif