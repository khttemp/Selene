#pragma once


namespace Selene
{
	class CCore;
	class CGraphicCard;
	class CBaseList;

	namespace Renderer
	{
		class CRender;
		class CDepthTextureMgr;
		class CTextureMgr;
		class CRenderObjectMgr;
		class CBaseTexture;
		class CDepthTexture;
		class CTexture;
		class CCubeTexture;
		class CDepthTexture;
		class CTargetTexture;
		class CTextureInterface;
		class CVertexBuffer;
		class CIndexBuffer;
		class CVertexLayout;
		class CPostEffect;
		class COcclusion;
		class CCollision;

		namespace Shader
		{
			class CShader;
		}

		namespace Object
		{
			class CPrimitive2DBaseMgr;
			class CPrimitive3DBaseMgr;
			class CPoint2D;
			class CPoint3D;
			class CLine2D;
			class CLine3D;
			class CPrimitive2D;
			class CPrimitive3D;
			class CSprite2D;
			class CSprite3D;
			class CParticle;
			class CFontSprite2D;
			class CFontSprite3D;
			class CModelMgr;
			class CMapModelMgr;
			class CMapFrame;
			class CMapMesh;
			class CMapMaterial;
			class CFrame;
			class CMesh;
			class CAnimationData;
			class CMaterial;
			class CAnimationController;
			class CModel;
			class CMapMesh;
			class CMapModel;
			class CCollisionController;
		}
	}

	namespace Fiber
	{
		class CFiber;
		class CFiberController;
	};

	namespace Peripheral
	{
		class CInput;
		class CMouse;
		class CKeyboard;
		class CJoystick;
		class CInputController;
	}

	namespace File
	{
		class CResourceFile;
		class CFile;
		class CFileManager;
	}

	namespace Sound
	{
		class CSound;
		class CStreamSound;
	}

	namespace Dynamics
	{
		class CRigidModel;
		class CRigidBody;
		class CContactPoint;
		class CSimulationWorld;
	}

	namespace Scene
	{
		class CActorObject;
		class CCamera;
		class CSceneManagerBase;
		class CInstanceModelControllerObject;
		class CCustomizedSceneRenderObject;
	}

	namespace Network
	{
		class CNetworkManager;
		class CServerTCP;
		class CSocketTCP;
		class CServerClientTCP;
	}
}

