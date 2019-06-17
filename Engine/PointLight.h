////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

class PointLight
{
public:
	PointLight();
	PointLight(const PointLight&);
	~PointLight();

	void SetDiffuseColor(float, float, float, float);
	void SetPosition(float, float, float);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR4 GetPosition();

private:
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_position;
};
#endif