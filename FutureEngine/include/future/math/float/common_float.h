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
*	A standard 3 coordinate vector (x, y, z)
*/

#ifndef FUTURE_MATH_COMMON_H
#define FUTURE_MATH_COMMON_H

#include <future/math/type/type.h
#include <future/math/scalar.h>
#include <future/math/vector.h>
#include <future/math/quat.h>>
#include <future/math/matrix.h>


template<typedef T>
inline T FutureMin(const T & t0, const T & t1)
{
    return t0 < t1 : t0 : t1;
}

template<typedef T>
inline T FutureMax(const T & t0, const T & t1)
{
    return t0 > t1 : t0 : t1;
}

template<typedef T>
inline T FutureClamp(const T & t0, const T & min, const T & max)
{
    return t0 < min : min : (t0 > max ? max : t0);
}


inline const FutureScalar       FutureRadToDeg(FutureScalarArg rad);
inline const FutureScalar       FutureDegToRad(FutureScalarArg deg);
inline const f32                FutureRadToDeg(f32 rad);
inline const f32                FutureDegToRad(f32 deg);



inline void                     FutureSinCos(FutureScalarArg scalar, FutureScalar * sin, FutureScalar * cos);
inline const FutureScalar       FutureSin(FutureScalarArg scalar);
inline const FutureScalar       FutureCos(FutureScalarArg scalar);
inline const FutureScalar       FutureTan(FutureScalarArg scalar);
inline const FutureScalar       FutureASin(FutureScalarArg scalar);
inline const FutureScalar       FutureACos(FutureScalarArg scalar);
inline const FutureScalar       FutureATan(FutureScalarArg scalar);


inline const FutureScalar       FutureAngleBetween(FutureVector4Arg vec0, FutureVector4Arg vec1, normalized = false);
inline const FutureScalar       FutureAngleBetweenExact(FutureVector4Arg vec0, FutureVector4Arg vec1, normalized = false);
inline const FutureVector4      FutureClampLength(FutureVector4Arg vec, FutureScalarArg min, FutureScalarArg max);
inline const FutureVector4      FutureCross(FutureVector4Arg vec0, FutureVector4Arg vec1);
inline const FutureScalar       FutureDot(FutureVector4Arg vec0, FutureVector4Arg vec1);
inline const FutureScalar       FutureLength(FutureVector4Arg vec);
inline const FutureScalar       FutureLengthSquare(FutureVector4Arg vec);
inline const FutureScalar       FutureDistance(FutureVector4Arg vec0, FutureVector4Arg vec1);
inline const FutureVector4      FutureNormalize(FutureVector4Arg vec);
inline const FutureVector4      FutureNormalizeSafe(FutureVector4Arg vec);
inline const FutureVector4      FutureReflect(FutureVector4Arg vec, FutureVector4Arg normal);
inline const FutureVector4      FutureTransform(FutureVector4Arg vec, FutureMatrixArg matrix);
inline const FutureVector4      FutureTransform(FutureVector4Arg vec, FutureQuatArg quat);
inline const FutureVector4      FutureSaturate(FutureVector4Arg vec);
inline const FutureVector4      FutureLerp(FutureVector4Arg from, FutureVector4Arg to, FutureScalarArg u);


inline const FutureScalar       FutureAngleBetween(FutureVector3Arg vec0, FutureVector3Arg vec1, normalized = false);
inline const FutureScalar       FutureAngleBetweenExact(FutureVector3Arg vec0, FutureVector3Arg vec1, normalized = false);
inline const FutureVector3      FutureClampLength(FutureVector3Arg vec, FutureScalarArg min, FutureScalarArg max);
inline const FutureVector3      FutureCross(FutureVector3Arg vec0, FutureVector3Arg vec1);
inline const FutureScalar       FutureDot(FutureVector3Arg vec0, FutureVector3Arg vec1);
inline const FutureScalar       FutureLength(FutureVector3Arg vec);
inline const FutureScalar       FutureLengthSquare(FutureVector3Arg vec);
inline const FutureScalar       FutureDistance(FutureVector3Arg vec0, FutureVector3Arg vec1);
inline const FutureVector3      FutureNormalize(FutureVector3Arg vec);
inline const FutureVector3      FutureNormalizeSafe(FutureVector3Arg vec);
inline const FutureVector3      FutureReflect(FutureVector3Arg vec, FutureVector3Arg normal);
inline const FutureVector3      FutureTransform(FutureVector3Arg vec, FutureMatrixArg matrix);
inline const FutureVector3      FutureTransform(FutureVector3Arg vec, FutureQuatArg quat);
inline const FutureVector3      FutureSaturate(FutureVector3Arg vec);
inline const FutureVector3      FutureLerp(FutureVector3Arg from, FutureVector3Arg to, FutureScalarArg u);



inline const FutureScalar       FutureAngleBetween(FutureVector2Arg vec0, FutureVector2Arg vec1, normalized = false);
inline const FutureScalar       FutureAngleBetweenExact(FutureVector2Arg vec0, FutureVector2Arg vec1, normalized = false);
inline const FutureVector2      FutureClampLength(FutureVector2Arg vec, FutureScalarArg min, FutureScalarArg max);
inline const FutureVector3      FutureCross(FutureVector2Arg vec0, FutureVector2Arg vec1);
inline const FutureVector2      FutureDot(FutureVector2Arg vec0, FutureVector2Arg vec1);
inline const FutureVector2      FutureLength(FutureVector2Arg vec);
inline const FutureVector2      FutureLengthSquare(FutureVector2Arg vec);
inline const FutureScalar       FutureDistance(FutureVector2Arg vec0, FutureVector2Arg vec1);
inline const FutureVector2      FutureNormalize(FutureVector2Arg vec);
inline const FutureVector2      FutureNormalizeSafe(FutureVector2Arg vec);
inline const FutureVector2      FutureReflect(FutureVector2Arg vec, FutureVector2Arg normal);
inline const FutureVector2      FutureTransform(FutureVector2Arg vec, FutureMatrixArg matrix);
inline const FutureVector2      FutureTransform(FutureVector2Arg vec, FutureQuatArg quat);
inline const FutureVector2      FutureRotate(FutureVector2Arg vec, FutureScalarArg rad);
inline const FutureVector2      FutureSaturate(FutureVector2Arg vec);
inline const FutureVector2      FutureLerp(FutureVector2Arg from, FutureVector2Arg to, FutureScalarArg u);



inline const FutureQuat         FutureConjugate(FutureQuatArg quat);
inline const FutureScalar       FutureDot(FutureQuatArg quat0, FutureQuatArg quat1);
inline const FutureQuat         FutureInverse(FutureQuatArg quat);
inline const FutureScalar       FutureLength(FutureQuatArg quat);
inline const FutureScalar       FutureLengthSquare(FutureQuatArg quat);
inline const FutureQuat         FutureMultiply(FutureQuatArg quat0, FutureQuatArg quat1);
inline const FutureQuat         FutureNormalize(FutureQuatArg quat);
inline const FutureQuat         FutureNormalizeSafe(FutureQuatArg quat);
inline const FutureQuat         FutureLerp(FutureQuatArg from, FutureQuatArg to, FutureScalarArg u);
inline const FutureQuat         FutureSLerp(FutureQuatArg from, FutureQuatArg to, FutureScalarArg u);



       const FutureMatrix       FutureAffineTransformation(FutureVector3Arg scale, FutureVector3Arg rotOrigin, FutureQuatArg rotation, FutureVector3Arg position);
       const FutureMatrix       Future2DAffineTransformation(FutureVector2Arg scale, FutureVector2Arg rotOrigin, FutureScalarArg rotation, FutureVector2Arg position);
inline const void               FutureDecompose(FutureMatrixArg matrix, FutureVector3 * outScale, FutureQuat * outRotation, FutureVector3 * outPosition);
inline const FutureScalar       FutureDeterminant(FutureMatrixArg matrix);
inline const FutureMatrix       FutureInverse(FutureMatrixArg matrix);
inline const FutureMatrix       FutureLookAtLH(FutureVector3Arg eye, FutureVector3Arg focus, FutureVector3Arg up);
inline const FutureMatrix       FutureLookAtRH(FutureVector3Arg eye, FutureVector3Arg focus, FutureVector3Arg up);
inline const FutureMatrix       FutureLookInLH(FutureVector3Arg eye, FutureVector3Arg direction, FutureVector3Arg up);
inline const FutureMatrix       FutureLookInRH(FutureVector3Arg eye, FutureVector3Arg direction, FutureVector3Arg up);
inline const FutureMatrix       FutureMultiply(FutureMatrixArg matrix0, FutureMatrixArg matrix1);
inline const FutureMatrix       FutureMultiplyTransverse(FutureMatrixArg matrix0, FutureMatrixArg matrix1);
inline const FutureMatrix       FutureOrthographicProjectionLH(f32 width, f32 height, f32 near, f32 far);
inline const FutureMatrix       FutureOrthographicProjectionRH(f32 width, f32 height, f32 near, f32 far);
inline const FutureMatrix       FuturePerspectiveProjectionLH(f32 fov, f32 aspect, f32 near, f32 far);
inline const FutureMatrix       FuturePerspectiveProjectionRH(f32 fov, f32 aspect, f32 near, f32 far);
inline const FutureMatrix       FutureRotateTransformation(FutureQuatArg rotation);
       const FutureMatrix       FutureRotateTransformation(FutureVector3Arg origin, FutureQuatArg rotation);
inline const FutureMatrix       FutureScaleTransformation(FutureVector3Arg scale);
       const FutureMatrix       FutureScaleTransformation(FutureVector3Arg scaleOrigin, FutureQuatArg scaleOrientation, FutureVector3Arg scale);
inline const FutureMatrix       FutureTranslateTransformation(FutureVector3Arg position);
       const FutureMatrix       FutureTransformation(FutureVector3Arg scale, FutureQuatArg rotation, FutureVector3Arg position);
       const FutureMatrix       FutureTransformation(FutureVector3Arg scaleOrigin, FutureQuatArg scaleOrientation, FutureVector3Arg scale, FutureVector3Arg rotOrigin, FutureQuatArg rotation, FutureVector3Arg position);
inline const FutureMatrix       FutureTranspose(FutureMatrixArg matrix);


#endif