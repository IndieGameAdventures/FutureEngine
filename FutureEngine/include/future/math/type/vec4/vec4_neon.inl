/*!
*	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
*
*	Thank you for taking a look at my code. If you like it, please click
*	the donation button at the bottom of the sidebar on my blog. Thanks!
*
*	Licensed under the Apache License, Version 2.0 (the "License");
*	you may not use this file except in compliance with the License.
*	You may obtain a copy of the License at
*
*		http://www.apache.org/licenses/LICENSE-2.0
*
*	Unless required by applicable law or agreed to in writing, software
*	distributed under the License is distributed on an "AS IS" BASIS,
*	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*	See the License for the specific language governing permissions and
*	limitations under the License.
*
*/

/*
*	
*	
*/
#	include <immintrin.h>
#	include <xmmintrin.h>
#include <future/math/type/vec4.h>

typedef __m128 f128;

FutureVec4Float::FutureVec4Float()
{
	m_vec = _mm_setzero_ps();
}
FutureVec4Float::FutureVec4Float(f32 set)
{

}
FutureVec4Float::FutureVec4Float(f32 x, f32 y, f32 z, f32 w)
{

}

// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
FutureVec4Float	FutureVec4Float::Add(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::Subtract(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::Multiply(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::Divide(FutureVec4Float vec)
{

}

FutureVec4Float FutureVec4Float::And(FutureVec4Float vec)
{

}
FutureVec4Float FutureVec4Float::Or(FutureVec4Float vec)
{

}
FutureVec4Float FutureVec4Float::XOr(FutureVec4Float vec)
{

}

FutureVec4Float FutureVec4Float::Min(FutureVec4Float vec)
{

}
FutureVec4Float FutureVec4Float::Max(FutureVec4Float vec)
{

}
FutureVec4Float FutureVec4Float::Clamp(FutureVec4Float min, FutureVec4Float max)
{

}
	
// Complex vector functions
FutureVec4Float	FutureVec4Float::MultiplyAndAdd(FutureVec4Float mul, FutureVec4Float add)
{

}
FutureVec4Float FutureVec4Float::Cross(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::Dot(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::MatrixMultiply(FutureVec4Float row0, FutureVec4Float row1, FutureVec4Float row2, FutureVec4Float row3)
{

}

// {[op] a0, [op] a1, [op] a2, [op] a3}
FutureVec4Float	FutureVec4Float::Negate()
{

}
FutureVec4Float FutureVec4Float::Reciprocal()
{

}
FutureVec4Float FutureVec4Float::SquareRoot()
{

}
FutureVec4Float FutureVec4Float::ReciprocalSquareRoot()
{

}

	
// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
FutureVec4Float	FutureVec4Float::CompareLessThan(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::CompareLessThanOrEqual(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::CompareGreaterThan(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::CompareGreaterThanOrEqual(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::CompareEqual(FutureVec4Float vec)
{

}
FutureVec4Float	FutureVec4Float::CompareNotEqual(FutureVec4Float vec)
{

}
	
// {a1, a2, a3, a0}
FutureVec4Float	FutureVec4Float::RotateLeft(u32 amount)
{

}
// {a3, a0, a1, a2}
FutureVec4Float	FutureVec4Float::RotateRight(u32 amount)
{

}
// {b0, a0, a1, a2}
FutureVec4Float FutureVec4Float::Move(FutureVec4Float a, FutureVec4Float b)
{

}
// {a3, a2, a1, a0}
FutureVec4Float FutureVec4Float::Reverse()
{

}
// {a[x], a[y], a[z], a[w]}
FutureVec4Float	FutureVec4Float::Shuffle(u8 x, u8 y, u8 z, u8 w)
{

}
// {a[i], a[i], a[i], a[i]}
FutureVec4Float FutureVec4Float::Replicate(u8 i)
{

}

f32 FutureVec4Float::Get(u32 i)
{

}
void FutureVec4Float::GetAll(f32 * values)
{

}
FutureVec4Float FutureVec4Float::GetAsVector(u32 i)
{

}

void FutureVec4Float::Set(u32 i, f32 value)
{

}
void FutureVec4Float::Set(f32 x, f32 y, f32 z, f32 w)
{

}
void FutureVec4Float::Set(FutureVec4Float vec)
{

}
void FutureVec4Float::SetAll(f32 value)
{

}

void FutureVec4Float::Clear()
{
	m_vec = _mm_setzero_ps();
}

#define _MM_INIT4( p_r0, p_r1, p_r2, p_r3 )		_mm_setr_ps( p_r0, p_r1, p_r2, p_r3 )

#define _MM_INIT3( p_r0, p_r1, p_r2 )			_mm_setr_ps( p_r0, p_r1, p_r2, 0.f )

#define _MM_INIT1( p_r )						_mm_set1_ps( p_r )



#define _MM_ADD( p_v1, p_v2 )	_mm_add_ps( p_v1, p_v2 )

#define _MM_SUB( p_v1, p_v2 )	_mm_sub_ps( p_v1, p_v2 )

#define _MM_MUL( p_v1, p_v2 )	_mm_mul_ps( p_v1, p_v2 )

#define _MM_DIV( p_v1, p_v2 )	_mm_div_ps( p_v1, p_v2 )

#define _MM_NEG( p_v )			_MM_SUB( _mm_setzero_ps(), p_v )



#define _MM_CMPLT_SEP( p_v1, p_v2 )		_mm_cmplt_ps( p_v1, p_v2 )

#define _MM_CMPLE_SEP( p_v1, p_v2 )		_mm_cmple_ps( p_v1, p_v2 )

#define _MM_CMPGT_SEP( p_v1, p_v2 )		_mm_cmpgt_ps( p_v1, p_v2 )

#define _MM_CMPGE_SEP( p_v1, p_v2 )		_mm_cmpge_ps( p_v1, p_v2 )

#define _MM_CMPEQ_SEP( p_v1, p_v2 )		_mm_cmpeq_ps( p_v1, p_v2 )

#define _MM_CMPNEQ_SEP( p_v1, p_v2 ) 	_mm_cmpneq_ps( p_v1, p_v2 )


#define _MM_CMPLT_ONE( p_v1, p_v2 )		(_mm_comilt_ss( p_v1, p_v2 ) == 0x1)

#define _MM_CMPLE_ONE( p_v1, p_v2 )		(_mm_comile_ss( p_v1, p_v2 ) == 0x1)

#define _MM_CMPGT_ONE( p_v1, p_v2 )		(_mm_comigt_ss( p_v1, p_v2 ) == 0x1)

#define _MM_CMPGE_ONE( p_v1, p_v2 )		(_mm_comige_ss( p_v1, p_v2 ) == 0x1)

#define _MM_CMPEQ_ONE( p_v1, p_v2 )		(_mm_comieq_ss( p_v1, p_v2 ) == 0x1)

#define _MM_CMPNEQ_ONE( p_v1, p_v2 ) 	(_mm_comineq_ss( p_v1, p_v2 ) == 0x1)


static inline bool _MM_CVT_TO_BOOL( f128 p_v )
{
	return  p_v.m128_f32[0] != 0x0 &&
			p_v.m128_f32[1] != 0x0 &&
			p_v.m128_f32[2] != 0x0 &&
			p_v.m128_f32[3] != 0x0;
}

#define _MM_ROT_R(p_v, p_i)	\
	(((p_i)%4) ? (_mm_shuffle_ps((p_v),(p_v), _MM_SHUFFLE(((p_i)+3)%4,((p_i)+2)%4,((p_i)+1)%4,((p_i)+0)%4))) : (p_v))

#define _MM_ROT_L(p_v, p_i)	\
	(((p_i)%4) ? (_mm_shuffle_ps((p_v),(p_v), _MM_SHUFFLE((7-(p_i))%4,(6-(p_i))%4,(5-(p_i))%4,(4-(p_i))%4))) : (p_v))

#define _MM_GET( p_v, p_i ) \
	_mm_shuffle_ps( p_v, p_v, _MM_SHUFFLE( p_i, p_i, p_i, p_i ) )

#define _MM_GET_ONE( p_r, p_v, p_i ) \
	_mm_store_ss( &p_r, _MM_ROT_R( p_v, p_i ))

#define _MM_SET( p_v1, p_v2, p_i ) \
	switch( p_i )\
	{ \
	case 0: \
		p_v1 = _MM_ROT_R( p_v1, 0 ); \
		p_v1 = _mm_move_ss( p_v1, p_v2 ); \
		p_v1 = _MM_ROT_L( p_v1, 0 ); \
		break; \
	case 1: \
		p_v1 = _MM_ROT_R( p_v1, 1 ); \
		p_v1 = _mm_move_ss( p_v1, p_v2 ); \
		p_v1 = _MM_ROT_L( p_v1, 1 ); \
		break; \
	case 2: \
		p_v1 = _MM_ROT_R( p_v1, 2 ); \
		p_v1 = _mm_move_ss( p_v1, p_v2 ); \
		p_v1 = _MM_ROT_L( p_v1, 2 ); \
		break; \
	case 3: \
		p_v1 = _MM_ROT_R( p_v1, 3 ); \
		p_v1 = _mm_move_ss( p_v1, p_v2 ); \
		p_v1 = _MM_ROT_L( p_v1, 3 ); \
		break; \
	}

#define _MM_RCP( p_v ) _mm_rcp_ps( p_v )
#define _MM_SQRT( p_v ) _mm_sqrt_ps( p_v )
#define _MM_RSQRT( p_v ) _mm_rsqrt_ps( p_v )


#ifndef SSE_4_1
static inline f128 _MM_DOT( f128 p_0, f128 p_1, const int mask )
{
	f128 t_v = _MM_MUL( p_0, p_1 );

	float tmp0 = (mask & 0x10) ? t_v.m128_f32[0] : +0.0f;
	float tmp1 = (mask & 0x20) ? t_v.m128_f32[1] : +0.0f;
	float tmp2 = (mask & 0x30) ? t_v.m128_f32[2] : +0.0f;
	float tmp3 = (mask & 0x40) ? t_v.m128_f32[3] : +0.0f;

	float tmp4 = tmp0 + tmp1 + tmp2 + tmp3;

	return _MM_INIT4(	(mask & 0x01) ? tmp4 : +0.0f, 
						(mask & 0x02) ? tmp4 : +0.0f,
						(mask & 0x04) ? tmp4 : +0.0f,
						(mask & 0x08) ? tmp4 : +0.0f );
}

#else
#define _MM_DOT( p_0, p_1, mask ) _mm_dp_ps( p_0, p_1, mask );
#endif