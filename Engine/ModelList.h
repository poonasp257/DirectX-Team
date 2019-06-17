#ifndef _ModelList_H_
#define _ModelList_H_

class ModelList
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX, positionY, positionZ;
	};
public:
	ModelList();
	ModelList(const ModelList&);
	~ModelList();

	bool Initialize(int);
	void Shutdown();
	int GetModelCount();
	void GetData(int, float&, float&, float&, D3DXVECTOR4&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};
#endif