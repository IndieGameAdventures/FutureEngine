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
#   error This file should only be included by scalar.h
#endif

#include <future/math/scalar.h>

#include <wchar.h>

inline FutureScalar::FutureScalar()
: m_vec(FutureVec4CreateEmpty())
{}
inline FutureScalar::FutureScalar(f32 value)
: m_vec(FutureVec4CreateOne(value))
{}
inline FutureScalar::FutureScalar(u32 value)
: m_vec(FutureVec4CreateOne((f32)value))
{}
inline FutureScalar::FutureScalar(FutureVec4Float value)
: m_vec(value)
{}
inline FutureScalar::FutureScalar(const FutureScalar & value)
: m_vec(value.m_vec)
{}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/
inline FutureScalar	FutureScalar::Add(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Add(m_vec, vec));
}
inline FutureScalar	FutureScalar::Subtract(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Subtract(m_vec, vec));
}
inline FutureScalar	FutureScalar::Multiply(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Multiply(m_vec, vec));
}
inline FutureScalar	FutureScalar::Divide(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Divide(m_vec, vec));
}

inline FutureScalar	FutureScalar::And(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4And(m_vec, vec));
}
inline FutureScalar	FutureScalar::Or(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Or(m_vec, vec));
}
inline FutureScalar	FutureScalar::XOr(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4XOr(m_vec, vec));
}

inline FutureScalar	FutureScalar::Min(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Min(m_vec, vec));
}
inline FutureScalar	FutureScalar::Max(FutureVec4Float vec) const
{
    return FutureScalar(FutureVec4Max(m_vec, vec));
}
inline FutureScalar	FutureScalar::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return FutureScalar(FutureVec4Clamp(m_vec, min, max));
}
		
inline FutureScalar	FutureScalar::AddAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Add(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::SubtractAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::DivideAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Divide(m_vec, vec);
    return *this;
}

inline FutureScalar	FutureScalar::AndAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4And(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::OrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Or(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::XOrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4XOr(m_vec, vec);
    return *this;
}

inline FutureScalar	FutureScalar::MinAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Min(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::MaxAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Max(m_vec, vec);
    return *this;
}
inline FutureScalar	FutureScalar::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec = FutureVec4Clamp(m_vec, min, max);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureScalar	FutureScalar::Add(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Add(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Subtract(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Subtract(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Multiply(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Multiply(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Divide(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Divide(m_vec, vec.m_vec));
}

inline FutureScalar	FutureScalar::And(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4And(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Or(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Or(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::XOr(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4XOr(m_vec, vec.m_vec));
}

inline FutureScalar	FutureScalar::Min(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Min(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Max(FutureScalarArg vec) const
{
    return FutureScalar(FutureVec4Max(m_vec, vec.m_vec));
}
inline FutureScalar	FutureScalar::Clamp(FutureScalarArg min, FutureScalarArg max) const
{
    return FutureScalar(FutureVec4Clamp(m_vec, min.m_vec, max.m_vec));
}

inline FutureScalar	FutureScalar::AddAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::SubtractAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::MultiplyAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::DivideAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::AndAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4And(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::OrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::XOrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.m_vec);
    return *this;
}

inline FutureScalar	FutureScalar::MinAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::MaxAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::ClampAndSave(FutureScalarArg min, FutureScalarArg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.m_vec, max.m_vec);
    return *this;
}



/*****************Unary Operations***********************************/

inline FutureScalar	FutureScalar::Abs() const
{
	return And(FUTURE_VECTOR_MASK_NO_SIGN);
}
inline FutureScalar	FutureScalar::Complement() const
{
    return XOr(NEGATIVE_ONE);
}
inline FutureScalar	FutureScalar::Negate() const
{
    return FutureScalar(FutureVec4Negate(m_vec));
}
inline FutureScalar	FutureScalar::Increment() const
{
    return Add(ONE);
}
inline FutureScalar	FutureScalar::Decrement() const
{
    return Subtract(ONE);
}
inline FutureScalar	FutureScalar::Reciprocal() const
{
    return FutureScalar(FutureVec4Reciprocal(m_vec));
}
inline FutureScalar	FutureScalar::SquareRoot() const
{
    return FutureScalar(FutureVec4SquareRoot(m_vec));
}
inline FutureScalar	FutureScalar::ReciprocalSquareRoot() const
{
    return FutureScalar(FutureVec4ReciprocalSquareRoot(m_vec));
}
inline FutureScalar	FutureScalar::Lerp(FutureScalarArg to, FutureScalarArg u) const
{
    return FutureScalar(FutureVec4Add(m_vec, FutureVec4Multiply(FutureVec4Subtract(to.Vec4(), m_vec), u.Vec4())));
}

inline FutureScalar	FutureScalar::AbsAndSave()
{
	return AndAndSave(FUTURE_VECTOR_MASK_NO_SIGN);
}
inline FutureScalar	FutureScalar::ComplementAndSave()
{
    return XOrAndSave(NEGATIVE_ONE);
}
inline FutureScalar	FutureScalar::NegateAndSave()
{
    m_vec = FutureVec4Negate(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::IncrementAndSave()
{
    return AddAndSave(ONE);
}
inline FutureScalar	FutureScalar::DecrementAndSave()
{
    return SubtractAndSave(ONE);
}
inline FutureScalar	FutureScalar::ReciprocalAndSave()
{
    m_vec = FutureVec4Reciprocal(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::SquareRootAndSave()
{
    m_vec = FutureVec4SquareRoot(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::ReciprocalSquareRootAndSave()
{
    m_vec = FutureVec4ReciprocalSquareRoot(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::LerpAndSave(FutureScalarArg to, FutureScalarArg u)
{
    m_vec = FutureVec4Add(m_vec, FutureVec4Multiply(FutureVec4Subtract(to.Vec4(), m_vec), u.Vec4()));
	return *this;
}

inline FutureScalar	FutureScalar::MultiplyAndAdd(FutureScalarArg mul, FutureScalarArg add) const
{
    return FutureScalar(FutureVec4MultiplyAndAdd(m_vec, mul.m_vec, add.m_vec));
}


/*****************Get/Set Operations***********************************/

inline f32				FutureScalar::AsFloat() const
{
    return FutureVec4GetAsFloat(m_vec, 0);
}
inline FutureVec4Float	FutureScalar::Vec4() const
{
    return m_vec;
}

inline void				FutureScalar::Set(f32 value)
{
    FutureVec4SetAll(m_vec, value);
}
inline void				FutureScalar::Set(FutureVec4Float value)
{
    m_vec = FutureVec4Replicate(value, 0);
}
inline void				FutureScalar::Set(FutureScalarArg value)
{
    m_vec = value.m_vec;
}
	


/***************** Operators ***********************************/

/********************* Binary ****************/
	
inline FutureScalar	FutureScalar::operator+(FutureVec4Float vec) const
{
    return Add(vec);
}
inline FutureScalar	FutureScalar::operator-(FutureVec4Float vec) const
{
    return Subtract(vec);
}
inline FutureScalar	FutureScalar::operator*(FutureVec4Float vec) const
{
    return Multiply(vec);
}
inline FutureScalar	FutureScalar::operator/(FutureVec4Float vec) const
{
    return Divide(vec);
}

inline FutureScalar	FutureScalar::operator&(FutureVec4Float vec) const
{
    return And(vec);
}
inline FutureScalar	FutureScalar::operator|(FutureVec4Float vec) const
{
    return Or(vec);
}
inline FutureScalar	FutureScalar::operator^(FutureVec4Float vec) const
{
    return XOr(vec);
}
		
inline FutureScalar	FutureScalar::operator+=(FutureVec4Float vec)
{
    return AddAndSave(vec);
}
inline FutureScalar	FutureScalar::operator-=(FutureVec4Float vec)
{
    return SubtractAndSave(vec);
}
inline FutureScalar	FutureScalar::operator*=(FutureVec4Float vec)
{
    return MultiplyAndSave(vec);
}
inline FutureScalar	FutureScalar::operator/=(FutureVec4Float vec)
{
    return DivideAndSave(vec);
}

inline FutureScalar	FutureScalar::operator&=(FutureVec4Float vec)
{
    return AndAndSave(vec);
}
inline FutureScalar	FutureScalar::operator|=(FutureVec4Float vec)
{
    return OrAndSave(vec);
}
inline FutureScalar	FutureScalar::operator^=(FutureVec4Float vec)
{
    return XOrAndSave(vec);
}


inline FutureScalar	FutureScalar::operator+(FutureScalarArg vec) const
{
    return Add(vec);
}
inline FutureScalar	FutureScalar::operator-(FutureScalarArg vec) const
{
    return Subtract(vec);
}
inline FutureScalar	FutureScalar::operator*(FutureScalarArg vec) const
{
    return Multiply(vec);
}
inline FutureScalar	FutureScalar::operator/(FutureScalarArg vec) const
{
    return Divide(vec);
}

inline FutureScalar	FutureScalar::operator&(FutureScalarArg vec) const
{
    return And(vec);
}
inline FutureScalar	FutureScalar::operator|(FutureScalarArg vec) const
{
    return Or(vec);
}
inline FutureScalar	FutureScalar::operator^(FutureScalarArg vec) const
{
    return XOr(vec);
}

inline FutureScalar	FutureScalar::operator+=(FutureScalarArg vec)
{
    return AddAndSave(vec);
}
inline FutureScalar	FutureScalar::operator-=(FutureScalarArg vec)
{
    return SubtractAndSave(vec);
}
inline FutureScalar	FutureScalar::operator*=(FutureScalarArg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureScalar	FutureScalar::operator/=(FutureScalarArg vec)
{
    return DivideAndSave(vec);
}

inline FutureScalar	FutureScalar::operator&=(FutureScalarArg vec)
{
    return AndAndSave(vec);
}
inline FutureScalar	FutureScalar::operator|=(FutureScalarArg vec)
{
    return OrAndSave(vec);
}
inline FutureScalar	FutureScalar::operator^=(FutureScalarArg vec)
{
    return XOrAndSave(vec);
}


/********************* Unary ****************/

inline FutureScalar FutureScalar::operator~() const
{
    return Complement();
}
inline FutureScalar FutureScalar::operator-() const
{
    return Negate();
}
inline FutureScalar FutureScalar::operator++()
{
    return IncrementAndSave();
}
inline FutureScalar FutureScalar::operator--()
{
    return DecrementAndSave();
}


/********************* Comparison ****************/

inline bool	FutureScalar::operator<(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareLessThan(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator<=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareLessThanOrEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator>(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareGreaterThan(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator>=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareGreaterThanOrEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator==(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator!=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
}


inline bool	FutureScalar::operator<(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareLessThan(m_vec, vec.m_vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator<=(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareLessThanOrEqual(m_vec, vec.m_vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator>(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareGreaterThan(m_vec, vec.m_vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator>=(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareGreaterThanOrEqual(m_vec, vec.m_vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator==(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec.m_vec)) == 0xFFFF;
}
inline bool	FutureScalar::operator!=(FutureScalarArg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec.m_vec)) == 0xFFFF;
}


/********************* Assignment ****************/

inline FutureScalar	FutureScalar::operator=(FutureVec4Float vec)
{
    Set(vec);
    return *this;
}
inline FutureScalar	FutureScalar::operator=(FutureScalarArg vec)
{
    Set(vec);
    return *this;
}
inline FutureScalar	FutureScalar::operator=(f32 vec)
{
    Set(vec);
    return *this;
}
inline FutureScalar	FutureScalar::operator=(u32 vec)
{
    Set((f32)vec);
    return *this;
}


/********************* Casting ****************/

inline FutureScalar::operator f32() const
{
    return AsFloat();
}
inline FutureScalar::operator u32() const
{
    return (u32)AsFloat();
}
inline FutureScalar::operator FutureVec4Float() const
{
    return Vec4();
}
inline FutureScalar::operator bool() const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, ZERO)) == 0xFFFF;
}

/***************** String Operations ***********************************/

inline string			FutureScalar::ToString() const
{
    f32 f = AsFloat();
    wchar_t str[256];
    swprintf(str, L"Scalar[%f, %f, %f, %f]", f, f, f, f);
    return str;
}
inline FutureScalar		FutureScalar::SetFromString(string str)
{
    return ZERO;
}

inline FutureScalar::operator string() const
{
    return ToString();
}


/***************** Static ***********************************/

inline FutureScalar		FutureScalar::Parse(string str)
{
    return ZERO;
}

const FutureScalar		FutureScalar::ZERO = FutureScalar();
const FutureScalar		FutureScalar::ONE = FutureScalar(1.f);
const FutureScalar		FutureScalar::TWO = FutureScalar(2.f);
const FutureScalar		FutureScalar::FOUR = FutureScalar(4.f);
const FutureScalar		FutureScalar::HALF = FutureScalar(0.5f);
const FutureScalar		FutureScalar::TOLERANCE = FutureScalar(0.00000001f);

const FutureScalar		FutureScalar::PI = FutureScalar(3.14159265358979f);
const FutureScalar		FutureScalar::HALF_PI = FutureScalar(1.5707963267949f);
const FutureScalar		FutureScalar::QUARTER_PI = FutureScalar(0.78539816339745f);
const FutureScalar		FutureScalar::TWO_PI = FutureScalar(6.28318530717959f);
const FutureScalar		FutureScalar::FOUR_PI = FutureScalar(12.5663706143592f);

const FutureScalar		FutureScalar::SQRT_TWO = FutureScalar(1.4142135623731f);
const FutureScalar		FutureScalar::INVERSE_SQRT_TWO = FutureScalar(0.70710678118655f);
const FutureScalar		FutureScalar::E = FutureScalar(2.71828182845904f);
const FutureScalar		FutureScalar::LOG2E = FutureScalar(1.44269504088896f);
const FutureScalar		FutureScalar::LOG10E = FutureScalar(0.434294481903252f);
const FutureScalar		FutureScalar::LN2 = FutureScalar(0.434294481903252f);
const FutureScalar		FutureScalar::LN10 = FutureScalar(2.30258509299405f);

