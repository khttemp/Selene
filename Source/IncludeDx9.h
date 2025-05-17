#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <dshow.h>
#include <vmr9.h>


//-----------------------------------------------------------------------------------
// LIB
//-----------------------------------------------------------------------------------
#pragma comment( lib, "../../SDK/DirectX/DirectX9/Library/d3d9.lib" )
#pragma comment( lib, "../../SDK/DirectX/DirectX9/Library/d3dx9.lib" )


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
static const D3DFORMAT D3DFMT_R2VB	= (D3DFORMAT)MAKEFOURCC('R','2','V','B');
static const D3DFORMAT D3DFMT_DF24	= (D3DFORMAT)MAKEFOURCC('D','F','2','4');
static const Uint32 FOURCC_GET1		= MAKEFOURCC('G','E','T','1');
static const Uint32 FOURCC_GET4		= MAKEFOURCC('G','E','T','4');

