#pragma once


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Class/ClassReference.h"
#include "Class/Common/Object/CBaseObject.h"
#include "Interface/Fiber/IFiberController.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Fiber
{
	struct SFiberData
	{
		IFiber *pFiberInterface;
		void *pFiber;
		Sint32 Next;
	};

	struct SRoutineData
	{
		CFiberController *pContrler;
		SFiberData *pData;
	};

	class CFiberController : public IFiberController, public CBaseObject
	{
	private:
		Bool m_IsRun;
		Sint32 m_FiberMax;
		Sint32 m_FiberMaxCount;
		Sint32 m_FiberRoot;
		Sint32 m_FiberDataId;
		SFiberData *m_pFiberData;
		SRoutineData *m_pRoutineData;

	private:
		static void WINAPI Routine( void *pParam );

	private:
		void UpdateList( void );

	public:
		CFiberController( Sint32 Max );
		~CFiberController();

	public:
		virtual Bool IsInvalid( void ) { return false; }
		virtual Sint32 Release( void ) { return CBaseObject::Release(); }
		virtual Sint32 AddRef( void	)  { return CBaseObject::AddRef(); }
		virtual void Start( void );
		virtual void Exit( void );
		virtual Bool Switch( void );
		virtual Bool Create( Sint32 FiberId, IFiber *pFiber );
	};
}
}
