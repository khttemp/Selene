#pragma once


//------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------
#define STM_VERSION_GUID		0x20071101


//------------------------------------------------------------------------------
// ENUM
//------------------------------------------------------------------------------
enum eSTMDrawType
{
	STM_DRAW_NORMAL,
	STM_DRAW_BLEND,
	STM_DRAW_ADD,
	STM_DRAW_ADD_NOALPHA,
	STM_DRAW_SUB,
	STM_DRAW_SUB_NOALPHA,
	STM_DRAW_MULTIPLE,
};


//------------------------------------------------------------------------------
// STRUCT
//------------------------------------------------------------------------------
struct STM_VECTOR3
{
	float x;
	float y;
	float z;
};

struct STM_VECTOR4
{
	float x;
	float y;
	float z;
	float w;
};

struct STM_PLANE
{
	STM_VECTOR3 vNormal;
	float d;
};

struct STM_MATRIX
{
	STM_VECTOR4 x;
	STM_VECTOR4 y;
	STM_VECTOR4 z;
	STM_VECTOR4 w;
};

struct STM_OBBDATA
{
	STM_VECTOR3 vMin;
	STM_VECTOR3 vMax;
};

struct STM_CHUNK
{
	unsigned long Chunk;
	unsigned long Size;
};

struct STM_FILEHEAD
{
	unsigned long Guid;
	unsigned long FirstFrame;
	unsigned long FrameCount;
	unsigned long MeshCount;
	unsigned long MaterialCount;
	float fCellSizeX;
	float fCellSizeY;
	float fCellSizeZ;
	long CellCountX;
	long CellCountY;
	long CellCountZ;
};

struct STM_COLLISIONHEAD
{
	unsigned long FirstFrame;
	unsigned long FrameCount;
	unsigned long CollisionCount;
	float fCellSizeX;
	float fCellSizeY;
	float fCellSizeZ;
	long CellCountX;
	long CellCountY;
	long CellCountZ;
};

struct STM_RENDERDATA
{
	long MaterialId;
	long PolygonStart;
	long PolygonCount;
	long VertexStart;
	long VertexCount;
};

struct STM_FRAMEDATA
{
	long FrameNo[2][2][2];
	long MeshNo;

	STM_OBBDATA OBB;
};

struct STM_MESHDATA
{
	long RenderIdCount;
};

struct STM_SPECULAR
{
	STM_VECTOR3 vSpecular;
	float fRefractive;
	float fRoughly;
};

struct STM_BUMPMAP
{
	float fBumpmapHeight;
	float fParallaxDepth;
};

struct STM_COLLISION_FACE
{
	long Attribute;
	long Index[3];
	STM_PLANE Plane;
};

struct STM_COLLISION_ATTRIBUTE
{
	long Start;
	long Count;
	long Attribute;
};

struct STM_COLLISION_VERTEX
{
	STM_VECTOR3 Position;
	unsigned long Color;
	STM_VECTOR3 Normal;
};

