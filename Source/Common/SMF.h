#pragma once


//------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------
#define SMF_VERSION_GUID		0x20071101
#define MAX_BONE_COUNT			(40)
#define MAX_NAME_SIZE			(64)


//------------------------------------------------------------------------------
// ENUM
//------------------------------------------------------------------------------
enum eSMFDrawType
{
	SMF_DRAW_NORMAL,
	SMF_DRAW_BLEND,
	SMF_DRAW_ADD,
	SMF_DRAW_ADD_NOALPHA,
	SMF_DRAW_SUB,
	SMF_DRAW_SUB_NOALPHA,
	SMF_DRAW_MULTIPLE,
};


//------------------------------------------------------------------------------
// STRUCT
//------------------------------------------------------------------------------
struct SMF_VECTOR3
{
	float x;
	float y;
	float z;
};

struct SMF_VECTOR4
{
	float x;
	float y;
	float z;
	float w;
};

struct SMF_MATRIX
{
	SMF_VECTOR4 x;
	SMF_VECTOR4 y;
	SMF_VECTOR4 z;
	SMF_VECTOR4 w;
};

struct SMF_PLANE
{
	SMF_VECTOR3 vNormal;
	float d;
};

struct SMF_OBBDATA
{
	SMF_VECTOR3 vCenter;
	SMF_VECTOR3 vAxis[3];
	float fLength[3];
};

struct SMF_CHUNK
{
	long Chunk;
	long Size;
};

struct SMF_FILEHEAD
{
	unsigned long Guid;
	long MeshCount;
	long FrameCount;
	long AnimationSetCount;
};

struct SMF_FRAMEDATA
{
	SMF_MATRIX mTransform;
	char Name[MAX_NAME_SIZE];
	long MeshNo;
	long ParentFrameNo;
};

struct SMF_ANIMATIONSETDATA
{
	char Name[MAX_NAME_SIZE];
	long AnimationCount;
	long LastTime;
};

struct SMF_ANIMATIONDATA
{
	long TargetFrame;
	long KeyMaxScale;
	long KeyMaxRotate;
	long KeyMaxTranslate;
};

struct SMF_MESHDATA
{
	char Name[MAX_NAME_SIZE];
	long MaterialCount;
};

struct SMF_BONEDATA
{
	SMF_MATRIX mBoneOffset;
	long FrameNo;
};

struct SMF_MATERIAL
{
	char Name[MAX_NAME_SIZE];
	long PolygonStart;
	long PolygonCount;
	long VertexStart;
	long VertexCount;
};

struct SMF_SPECULAR
{
	SMF_VECTOR3 vSpecular;
	float fRefractive;
	float fRoughly;
};

struct SMF_BUMPMAP
{
	float fParallaxDepth;
};

struct SMF_ANIMATIONKEY_SCALE
{
	long Time;
	float x;
	float y;
	float z;
};

struct SMF_ANIMATIONKEY_ROTATE
{
	long Time;
	float x;
	float y;
	float z;
	float w;
};

struct SMF_ANIMATIONKEY_TRANSLATE
{
	long Time;
	float x;
	float y;
	float z;
};

struct SMF_COLLISION_FACE
{
	long Attribute;
	long Index[3];
	SMF_PLANE Plane;
};

struct SMF_COLLISION_ATTRIBUTE
{
	long Start;
	long Count;
	long Attribute;
};

struct SMF_COLLISIONVERTEX
{
	SMF_VECTOR3 Position;
	unsigned long Color;
	SMF_VECTOR3 Normal;
};
