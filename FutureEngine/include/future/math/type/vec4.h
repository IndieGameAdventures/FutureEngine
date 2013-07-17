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

#endif