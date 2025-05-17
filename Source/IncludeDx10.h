#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include <d3d10.h>
#include <d3dx10.h>
#include <dinput.h>
#include <dsound.h>


//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
typedef D3DCAPS10						D3DCAPS;
typedef IDirect3D10						IDirect3D;
typedef IDirect3DQuery10				IDirect3DQuery;
typedef IDirect3DDevice10				IDirect3DDevice;
typedef IDirect3DSurface10				IDirect3DSurface;
typedef IDirect3DTexture10				IDirect3DTexture;
typedef IDirect3DIndexBuffer10			IDirect3DIndexBuffer;
typedef IDirect3DBaseTexture10			IDirect3DBaseTexture;
typedef IDirect3DVertexBuffer10			IDirect3DVertexBuffer;
typedef IDirect3DVertexDeclaration10	IDirect3DVertexDeclaration;


//-----------------------------------------------------------------------------------
// LIB
//-----------------------------------------------------------------------------------
#pragma comment( lib, "../../DirectXSDK/Library/d3d10.lib" )
#pragma comment( lib, "../../DirectXSDK/Library/d3dx10.lib" )

