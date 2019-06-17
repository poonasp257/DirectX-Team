#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();
	
	void MoveForward(float units);
	void Strafe(float units);
	void Yaw(float radians);
	void Pitch(float radians);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetRight();
	D3DXMATRIX GetRotMatrix();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	float getYaw();
	float getPitch();

private:
	D3DXMATRIX  m_viewMatrix;
	D3DXMATRIX  m_rotMatrix;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_lookAt;
	D3DXVECTOR3 m_velocity;
	float       m_yaw;
	float       m_pitch;
	float       m_maxPitch;
	float       m_maxVelocity;
	float       m_fov;
	float       m_aspect;
	float       m_nearPlane;
	float       m_farPlane;
	bool        m_invertY;
	bool        m_enableYMovement;
};

#endif