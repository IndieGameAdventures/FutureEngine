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
*	FutureVec4Float and FutureVec4Int contain functions for dealing with SIMD instructions
*	if they are available. If they are not, then these types default to floating point operations.
*/

#ifndef FUTURE_MATH_VEC4_H
#define FUTURE_MATH_VEC4_H

#if defined(FUTURE_USES_SSE)
#	include <immintrin.h>
#	include <xmmintrin.h>
#endif

#include <future/core/type/type.h>
#include <future/core/object/threadsafeobject.h>

class FutureVec4Float;
typedef const FutureVec4Float & FutureVec4FloatArg;

class FutureVec4Float
{
public:

	FutureVec4Float();
	FutureVec4Float(f32 set);
	FutureVec4Float(f32 x, f32 y, f32 z, f32 w);
	FutureVec4Float(const FutureVec4Float & arg);

	// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
	FutureVec4Float	Add(FutureVec4FloatArg vec) const;
	FutureVec4Float	Subtract(FutureVec4FloatArg vec) const;
	FutureVec4Float	Multiply(FutureVec4FloatArg vec) const;
	FutureVec4Float	Divide(FutureVec4FloatArg vec) const;

	FutureVec4Float And(FutureVec4FloatArg vec) const;
	FutureVec4Float Or(FutureVec4FloatArg vec) const;
	FutureVec4Float XOr(FutureVec4FloatArg vec) const;

	FutureVec4Float Min(FutureVec4FloatArg vec) const;
	FutureVec4Float Max(FutureVec4FloatArg vec) const;
	FutureVec4Float Clamp(FutureVec4FloatArg min, FutureVec4FloatArg max) const;
	
	// Complex vector functions
	FutureVec4Float	MultiplyAndAdd(FutureVec4FloatArg mul, FutureVec4FloatArg add) const;
	FutureVec4Float Cross(FutureVec4FloatArg vec) const;
	FutureVec4Float	Dot(FutureVec4FloatArg vec) const;
	FutureVec4Float	MatrixMultiply(FutureVec4FloatArg row0, FutureVec4FloatArg row1, FutureVec4FloatArg row2, FutureVec4FloatArg row3) const;

	// {[op] a0, [op] a1, [op] a2, [op] a3}
	FutureVec4Float	Negate() const;
	FutureVec4Float Reciprocal() const;
	FutureVec4Float SquareRoot() const;
	FutureVec4Float ReciprocalSquareRoot() const;

	
	// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
	FutureVec4Float	CompareLessThan(FutureVec4FloatArg vec) const;
	FutureVec4Float	CompareLessThanOrEqual(FutureVec4FloatArg vec) const;
	FutureVec4Float	CompareGreaterThan(FutureVec4FloatArg vec) const;
	FutureVec4Float	CompareGreaterThanOrEqual(FutureVec4FloatArg vec) const;
	FutureVec4Float	CompareEqual(FutureVec4FloatArg vec) const;
	FutureVec4Float	CompareNotEqual(FutureVec4FloatArg vec) const;
	
	// {a1, a2, a3, a0}
	FutureVec4Float	RotateLeft(u32 amount) const;
	// {a3, a0, a1, a2}
	FutureVec4Float	RotateRight(u32 amount) const;
	// {b0, a0, a1, a2}
	FutureVec4Float Move(FutureVec4FloatArg vec) const;
	// {a3, a2, a1, a0}
	FutureVec4Float Reverse() const;
	// {a[x], a[y], a[z], a[w]}
	FutureVec4Float	Shuffle(u8 x, u8 y, u8 z, u8 w) const;
	// {a[i], a[i], a[i], a[i]}
	FutureVec4Float Replicate(u8 i) const;

	FutureVec4Float	Get(u32 i) const;
	f32				GetAsFloat(u32 i) const; //! Expensive!
	void			GetAll(f32 * values) const;
	
	void			Set(u32 i, FutureVec4FloatArg value);
	void			Set(f32 x, f32 y, f32 z, f32 w);
	void			Set(FutureVec4FloatArg vec);
	void			SetAll(f32 value);

	void			Clear();
	
#if defined(FUTURE_USES_SSE)

	FutureVec4Float operator=(__m128 vec)
	{
		m_vec = vec;
		return *this;
	}

	FutureVec4Float(__m128 vec)
	{
		m_vec = vec;
	}
	__declspec(align(16)) __m128	m_vec;
#elif defined(FUTURE_USES_NEON)
#elif defined(FUTURE_USES_ALIVEC)
#else
#endif
};

#if defined(FUTURE_USES_SSE)
#	include <future/math/type/vec4/vec4_sse.inl>
#elif defined(FUTURE_USES_NEON)
#	include <future/math/type/vec4/vec4_neon.inl>
#elif defined(FUTURE_USES_ALIVEC)
#	include <future/math/type/vec4/vec4_altivec.inl>
#else
#	include <future/math/type/vec4/vec4_float.inl>
#endif

#endif