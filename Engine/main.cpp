#include "PCH.h"
#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Create the system object.
	 System* system = new System;
	if (!system) return -1;

	// Initialize and run the system object.
	if(system->Initialize()) system->Run();

	// Shutdown and release the system object.
	system->Shutdown();
	delete system;
	system = nullptr;

	return 0;
}