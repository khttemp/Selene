#pragma once


//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define SSE_ALIGN							__declspec( align( 16 ) )
#define SSE_X								(0x03)
#define SSE_Y								(0x02)
#define SSE_Z								(0x01)
#define SSE_W								(0x00)
#define SSE_PACK(a,b,c,d)					((a<<6) | (b<<4) | (c<<2) | (d<<0))
#define IS_SSE_ALIGN(address)				(((Uint32)(address) & 0xF) == 0)

