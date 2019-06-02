#include "PCH.h"
#include "FPS.h"

FPS::FPS()
{
}
FPS::FPS(const FPS& other)
{
}
FPS::~FPS()
{
}

void FPS::Initialize()
{
	m_Fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return;
}

void FPS::Frame()
{
	m_count++;
	if (timeGetTime() >= (m_startTime + 1000))
	{
		m_Fps = m_count;
		m_count = 0;
		m_startTime = timeGetTime();
	}
}

int FPS::GetFPS()
{
	return m_Fps;
}