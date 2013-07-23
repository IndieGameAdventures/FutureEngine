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
*	FutureVec4Float contains functions for dealing with SIMD instructions
*	if they are available. If they are not, then these types default to floating point operations.
*/

#ifndef FUTURE_MATH_VEC4_SSE_H
#define FUTURE_MATH_VEC4_SSE_H

#ifndef FUTURE_MATH_VEC4_H
#	error This file must be included by vec4.h
#endif

#include <immintrin.h>
#include <xmmintrin.h>

#include <future/core/type/type.h>

typedef __declspec(align(16)) __m128 FutureVec4Float;
typedef const FutureVec4Float & FutureVec4FloatArg;

// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
#define	FutureVec4Add(a, b) _mm_add_ps(a, b)

#define	FutureVec4Subtract(a, b) _mm_sub_ps(a, b)
#define	FutureVec4Multiply(a, b) _mm_mul_ps(a, b)
#define	FutureVec4Divide(a, b) _mm_div_ps(a, b)

#define	FutureVec4And(a, b) _mm_and_ps(a, b)
#define	FutureVec4Or(a, b) _mm_or_ps(a, b)
#define	FutureVec4XOr(a, b) _mm_xor_ps(a, b)

#define	FutureVec4Min(a, b) _mm_min_ps(a, b)
#define	FutureVec4Max(a, b) _mm_max_ps(a, b)
#define	FutureVec4Clamp(vec, min, max) _mm_max_ps(_mm_min_ps(vec, max), min)
	
// Complex vector functions
#define	FutureVec4MultiplyAndAdd(vec, mul, add) _mm_add_ps(add, _mm_mul_ps(vec, mul))

inline FutureVec4Float FutureVec4Cross(FutureVec4FloatArg a, FutureVec4FloatArg b)
{
	__m128 sub = _mm_sub_ps(
					_mm_mul_ps(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1))),
					_mm_mul_ps(b, _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1))));
		
	return	_mm_shuffle_ps(sub, sub, _MM_SHUFFLE(3, 0, 2, 1));
}
inline FutureVec4Float FutureVec4Dot(FutureVec4FloatArg a, FutureVec4FloatArg b)
{
	__m128 mul = _mm_mul_ps(a, b);
	__m128 sum0 = _mm_add_ps(_mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2)), mul);
	__m128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2, 3, 0, 1));
	return _mm_add_ps(sum0, sum1);
}

inline FutureVec4Float FutureVec4MatrixMultiply(FutureVec4FloatArg vec, FutureVec4FloatArg row0, FutureVec4FloatArg row1, FutureVec4FloatArg row2, FutureVec4FloatArg row3)
{
	__m128 x = _mm_mul_ps(row0, _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(3, 3, 3, 3)));
	__m128 y = _mm_mul_ps(row1, _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(2, 2, 2, 2)));
	__m128 z = _mm_mul_ps(row2, _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 w = _mm_mul_ps(row3, _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(0, 0, 0, 0)));

	return _mm_add_ps(x, _mm_add_ps(y, _mm_add_ps(z, w)));
}

inline void FutureVec4Transpose(FutureVec4Float & row0, FutureVec4Float & row1, FutureVec4Float & row2, FutureVec4Float & row3)
{
	_MM_TRANSPOSE4_PS(row0, row1, row2, row3);
}

// {[op] a0, [op] a1, [op] a2, [op] a3}
#define	FutureVec4Negate(vec) _mm_sub_ps(_mm_setzero_ps(), vec)
#define	FutureVec4Reciprocal(vec) _mm_rcp_ps(vec)
#define	FutureVec4SquareRoot(vec) _mm_sqrt_ps(vec)
#define	FutureVec4ReciprocalSquareRoot(vec) _mm_rsqrt_ps(vec)


	
// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
#define	FutureVec4CompareLessThan(a, b) _mm_cmplt_ps(a, b)
#define	FutureVec4CompareLessThanOrEqual(a, b) _mm_cmple_ps(a, b)
#define	FutureVec4CompareGreaterThan(a, b) _mm_cmpgt_ps(a, b)
#define	FutureVec4CompareGreaterThanOrEqual(a, b) _mm_cmpge_ps(a, b)
#define	FutureVec4CompareEqual(a, b) _mm_cmpeq_ps(a, b)
#define	FutureVec4CompareNotEqual(a, b) _mm_cmpneq_ps(a, b)

#define FutureVec4CompareResult(result) _mm_movemask_epi8(_mm_castps_si128(result))


// {a1, a2, a3, a0}
#define	FutureVec4RotateLeft(vec, amount) \
	(((amount) % 4) ? (_mm_shuffle_ps(vec, vec, _MM_SHUFFLE((7 - amount) % 4, (6 - amount) % 4, (5 - amount) % 4, (4 - amount) % 4))) : vec)
// {a3, a0, a1, a2}
#define	FutureVec4RotateRight(vec, amount) \
	(((amount) % 4) ? (_mm_shuffle_ps(vec, vec, _MM_SHUFFLE((amount + 3) % 4,(amount + 2) % 4,(amount + 1) % 4,(amount + 0) % 4))) : vec)
// {b0, a0, a1, a2}
#define	FutureVec4Move(a, b) _mm_move_ss(a, b);
// {a0, a1, b0, b1}
#define	FutureVec4Reverse(vec) _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(0, 1, 2, 3))
// {a[x], a[y], b[z], b[w]}
#define	FutureVec4Shuffle(a, b, x, y, z, w) _mm_shuffle_ps(a, b, _MM_SHUFFLE(3 - x, 3 - y, 3 - z, 3 - w))
// {a[x], a[y], a[z], a[w]}
#define	FutureVec4ShuffleOne(vec, x, y, z, w) _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(3 - x, 3 - y, 3 - z, 3 - w))
// {a[i], a[i], a[i], a[i]}
#define	FutureVec4Replicate(vec, i) _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(3 - i, 3 - i, 3 - i, 3 - i))

#define	FutureVec4Get(vec, i) FutureVec4Replicate(vec, i)

inline f32 FutureVec4GetAsFloat(FutureVec4FloatArg vec, u32 i)
{
	f32 r;
	switch(i)
	{
	case 0:
		_mm_store1_ps(&r, FutureVec4RotateRight(vec, 3));
		break;
	case 1:
		_mm_store1_ps(&r, FutureVec4RotateRight(vec, 2));
		break;
	case 2:
		_mm_store1_ps(&r, FutureVec4RotateRight(vec, 1));
		break;
	case 3:
		_mm_store1_ps(&r, FutureVec4RotateRight(vec, 0));
		break;
	default:
		r = 0;
		break;
	}
	return r;
}

#define	FutureVec4GetAll(vec, values) _mm_store_ps(values, m_vec)
	
#define	FutureVec4Set(vec, i, value) _mm_move_ss(FutureVec4RotateRight(vec, i), value)
#define	FutureVec4SetAll(vec, value) vec = _mm_set1_ps(value)

#define FutureVec4CreateOne(value) _mm_set1_ps(value)
#define	FutureVec4CreateVec(x, y, z, w) _mm_setr_ps(x, w, z, w)
#define	FutureVec4CreateEmpty() _mm_setzero_ps()

#endif