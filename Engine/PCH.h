#ifndef _PCH_H
#define _PCH_H

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

///////////////////
//////Linking//////
///////////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dinput8.lib")

///////////////////
//Library Include//
///////////////////
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <Pdh.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3dx10math.h>
#include <d3dx11tex.h>
#include <d3dx11async.h>
#include <dinput.h>
#include <dsound.h>

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <map>

/////////////////////
//My Header Include//
/////////////////////
#include "Direct3D.h"
#include "System.h"

#endif