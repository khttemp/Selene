#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Platform/Render/Shader/ShaderBase.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	enum eTechniqueEffectType
	{
		TECHNIQUE_EFFECT_DEPTH,
		TECHNIQUE_EFFECT_DEPTH_NORMAL,
		TECHNIQUE_EFFECT_VELOCITY_SIMPLE,
		TECHNIQUE_EFFECT_VELOCITY,
		TECHNIQUE_EFFECT_SHADOWMAP,
		TECHNIQUE_EFFECT_SHADOW_PROJECTION,
		TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE,
		TECHNIQUE_EFFECT_SHADOW_PROJECTION_SHAPE_TEXTURE,
		TECHNIQUE_EFFECT_MAX,
	};
}
