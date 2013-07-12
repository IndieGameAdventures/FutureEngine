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

inline FutureVec4Float::FutureVec4Float()
{
	m_vec = _mm_setzero_ps();
}
inline FutureVec4Float::FutureVec4Float(f32 set)
{
	m_vec = _mm_set1_ps(set);
}
inline FutureVec4Float::FutureVec4Float(f32 x, f32 y, f32 z, f32 w)
{
	m_vec = _mm_setr_ps(x, y, z, w);
}

// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
inline FutureVec4Float	FutureVec4Float::Add(FutureVec4Float vec)
{
	return _mm_add_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::Subtract(FutureVec4Float vec)
{
	return _mm_sub_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::Multiply(FutureVec4Float vec)
{
	return _mm_mul_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::Divide(FutureVec4Float vec)
{
	return _mm_div_ps(m_vec, vec.m_vec);
}

inline FutureVec4Float FutureVec4Float::And(FutureVec4Float vec)
{
	return _mm_and_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float FutureVec4Float::Or(FutureVec4Float vec)
{
	return _mm_or_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float FutureVec4Float::XOr(FutureVec4Float vec)
{
	return _mm_xor_ps(m_vec, vec.m_vec);
}

inline FutureVec4Float FutureVec4Float::Min(FutureVec4Float vec)
{
	return _mm_min_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float FutureVec4Float::Max(FutureVec4Float vec)
{
	return _mm_max_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float FutureVec4Float::Clamp(FutureVec4Float min, FutureVec4Float max)
{
	return _mm_min_ps(_mm_max_ps(m_vec, min.m_vec), max.m_vec);
}
	
// Complex vector functions
inline FutureVec4Float	FutureVec4Float::MultiplyAndAdd(FutureVec4Float mul, FutureVec4Float add)
{
	return _mm_add_ps(add.m_vec, _mm_mul_ps(m_vec, mul.m_vec));
}

inline FutureVec4Float FutureVec4Float::Cross(FutureVec4Float vec)
{
	__m128 sub = _mm_sub_ps(
					_mm_mul_ps(m_vec, _mm_shuffle_ps(vec.m_vec, vec.m_vec, _MM_SHUFFLE(3, 0, 2, 1))),
					_mm_mul_ps(vec.m_vec, _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(3, 0, 2, 1))));
		
	return	_mm_shuffle_ps(sub, sub, _MM_SHUFFLE(3, 0, 2, 1));
}
inline FutureVec4Float	FutureVec4Float::Dot(FutureVec4Float vec)
{
	__m128 mul = _mm_mul_ps(m_vec, vec.m_vec);
	__m128 sum0 = _mm_add_ps(_mm_shuffle_ps(mul, mul, _MM_SHUFFLE(1, 0, 3, 2)), mul);
	__m128 sum1 = _mm_shuffle_ps(sum0, sum0, _MM_SHUFFLE(2, 3, 0, 1));
	return _mm_add_ps(sum0, sum1);

}

inline FutureVec4Float	FutureVec4Float::MatrixMultiply(FutureVec4Float row0, FutureVec4Float row1, FutureVec4Float row2, FutureVec4Float row3)
{
	__m128 x = _mm_mul_ps(row0.m_vec, _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(3, 3, 3, 3)));
	__m128 y = _mm_mul_ps(row1.m_vec, _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(2, 2, 2, 2)));
	__m128 z = _mm_mul_ps(row2.m_vec, _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 w = _mm_mul_ps(row3.m_vec, _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(0, 0, 0, 0)));

	return _mm_add_ps(x, _mm_add_ps(y, _mm_add_ps(z, w)));
}

// {[op] a0, [op] a1, [op] a2, [op] a3}
inline FutureVec4Float	FutureVec4Float::Negate()
{
	return _mm_sub_ps(_mm_setzero_ps(), m_vec);
}
inline FutureVec4Float FutureVec4Float::Reciprocal()
{
	return _mm_rcp_ps(m_vec);
}
inline FutureVec4Float FutureVec4Float::SquareRoot()
{
	return _mm_sqrt_ps(m_vec);
}
inline FutureVec4Float FutureVec4Float::ReciprocalSquareRoot()
{
	return _mm_rsqrt_ps(m_vec);
}

	
// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
inline FutureVec4Float	FutureVec4Float::CompareLessThan(FutureVec4Float vec)
{
	return _mm_cmplt_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::CompareLessThanOrEqual(FutureVec4Float vec)
{
	return _mm_cmple_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::CompareGreaterThan(FutureVec4Float vec)
{
	return _mm_cmpgt_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::CompareGreaterThanOrEqual(FutureVec4Float vec)
{
	return _mm_cmpge_ps(m_vec, vec.m_vec);
}
inline FutureVec4Float	FutureVec4Float::CompareEqual(FutureVec4Float vec)
{
	return _mm_cmpeq_ps(m_vec, vec.m_vec);

}
inline FutureVec4Float	FutureVec4Float::CompareNotEqual(FutureVec4Float vec)
{
	return _mm_cmpneq_ps(m_vec, vec.m_vec);
}
	
// {a1, a2, a3, a0}
inline FutureVec4Float	FutureVec4Float::RotateLeft(u32 amount)
{
	return (((amount) % 4) ? (_mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE((7 - amount) % 4, (6 - amount) % 4, (5 - amount) % 4, (4 - amount) % 4))) : m_vec);
}
// {a3, a0, a1, a2}
inline FutureVec4Float	FutureVec4Float::RotateRight(u32 amount)
{
	return (((amount) % 4) ? (_mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE((amount + 3) % 4,(amount + 2) % 4,(amount + 1) % 4,(amount + 0) % 4))) : m_vec);
}
// {b0, a0, a1, a2}
inline FutureVec4Float FutureVec4Float::Move(FutureVec4Float vec)
{
	return _mm_move_ss(m_vec, vec.m_vec);
}
// {a3, a2, a1, a0}
inline FutureVec4Float FutureVec4Float::Reverse()
{
	return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(0, 1, 2, 3));
}
// {a[x], a[y], a[z], a[w]}
FutureVec4Float	FutureVec4Float::Shuffle(u8 w, u8 z, u8 y, u8 x)
{
	return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(x, y, z, w));
}
// {a[i], a[i], a[i], a[i]}
inline FutureVec4Float FutureVec4Float::Replicate(u8 i)
{
	return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(i, i, i, i));
}

inline FutureVec4Float FutureVec4Float::Get(u32 i)
{
	return Replicate(i);
}
inline void FutureVec4Float::GetAll(f32 * values)
{
	_mm_store_ps(values, m_vec);
}
inline f32 FutureVec4Float::GetAsFloat(u32 i)
{
	f32 r;
	_mm_store1_ps(&r, RotateRight(i).m_vec);
	return r;
}

inline void FutureVec4Float::Set(u32 i, FutureVec4Float value)
{
	m_vec = _mm_move_ss(RotateRight(i).m_vec, value.m_vec);
}
inline void FutureVec4Float::Set(f32 x, f32 y, f32 z, f32 w)
{
	m_vec = _mm_setr_ps(x, w, z, w);
}
inline void FutureVec4Float::Set(FutureVec4Float vec)
{
	m_vec = vec.m_vec;
}
inline void FutureVec4Float::SetAll(f32 value)
{
	m_vec = _mm_set1_ps(value);
}

inline void FutureVec4Float::Clear()
{
	m_vec = _mm_setzero_ps();
}