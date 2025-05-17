

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Math/Random.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;
using namespace Math;


//-----------------------------------------------------------------------------------
// VARIABLE
//-----------------------------------------------------------------------------------
static const Sint32 M			= 397UL;
static const Sint32 MATRIX_A	= 0x9908B0DFUL;
static const Sint32 UPPER_MASK	= 0x80000000UL;
static const Sint32 LOWER_MASK	= 0x7FFFFFFFUL;


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRandom::CRandom()
{
	Seed( ::timeGetTime() );
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
CRandom::CRandom( Sint32 Param )
{
	Seed( Param );
}


//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRandom::GenerateInt32( void )
{
    Sint32 Mag01[2] = { 0x00000000UL, MATRIX_A };
    Sint32 Param;

    if ( m_MersenneTwisterCount >= N )
	{
        Sint32 kk = 0;

		while ( kk < N - M )
		{
            Param = (m_MersenneTwister[kk] & UPPER_MASK) | (m_MersenneTwister[kk+1] & LOWER_MASK);
            m_MersenneTwister[kk] = m_MersenneTwister[kk + M] ^ (Param >> 1) ^ Mag01[Param & 0x01];

			kk++;
		}

		while ( kk < N - 1 )
		{
            Param = (m_MersenneTwister[kk] & UPPER_MASK) | (m_MersenneTwister[kk + 1] & LOWER_MASK);
            m_MersenneTwister[kk] = m_MersenneTwister[kk + (M - N)] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

			kk++;
		}

		Param = (m_MersenneTwister[N - 1]&UPPER_MASK) | (m_MersenneTwister[0] & LOWER_MASK);
        m_MersenneTwister[N - 1] = m_MersenneTwister[M-1] ^ (Param >> 1) ^ Mag01[Param & 0x00000001UL];

        m_MersenneTwisterCount = 0;
    }
  
    Param = m_MersenneTwister[m_MersenneTwisterCount++];

    /* Tempering */
    Param ^= (Param >> 11);
    Param ^= (Param <<  7) & 0x9D2C5680UL;
    Param ^= (Param << 15) & 0xEFC60000UL;
    Param ^= (Param >> 18);

    return Param;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
void CRandom::Seed( Sint32 Param )
{
    m_MersenneTwister[0] = Param & 0xFFFFFFFFUL;
    for ( m_MersenneTwisterCount = 1; m_MersenneTwisterCount < N; m_MersenneTwisterCount++ )
	{
        m_MersenneTwister[m_MersenneTwisterCount] = (1812433253UL * (m_MersenneTwister[m_MersenneTwisterCount-1] ^ (m_MersenneTwister[m_MersenneTwisterCount-1] >> 30)) + m_MersenneTwisterCount); 
        m_MersenneTwister[m_MersenneTwisterCount] &= 0xFFFFFFFFUL;
    }
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRandom::GetInt32( void )
{
    return GenerateInt32();
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Uint64 CRandom::GetInt64( void )
{
	Uint64 a = GenerateInt32();
	Uint64 b = GenerateInt32();

	return (a << 32) | b;
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRandom::GetFloat32( void )
{
	const Sint32 RANDOM_MAX	= 100000000;

    return toF(GenerateInt32() % (RANDOM_MAX+1)) / toF(RANDOM_MAX);
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Sint32 CRandom::GetInt( Sint32 Min, Sint32 Max )
{
	Sint32 a = (Sint32)(GetInt32() >> 1);

	return Min + (a % (Max + 1 - Min));
}

//-----------------------------------------------------------------------------------
/**
*/
//-----------------------------------------------------------------------------------
Float CRandom::GetFloat( Float Min, Float Max )
{
	Float a = GetFloat32();

	return Min + (a * (Max - Min));
}

