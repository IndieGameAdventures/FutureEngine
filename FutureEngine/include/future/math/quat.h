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
*	A Quaternion used for rotation
*/

#ifndef FUTURE_MATH_QUAT_H
#define FUTURE_MATH_QUAT_H

#include <future/math/type/vec4.h>
#include <future/math/scalar.h>
#include <future/math/vector.h>
#include <math.h>

class FutureQuat;
typedef const FutureQuat & FutureQuatArg;

class FutureQuat
{
public:

	inline FutureQuat();
	inline FutureQuat(f32 x, f32 y, f32 z, f32 w);
	inline FutureQuat(FutureVector3Arg axis, f32 rotation);
	inline FutureQuat(FutureVector4Arg axis, f32 rotation);
	inline FutureQuat(FutureVec4Float quat);
	inline FutureQuat(FutureVector4Arg quat);
	inline FutureQuat(FutureVector3Arg euler);
	inline FutureQuat(FutureScalarArg xRot, FutureScalarArg yRot, FutureScalarArg zRot);
	inline FutureQuat(f32 xRot, f32 yRot, f32 zRot);
	inline FutureQuat(const FutureQuat & quat);

	/*****************Binary Operations***********************************/


	/*********************Scalar Operations***************************/

	inline FutureQuat	Multiply(FutureScalarArg vec) const;
	inline FutureQuat	Divide(FutureScalarArg vec) const;

	inline FutureQuat	MultiplyAndSave(FutureScalarArg vec);
	inline FutureQuat	DivideAndSave(FutureScalarArg vec);

	/*********************Quat Operations ***************************/

	inline FutureQuat	Add(FutureQuatArg vec) const;
	inline FutureQuat	Subtract(FutureQuatArg vec) const;
	inline FutureQuat	Multiply(FutureQuatArg vec) const;

	inline FutureQuat	AddAndSave(FutureQuatArg vec);
	inline FutureQuat	SubtractAndSave(FutureQuatArg vec);
	inline FutureQuat	MultiplyAndSave(FutureQuatArg vec);

	inline FutureScalar	Dot(FutureQuatArg vec) const;

	/*****************Unary Operations***********************************/

	inline FutureQuat	Conjugate() const;
	inline FutureQuat	ConjugateAndSave();

	inline FutureQuat	Normalize() const;
	inline FutureQuat	NormalizeAndSave();


	/*****************Get/Set Operations***********************************/

	inline FutureVector3	AsEuler() const;
	inline FutureVector4	AsVec4() const;
	inline void				AsAxisAngle(FutureVector3 * axis, FutureScalar * angle);
	inline FutureVec4Float	Vec4() const;
    inline FutureScalar     Get(u8 i) const;
    
    inline FutureScalar     X() const;
    inline FutureScalar     Y() const;
    inline FutureScalar     Z() const;
    inline FutureScalar     W() const;
	
	inline FutureScalar     x() const {return X();}
    inline FutureScalar     y() const {return Y();}
    inline FutureScalar     z() const {return Z();}
    inline FutureScalar     w() const {return W();}
    
	inline void				SetEuler(FutureVector3Arg value);
	inline void				Set(FutureVector4Arg value);
	inline void				Set(FutureVec4Float value);
	inline void				Set(FutureVector3Arg axis, FutureScalar angle);
    
	inline void				Set(u8 i, FutureScalarArg value);
	
    inline void             SetX(FutureScalarArg value);
    inline void             SetY(FutureScalarArg value);
    inline void             SetZ(FutureScalarArg value);
    inline void             SetW(FutureScalarArg value);


	/***************** Operators ***********************************/

	/********************* Binary ****************/

	inline FutureQuat	operator*(FutureScalarArg scale) const;
	inline FutureQuat	operator/(FutureScalarArg scale) const;

	inline FutureQuat	operator*=(FutureScalarArg scale);
	inline FutureQuat	operator/=(FutureScalarArg scale);

	inline FutureQuat	operator+(FutureQuatArg quat) const;
	inline FutureQuat	operator-(FutureQuatArg quat) const;
	inline FutureQuat	operator*(FutureQuatArg quat) const;
    
	inline FutureQuat	operator+=(FutureQuatArg quat);
	inline FutureQuat	operator-=(FutureQuatArg quat);
	inline FutureQuat	operator*=(FutureQuatArg quat);


	/********************* Comparison ****************/

	inline bool	operator==(FutureVec4Float vec) const;
	inline bool	operator!=(FutureVec4Float vec) const;
    
	inline bool	operator==(FutureQuatArg quat) const;
	inline bool	operator!=(FutureQuatArg quat) const;


	/********************* Assignment ****************/

	inline FutureQuat	operator=(FutureVec4Float vec);
	inline FutureQuat	operator=(FutureVector2Arg vec);
	inline FutureQuat	operator=(FutureVector3Arg vec);
	inline FutureQuat	operator=(FutureVector4Arg vec);

	/********************* Casting ****************/

	inline operator FutureVec4Float() const;
	inline operator FutureVector2() const;
	inline operator FutureVector3() const;
	inline operator FutureVector4() const;
	inline operator bool() const;


	/***************** String Operations ***********************************/

	inline string						ToString() const;
	inline FutureQuat	SetFromString(string str);

	inline operator string() const;

	/***************** Static ***********************************/

	static inline FutureQuat		Parse(string str);
	
	static const FutureQuat		ZERO;
	static const FutureQuat		IDENTITY;

	static const FutureQuat		AXIS_X;
	static const FutureQuat		AXIS_Y;
	static const FutureQuat		AXIS_Z;

protected:
	__declspec(align(16)) FutureVec4Float m_vec;
};



#endif