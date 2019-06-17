#include "PCH.h"
#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(const PointLight& other)
{
}

PointLight::~PointLight()
{
}

void PointLight::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void PointLight::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR4(x, y, z, 1.0f);
	return;
}

D3DXVECTOR4 PointLight::GetDiffuseColor()
{
	return m_diffuseColor;
}

D3DXVECTOR4 PointLight::GetPosition()
{
	return m_position;
}