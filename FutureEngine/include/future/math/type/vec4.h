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

#include <future/core/type/type.h>
#include <future/core/object/threadsafeobject.h>

class FutureVec4Float
{
public:

	FutureVec4Float();
	FutureVec4Float(f32 set);
	FutureVec4Float(f32 x, f32 y, f32 z, f32 w);

	// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
	FutureVec4Float	Add(FutureVec4Float vec);
	FutureVec4Float	Subtract(FutureVec4Float vec);
	FutureVec4Float	Multiply(FutureVec4Float vec);
	FutureVec4Float	Divide(FutureVec4Float vec);

	FutureVec4Float And(FutureVec4Float vec);
	FutureVec4Float Or(FutureVec4Float vec);
	FutureVec4Float XOr(FutureVec4Float vec);

	FutureVec4Float Min(FutureVec4Float vec);
	FutureVec4Float Max(FutureVec4Float vec);
	FutureVec4Float Clamp(FutureVec4Float min, FutureVec4Float max);
	
	// Complex vector functions
	FutureVec4Float	MultiplyAndAdd(FutureVec4Float mul, FutureVec4Float add);
	FutureVec4Float Cross(FutureVec4Float vec);
	FutureVec4Float	Dot(FutureVec4Float vec);
	FutureVec4Float	MatrixMultiply(FutureVec4Float row0, FutureVec4Float row1, FutureVec4Float row2, FutureVec4Float row3);

	// {[op] a0, [op] a1, [op] a2, [op] a3}
	FutureVec4Float	Negate();
	FutureVec4Float Reciprocal();
	FutureVec4Float SquareRoot();
	FutureVec4Float ReciprocalSquareRoot();

	
	// {a0 [op] b0, a1 [op] b1, a2 [op] b2, a3 [op] b3}
	FutureVec4Float	CompareLessThan(FutureVec4Float vec);
	FutureVec4Float	CompareLessThanOrEqual(FutureVec4Float vec);
	FutureVec4Float	CompareGreaterThan(FutureVec4Float vec);
	FutureVec4Float	CompareGreaterThanOrEqual(FutureVec4Float vec);
	FutureVec4Float	CompareEqual(FutureVec4Float vec);
	FutureVec4Float	CompareNotEqual(FutureVec4Float vec);
	
	// {a1, a2, a3, a0}
	FutureVec4Float	RotateLeft(u32 amount);
	// {a3, a0, a1, a2}
	FutureVec4Float	RotateRight(u32 amount);
	// {b0, a0, a1, a2}
	FutureVec4Float Move(FutureVec4Float a, FutureVec4Float b);
	// {a3, a2, a1, a0}
	FutureVec4Float Reverse();
	// {a[x], a[y], a[z], a[w]}
	FutureVec4Float	Shuffle(u8 x, u8 y, u8 z, u8 w);
	// {a[i], a[i], a[i], a[i]}
	FutureVec4Float Replicate(u8 i);

	f32				Get(u32 i);
	void			GetAll(f32 * values);
	FutureVec4Float GetAsVector(u32 i);

	void			Set(u32 i, f32 value);
	void			Set(f32 x, f32 y, f32 z, f32 w);
	void			Set(FutureVec4Float vec);
	void			SetAll(f32 value);

	void			Clear();
};

#if defined(FUTURE_USES_SSE)
//#	include <future/math/type/vec4/vec4_sse.h>
#elif defined(FUTURE_USES_NEON)
#	include <future/math/type/vec4/vec4_neon.h>
#elif defined(FUTURE_USES_ALIVEC)
#	include <future/math/type/vec4/vec4_altivec.h>
#else
#	include <future/math/type/vec4/vec4_float.h>
#endif

#endif