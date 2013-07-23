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

#include <future/math/type/type.h>

struct FutureVec4Float
{
    f32 x, y, z, w;
}
typedef const FutureVec4Float & FutureVec4FloatArg;

#define FUTURE_SCALAR_FLOAT_TYPE   f32

#endif