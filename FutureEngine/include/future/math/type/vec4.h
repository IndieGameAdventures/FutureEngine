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

#include <future/core/type/platform.h>

#if defined(FUTURE_USES_SSE)
#	include <future/math/type/vec4/vec4_sse.h>
#elif defined(FUTURE_USES_NEON)
#	include <future/math/type/vec4/vec4_neon.h>
#elif defined(FUTURE_USES_ALIVEC)
#	include <future/math/type/vec4/vec4_altivec.h>
#else
#	include <future/math/type/vec4/vec4_float.h>
#endif

namespace FutureMathVectorMasksInternal
{
	__declspec(align(16)) const unsigned int MASK_ALL[] = 	{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	__declspec(align(16)) const unsigned int MASK_YZW[] = 	{ 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	__declspec(align(16)) const unsigned int MASK_XZW[] = 	{ 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF };
	__declspec(align(16)) const unsigned int MASK_XYW[] = 	{ 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF };	
	__declspec(align(16)) const unsigned int MASK_XYZ[] = 	{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };

	__declspec(align(16)) const unsigned int MASK_XY[] = 	{ 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 };	
	__declspec(align(16)) const unsigned int MASK_XZ[] = 	{ 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000 };
	__declspec(align(16)) const unsigned int MASK_XW[] = 	{ 0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF };
	__declspec(align(16)) const unsigned int MASK_YZ[] = 	{ 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };
	__declspec(align(16)) const unsigned int MASK_YW[] = 	{ 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF };
	__declspec(align(16)) const unsigned int MASK_ZW[] = 	{ 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF };

	__declspec(align(16)) const unsigned int MASK_X[] = 	{ 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 };
	__declspec(align(16)) const unsigned int MASK_Y[] = 	{ 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 };
	__declspec(align(16)) const unsigned int MASK_Z[] = 	{ 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 };
	__declspec(align(16)) const unsigned int MASK_W[] = 	{ 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF };
	
	__declspec(align(16)) const unsigned int MASK_NO_SIGN[] = 	{ 0x8FFFFFFF, 0x8FFFFFFF, 0x8FFFFFFF, 0x8FFFFFFF };
}

const FutureVec4Float FUTURE_VECTOR_MASK_ALL = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_ALL));
const FutureVec4Float FUTURE_VECTOR_MASK_XYZ = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XYZ));
const FutureVec4Float FUTURE_VECTOR_MASK_XYW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XYW));
const FutureVec4Float FUTURE_VECTOR_MASK_YZW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_YZW));
const FutureVec4Float FUTURE_VECTOR_MASK_XZW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XZW));
const FutureVec4Float FUTURE_VECTOR_MASK_XY = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XY));
const FutureVec4Float FUTURE_VECTOR_MASK_XZ = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XZ));
const FutureVec4Float FUTURE_VECTOR_MASK_XW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_XW));
const FutureVec4Float FUTURE_VECTOR_MASK_YZ = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_YZ));
const FutureVec4Float FUTURE_VECTOR_MASK_YW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_YW));
const FutureVec4Float FUTURE_VECTOR_MASK_ZW = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_ZW));
const FutureVec4Float FUTURE_VECTOR_MASK_X = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_X));
const FutureVec4Float FUTURE_VECTOR_MASK_Y = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_Y));
const FutureVec4Float FUTURE_VECTOR_MASK_Z = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_Z));
const FutureVec4Float FUTURE_VECTOR_MASK_W = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_W));

const FutureVec4Float FUTURE_VECTOR_MASK_NO_SIGN = (*((FutureVec4Float*)&FutureMathVectorMasksInternal::MASK_NO_SIGN));

#endif