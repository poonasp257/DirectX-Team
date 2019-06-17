#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "Input.h"
#include "Graphics.h"
#include "Sound.h"
#include "Fps.h"
#include "Cpu.h"
#include "Timer.h"

class System
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int, int);
	void ShutdownWindows();

private:
	LPCWSTR		m_applicationName;
	HINSTANCE	m_hinstance;
	HWND		m_hwnd;
	Input		*m_Input;
	Graphics	*m_Graphics;
	Sound		*m_BGM;
	FPS			*m_Fps;
	CPU			*m_Cpu;
	Timer		*m_Timer;
	int			m_screenWidth;
	int			m_screenHeight;
};

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////
// GLOBALS //
/////////////
static System* ApplicationHandle = 0;

#endif