#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <winsock2.h>
#include <commdlg.h>
#include <commdlg.h>
#include <mmsystem.h>
#include <process.h>
#include <strsafe.h>
#include <shlobj.h>
#include <math.h>

#define dNODEBUG
#define dSINGLE

#include "IncludeDx9.h"

#include "../../../SDK/OpenDynamicsEngine/Include/ode.h"
#include "../../../SDK/Crypt/Include/Crypt.h"
#include "../../Plugins/Shader/ShaderPlugin.h"
#include "../../Plugins/Sound/SoundPlugin.h"

//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "imm32.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "shell32.lib" )

#pragma comment( lib, "../../SDK/Crypt/Library/Crypt.lib" )
#pragma comment( lib, "../../SDK/OpenDynamicsEngine/Library/ode.lib" )

