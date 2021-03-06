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

#ifndef FUTURE_MATH_VECTOR_H
#define FUTURE_MATH_VECTOR_H

#include <future/math/type/vec4.h>
#include <future/math/scalar.h>

template<int COUNT>
class FutureTemplateVector;

#define FutureTemplateVectorArg const FutureTemplateVector<COUNT> &

typedef FutureTemplateVector<2> FutureVector2;
typedef FutureTemplateVector<3> FutureVector3;
typedef FutureTemplateVector<4> FutureVector4;

typedef const FutureVector2 & FutureVector2Arg;
typedef const FutureVector3 & FutureVector3Arg;
typedef const FutureVector4 & FutureVector4Arg;

template<int COUNT>
class FutureTemplateVector
{
public:

	inline FutureTemplateVector();
	inline FutureTemplateVector(f32 value);
	inline FutureTemplateVector(f32 x, f32 y, f32 z = 0, f32 w = 0);
	inline FutureTemplateVector(FutureVec4Float value);
	inline FutureTemplateVector(FutureScalarArg value);
	inline FutureTemplateVector(FutureVector2Arg value);
	inline FutureTemplateVector(FutureVector3Arg value);
	inline FutureTemplateVector(FutureVector4Arg value);

	/*****************Binary Operations***********************************/

	/*********************Vec4 Operations***************************/

	inline FutureTemplateVector<COUNT>	Add(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Subtract(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Multiply(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Divide(FutureVec4Float vec) const;

	inline FutureTemplateVector<COUNT>	And(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Or(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	XOr(FutureVec4Float vec) const;

	inline FutureTemplateVector<COUNT>	Min(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Max(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	Clamp(FutureVec4Float min, FutureVec4Float max) const;
		

	inline FutureTemplateVector<COUNT>	AddAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	SubtractAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	MultiplyAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	DivideAndSave(FutureVec4Float vec);

	inline FutureTemplateVector<COUNT>	AndAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	OrAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	XOrAndSave(FutureVec4Float vec);

	inline FutureTemplateVector<COUNT>	MinAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	MaxAndSave(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	ClampAndSave(FutureVec4Float min, FutureVec4Float max);


	/*********************Scalar Operations***************************/

	inline FutureTemplateVector<COUNT>	Add(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Subtract(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Multiply(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Divide(FutureScalarArg vec) const;

	inline FutureTemplateVector<COUNT>	And(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Or(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	XOr(FutureScalarArg vec) const;

	inline FutureTemplateVector<COUNT>	Min(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Max(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	Clamp(FutureScalarArg min, FutureScalarArg max) const;
		

	inline FutureTemplateVector<COUNT>	AddAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	SubtractAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	MultiplyAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	DivideAndSave(FutureScalarArg vec);

	inline FutureTemplateVector<COUNT>	AndAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	OrAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	XOrAndSave(FutureScalarArg vec);

	inline FutureTemplateVector<COUNT>	MinAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	MaxAndSave(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	ClampAndSave(FutureScalarArg min, FutureScalarArg max);


	/*********************Vector Operations ***************************/

	inline FutureTemplateVector<COUNT>	Add(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Subtract(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Multiply(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Divide(FutureTemplateVectorArg vec) const;

	inline FutureTemplateVector<COUNT>	And(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Or(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	XOr(FutureTemplateVectorArg vec) const;

	inline FutureTemplateVector<COUNT>	Min(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Max(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	Clamp(FutureTemplateVectorArg min, FutureTemplateVectorArg max) const;
		

	inline FutureTemplateVector<COUNT>	AddAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	SubtractAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	MultiplyAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	DivideAndSave(FutureTemplateVectorArg vec);

	inline FutureTemplateVector<COUNT>	AndAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	OrAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	XOrAndSave(FutureTemplateVectorArg vec);

	inline FutureTemplateVector<COUNT>	MinAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	MaxAndSave(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	ClampAndSave(FutureTemplateVectorArg min, 
													 FutureTemplateVectorArg max);


	inline FutureTemplateVector<COUNT>	Cross(FutureTemplateVectorArg vec) const;
	inline FutureScalar					Dot(FutureTemplateVectorArg vec) const;
	inline FutureScalar					Projection(FutureTemplateVectorArg vec) const;

	inline FutureScalar					CosAngle(FutureTemplateVectorArg vec) const;


	/*****************Unary Operations***********************************/
	inline FutureTemplateVector<COUNT>	Abs() const;

	inline FutureScalar 				Length() const;
	inline FutureScalar 				LengthSqr() const;

	inline FutureTemplateVector<COUNT>	Normalize() const;
	inline FutureTemplateVector<COUNT>	NormalizeAndSave();


	/*****************Get/Set Operations***********************************/

	inline FutureVector2	AsVec2() const;
	inline FutureVector3	AsVec3() const;
	inline FutureVector4	AsVec4() const;
	inline FutureVec4Float	Vec4() const;
    
    inline FutureScalar     Get(u8 i) const;
    
    inline FutureScalar     X() const;
    inline FutureScalar     Y() const;
    inline FutureScalar     Z() const;
    inline FutureScalar     W() const;
    
	inline void				Set(FutureVector2Arg value);
	inline void				Set(FutureVector3Arg value);
	inline void				Set(FutureVector4Arg value);
	inline void				Set(FutureVec4Float value);
    
	inline void				Set(u8 i, FutureScalarArg value);
	
    inline void             SetX(FutureScalarArg value);
    inline void             SetY(FutureScalarArg value);
    inline void             SetZ(FutureScalarArg value);
    inline void             SetW(FutureScalarArg value);


	/***************** Operators ***********************************/

	/********************* Binary ****************/
	
	inline FutureTemplateVector<COUNT>	operator+(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	operator-(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	operator*(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	operator/(FutureVec4Float vec) const;

	inline FutureTemplateVector<COUNT>	operator&(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	operator|(FutureVec4Float vec) const;
	inline FutureTemplateVector<COUNT>	operator^(FutureVec4Float vec) const;
		
	inline FutureTemplateVector<COUNT>	operator+=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator-=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator*=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator/=(FutureVec4Float vec);

	inline FutureTemplateVector<COUNT>	operator&=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator|=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator^=(FutureVec4Float vec);
	

	inline FutureTemplateVector<COUNT>	operator+(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	operator-(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	operator*(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	operator/(FutureScalarArg vec) const;

	inline FutureTemplateVector<COUNT>	operator&(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	operator|(FutureScalarArg vec) const;
	inline FutureTemplateVector<COUNT>	operator^(FutureScalarArg vec) const;
		
	inline FutureTemplateVector<COUNT>	operator+=(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	operator-=(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	operator*=(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	operator/=(FutureScalarArg vec);

	inline FutureTemplateVector<COUNT>	operator&=(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	operator|=(FutureScalarArg vec);
	inline FutureTemplateVector<COUNT>	operator^=(FutureScalarArg vec);
	
    
	inline FutureTemplateVector<COUNT>	operator+(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	operator-(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	operator*(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	operator/(FutureTemplateVectorArg vec) const;
    
	inline FutureTemplateVector<COUNT>	operator&(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	operator|(FutureTemplateVectorArg vec) const;
	inline FutureTemplateVector<COUNT>	operator^(FutureTemplateVectorArg vec) const;
    
	inline FutureTemplateVector<COUNT>	operator+=(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	operator-=(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	operator*=(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	operator/=(FutureTemplateVectorArg vec);
    
	inline FutureTemplateVector<COUNT>	operator&=(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	operator|=(FutureTemplateVectorArg vec);
	inline FutureTemplateVector<COUNT>	operator^=(FutureTemplateVectorArg vec);


	/********************* Comparison ****************/

	inline bool	operator==(FutureVec4Float vec) const;
	inline bool	operator!=(FutureVec4Float vec) const;
    
	inline bool	operator==(FutureTemplateVectorArg vec) const;
	inline bool	operator!=(FutureTemplateVectorArg vec) const;


	/********************* Assignment ****************/

	inline FutureTemplateVector<COUNT>	operator=(FutureVec4Float vec);
	inline FutureTemplateVector<COUNT>	operator=(FutureVector2Arg vec);
	inline FutureTemplateVector<COUNT>	operator=(FutureVector3Arg vec);
	inline FutureTemplateVector<COUNT>	operator=(FutureVector4Arg vec);

	/********************* Casting ****************/

	inline operator FutureVec4Float() const;
	inline operator FutureVector2() const;
	inline operator FutureVector3() const;
	inline operator FutureVector4() const;
	inline operator bool() const;


	/***************** String Operations ***********************************/

	inline string						ToString() const;
	inline FutureTemplateVector<COUNT>	SetFromString(string str);

	inline operator string() const;

	/***************** Static ***********************************/

	static inline FutureTemplateVector<COUNT>		Parse(string str);
	
	static const FutureTemplateVector<COUNT>		NEGATIVE_ONE;
	static const FutureTemplateVector<COUNT>		ZERO;
	static const FutureTemplateVector<COUNT>		ONE;

	static const FutureTemplateVector<COUNT>		AXIS_X;
	static const FutureTemplateVector<COUNT>		AXIS_Y;
	static const FutureTemplateVector<COUNT>		AXIS_Z;
	static const FutureTemplateVector<COUNT>		AXIS_W;

protected:
	__declspec(align(16)) FutureVec4Float m_vec;
};



#endif