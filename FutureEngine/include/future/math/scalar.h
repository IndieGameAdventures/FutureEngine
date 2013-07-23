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
*	A scalar class. This class should be used for anything vector calculation
*	instead of using a standard int or float. This is because this class stores
*	itself as a vec4 internally so it can be make use of SIMD if avaliable.
*/

#ifndef FUTURE_MATH_SCALAR_H
#define FUTURE_MATH_SCALAR_H

#include <future/math/type/type.h>

class FutureScalar;
typedef const FutureScalar & FutureScalarArg;

class FutureScalar
{
public:

	inline FutureScalar();
	inline FutureScalar(f32 value);
	inline FutureScalar(u32 value);
	inline FutureScalar(FutureVec4Float value);
	inline FutureScalar(const FutureScalar & value);

	/*****************Binary Operations***********************************/

	/*********************Vec4 Operations***************************/
	inline FutureScalar	Add(FutureVec4Float vec) const;
	inline FutureScalar	Subtract(FutureVec4Float vec) const;
	inline FutureScalar	Multiply(FutureVec4Float vec) const;
	inline FutureScalar	Divide(FutureVec4Float vec) const;

	inline FutureScalar	And(FutureVec4Float vec) const;
	inline FutureScalar	Or(FutureVec4Float vec) const;
	inline FutureScalar	XOr(FutureVec4Float vec) const;

	inline FutureScalar	Min(FutureVec4Float vec) const;
	inline FutureScalar	Max(FutureVec4Float vec) const;
	inline FutureScalar	Clamp(FutureVec4Float min, FutureVec4Float max) const;
		

	inline FutureScalar	AddAndSave(FutureVec4Float vec);
	inline FutureScalar	SubtractAndSave(FutureVec4Float vec);
	inline FutureScalar	MultiplyAndSave(FutureVec4Float vec);
	inline FutureScalar	DivideAndSave(FutureVec4Float vec);

	inline FutureScalar	AndAndSave(FutureVec4Float vec);
	inline FutureScalar	OrAndSave(FutureVec4Float vec);
	inline FutureScalar	XOrAndSave(FutureVec4Float vec);

	inline FutureScalar	MinAndSave(FutureVec4Float vec);
	inline FutureScalar	MaxAndSave(FutureVec4Float vec);
	inline FutureScalar	ClampAndSave(FutureVec4Float min, FutureVec4Float max);


	/*********************Scalar Operations***************************/
	inline FutureScalar	Add(FutureScalarArg vec) const;
	inline FutureScalar	Subtract(FutureScalarArg vec) const;
	inline FutureScalar	Multiply(FutureScalarArg vec) const;
	inline FutureScalar	Divide(FutureScalarArg vec) const;

	inline FutureScalar	And(FutureScalarArg vec) const;
	inline FutureScalar	Or(FutureScalarArg vec) const;
	inline FutureScalar	XOr(FutureScalarArg vec) const;

	inline FutureScalar	Min(FutureScalarArg vec) const;
	inline FutureScalar	Max(FutureScalarArg vec) const;
	inline FutureScalar	Clamp(FutureScalarArg min, FutureScalarArg max) const;
		

	inline FutureScalar	AddAndSave(FutureScalarArg vec);
	inline FutureScalar	SubtractAndSave(FutureScalarArg vec);
	inline FutureScalar	MultiplyAndSave(FutureScalarArg vec);
	inline FutureScalar	DivideAndSave(FutureScalarArg vec);

	inline FutureScalar	AndAndSave(FutureScalarArg vec);
	inline FutureScalar	OrAndSave(FutureScalarArg vec);
	inline FutureScalar	XOrAndSave(FutureScalarArg vec);

	inline FutureScalar	MinAndSave(FutureScalarArg vec);
	inline FutureScalar	MaxAndSave(FutureScalarArg vec);
	inline FutureScalar	ClampAndSave(FutureScalarArg min, FutureScalarArg max);



	/*****************Unary Operations***********************************/
	
	inline FutureScalar	Abs() const;
	inline FutureScalar	Complement() const;
	inline FutureScalar	Negate() const;
	inline FutureScalar	Increment() const;
	inline FutureScalar	Decrement() const;
	inline FutureScalar	Reciprocal() const;
	inline FutureScalar	SquareRoot() const;
	inline FutureScalar	ReciprocalSquareRoot() const;
	inline FutureScalar Lerp(FutureScalarArg to, FutureScalarArg u) const;
	
	inline FutureScalar	AbsAndSave();
	inline FutureScalar	ComplementAndSave();
	inline FutureScalar	NegateAndSave();
	inline FutureScalar	IncrementAndSave();
	inline FutureScalar	DecrementAndSave();
	inline FutureScalar	ReciprocalAndSave();
	inline FutureScalar	SquareRootAndSave();
	inline FutureScalar	ReciprocalSquareRootAndSave();
	inline FutureScalar LerpAndSave(FutureScalarArg to, FutureScalarArg u);


	/*****************Get/Set Operations***********************************/

	inline f32				AsFloat() const;
	inline FutureVec4Float	Vec4() const;

	inline void				Set(f32 value);
	inline void				Set(FutureVec4Float value);
	inline void				Set(FutureScalarArg value);
	


	/***************** Operators ***********************************/

	/********************* Binary ****************/
	
	inline FutureScalar	operator+(FutureVec4Float vec) const;
	inline FutureScalar	operator-(FutureVec4Float vec) const;
	inline FutureScalar	operator*(FutureVec4Float vec) const;
	inline FutureScalar	operator/(FutureVec4Float vec) const;

	inline FutureScalar	operator&(FutureVec4Float vec) const;
	inline FutureScalar	operator|(FutureVec4Float vec) const;
	inline FutureScalar	operator^(FutureVec4Float vec) const;
		
	inline FutureScalar	operator+=(FutureVec4Float vec);
	inline FutureScalar	operator-=(FutureVec4Float vec);
	inline FutureScalar	operator*=(FutureVec4Float vec);
	inline FutureScalar	operator/=(FutureVec4Float vec);

	inline FutureScalar	operator&=(FutureVec4Float vec);
	inline FutureScalar	operator|=(FutureVec4Float vec);
	inline FutureScalar	operator^=(FutureVec4Float vec);
	

	inline FutureScalar	operator+(FutureScalarArg vec) const;
	inline FutureScalar	operator-(FutureScalarArg vec) const;
	inline FutureScalar	operator*(FutureScalarArg vec) const;
	inline FutureScalar	operator/(FutureScalarArg vec) const;

	inline FutureScalar	operator&(FutureScalarArg vec) const;
	inline FutureScalar	operator|(FutureScalarArg vec) const;
	inline FutureScalar	operator^(FutureScalarArg vec) const;
		
	inline FutureScalar	operator+=(FutureScalarArg vec);
	inline FutureScalar	operator-=(FutureScalarArg vec);
	inline FutureScalar	operator*=(FutureScalarArg vec);
	inline FutureScalar	operator/=(FutureScalarArg vec);

	inline FutureScalar	operator&=(FutureScalarArg vec);
	inline FutureScalar	operator|=(FutureScalarArg vec);
	inline FutureScalar	operator^=(FutureScalarArg vec);


	/********************* Unary ****************/

	inline FutureScalar operator~() const;
	inline FutureScalar operator-() const;
	inline FutureScalar operator++();
	inline FutureScalar operator--();


	/********************* Comparison ****************/

	inline bool	operator<(FutureVec4Float vec) const;
	inline bool	operator<=(FutureVec4Float vec) const;
	inline bool	operator>(FutureVec4Float vec) const;
	inline bool	operator>=(FutureVec4Float vec) const;
	inline bool	operator==(FutureVec4Float vec) const;
	inline bool	operator!=(FutureVec4Float vec) const;

	inline bool	operator<(FutureScalarArg vec) const;
	inline bool	operator<=(FutureScalarArg vec) const;
	inline bool	operator>(FutureScalarArg vec) const;
	inline bool	operator>=(FutureScalarArg vec) const;
	inline bool	operator==(FutureScalarArg vec) const;
	inline bool	operator!=(FutureScalarArg vec) const;


	/********************* Assignment ****************/

	inline FutureScalar	operator=(FutureVec4Float vec);
	inline FutureScalar	operator=(FutureScalarArg vec);
	inline FutureScalar	operator=(f32 vec);
	inline FutureScalar	operator=(u32 vec);


	/********************* Casting ****************/

	inline operator f32() const;
	inline operator u32() const;
	inline operator FutureVec4Float() const;
	inline operator bool() const;



	/***************** String Operations ***********************************/

	inline string			ToString() const;
	inline FutureScalar		SetFromString(string str);

	inline operator string() const;



	/***************** Static ***********************************/

	static inline FutureScalar		Parse(string str);

	static const FutureScalar		NEGATIVE_ONE;
	static const FutureScalar		ZERO;
	static const FutureScalar		ONE;
	static const FutureScalar		TWO;
	static const FutureScalar		FOUR;
	static const FutureScalar		HALF;
	static const FutureScalar		TOLERANCE;

	static const FutureScalar		PI;
	static const FutureScalar		HALF_PI;
	static const FutureScalar		QUARTER_PI;
	static const FutureScalar		TWO_PI;
	static const FutureScalar		FOUR_PI;

	static const FutureScalar		SQRT_TWO;
	static const FutureScalar		INVERSE_SQRT_TWO;

	static const FutureScalar		E;
	static const FutureScalar		LOG2E;
	static const FutureScalar		LOG10E;
	static const FutureScalar		LN2;
	static const FutureScalar		LN10;

    
    FUTURE_SCALAR_FLOAT_TYPE    m_vec;
};

#if FUTURE_PLATFORM_WINDOWS
#   include <future/math/windows/scalar_win.inl>
#elif FUTURE_PLATFORM_MAC
#   include <future/math/mac/scalar_mac.inl>
#elif FUTURE_PLATFORM_LINUX
#   include <future/math/linux/scalar_lin.inl>
#elif FUTURE_PLATFORM_ANDROID
#   include <future/math/android/scalar_and.inl>
#else
#   include <future/math/float/scalar_float.inl>
#endif

#endif