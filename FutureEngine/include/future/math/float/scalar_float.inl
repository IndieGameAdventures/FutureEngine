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

inline FutureScalar::FutureScalar()
: m_vec(0)
{}
inline FutureScalar::FutureScalar(f32 value)
: m_vec(value)
{}
inline FutureScalar::FutureScalar(u32 value)
: m_vec((f32)value)
{}
inline FutureScalar::FutureScalar(FutureVec4Float value)
: m_vec(value.x)
{}
inline FutureScalar::FutureScalar(const FutureScalar & value)
: m_vec(value.m_vec)
{}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/
inline FutureScalar	FutureScalar::Add(FutureVec4Float vec) const
{
    return FutureScalar(m_vec + vec.x);
}
inline FutureScalar	FutureScalar::Subtract(FutureVec4Float vec) const
{
    return FutureScalar(m_vec - vec.x);
}
inline FutureScalar	FutureScalar::Multiply(FutureVec4Float vec) const
{
    return FutureScalar(m_vec * vec.x);
}
inline FutureScalar	FutureScalar::Divide(FutureVec4Float vec) const
{
    return FutureScalar(m_vec / vec.x);
}

inline FutureScalar	FutureScalar::And(FutureVec4Float vec) const
{
    return FutureScalar(m_vec & vec.x);
}
inline FutureScalar	FutureScalar::Or(FutureVec4Float vec) const
{
    return FutureScalar(m_vec | vec.x);
}
inline FutureScalar	FutureScalar::XOr(FutureVec4Float vec) const
{
    return FutureScalar(m_vec ^ vec.x);
}

inline FutureScalar	FutureScalar::Min(FutureVec4Float vec) const
{
    return FutureScalar(m_vec < vec.x ? m_vec : vec.x);
}
inline FutureScalar	FutureScalar::Max(FutureVec4Float vec) const
{
    return FutureScalar(m_vec > vec.x ? m_vec : vec.x);
}
inline FutureScalar	FutureScalar::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return FutureScalar(m_vec < min.x ? min.x : (m_vec > max.x ? max.x : m_vec));
}
		
inline FutureScalar	FutureScalar::AddAndSave(FutureVec4Float vec)
{
    m_vec += vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::SubtractAndSave(FutureVec4Float vec)
{
    m_vec -= vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec *= vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::DivideAndSave(FutureVec4Float vec)
{
    m_vec /= vec.x;
    return *this;
}

inline FutureScalar	FutureScalar::AndAndSave(FutureVec4Float vec)
{
    m_vec &= vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::OrAndSave(FutureVec4Float vec)
{
    m_vec |= vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::XOrAndSave(FutureVec4Float vec)
{
    m_vec ^= vec.x;
    return *this;
}

inline FutureScalar	FutureScalar::MinAndSave(FutureVec4Float vec)
{
    m_vec = m_vec < vec.x ? m_vec : vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::MaxAndSave(FutureVec4Float vec)
{
    m_vec = m_vec > vec.x ? m_vec : vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec = m_vec < min.x ? min.x : (m_vec > max.x ? max.x : m_vec);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureScalar	FutureScalar::Add(FutureScalarArg vec) const
{
    return FutureScalar(m_vec + vec.m_vec);
}
inline FutureScalar	FutureScalar::Subtract(FutureScalarArg vec) const
{
    return FutureScalar(m_vec - vec.m_vec);
}
inline FutureScalar	FutureScalar::Multiply(FutureScalarArg vec) const
{
    return FutureScalar(m_vec * vec.m_vec);
}
inline FutureScalar	FutureScalar::Divide(FutureScalarArg vec) const
{
    return FutureScalar(m_vec / vec.m_vec);
}

inline FutureScalar	FutureScalar::And(FutureScalarArg vec) const
{
    return FutureScalar(m_vec & vec.m_vec);
}
inline FutureScalar	FutureScalar::Or(FutureScalarArg vec) const
{
    return FutureScalar(m_vec | vec.m_vec);
}
inline FutureScalar	FutureScalar::XOr(FutureScalarArg vec) const
{
    return FutureScalar(m_vec ^ vec.m_vec);
}

inline FutureScalar	FutureScalar::Min(FutureScalarArg vec) const
{
    return FutureScalar(m_vec < vec.m_vec ? m_vec : vec.m_vec);
}
inline FutureScalar	FutureScalar::Max(FutureScalarArg vec) const
{
    return FutureScalar(m_vec > vec.m_vec ? m_vec : vec.m_vec);
}
inline FutureScalar	FutureScalar::Clamp(FutureScalarArg min, FutureScalarArg max) const
{
    return FutureScalar(m_vec < min.x ? min.x : (m_vec > max.x ? max.x : m_vec));
}

inline FutureScalar	FutureScalar::AddAndSave(FutureScalarArg vec)
{
    m_vec += vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::SubtractAndSave(FutureScalarArg vec)
{
    m_vec -= vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::MultiplyAndSave(FutureScalarArg vec)
{
    m_vec *= vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::DivideAndSave(FutureScalarArg vec)
{
    m_vec /= vec.m_vec;
    return *this;
}

inline FutureScalar	FutureScalar::AndAndSave(FutureScalarArg vec)
{
    m_vec &= vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::OrAndSave(FutureScalarArg vec)
{
    m_vec |= vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::XOrAndSave(FutureScalarArg vec)
{
    m_vec ^= vec.m_vec;
    return *this;
}

inline FutureScalar	FutureScalar::MinAndSave(FutureScalarArg vec)
{
    m_vec = m_vec < vec.m_vec ? m_vec : vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::MaxAndSave(FutureScalarArg vec)
{
    m_vec = m_vec > vec.m_vec ? m_vec : vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::ClampAndSave(FutureScalarArg min, FutureScalarArg max)
{
    m_vec = m_vec < min.x ? min.x : (m_vec > max.x ? max.x : m_vec);
    return *this;
}



/*****************Unary Operations***********************************/

inline FutureScalar	FutureScalar::Abs() const
{
	return FutureScalar(m_vec & 0x8FFFFFFF);
}
inline FutureScalar	FutureScalar::Complement() const
{
    return FutureScalar(~m_Vec);
}
inline FutureScalar	FutureScalar::Negate() const
{
    return FutureScalar(-m_vec);
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
    return FutureScalar(1.f / m_vec);
}
inline FutureScalar	FutureScalar::SquareRoot() const
{
    return FutureScalar(sqrtf(m_vec));
}
inline FutureScalar	FutureScalar::ReciprocalSquareRoot() const
{
    return FutureScalar(1.f / sqrtf(m_vec));
}
inline FutureScalar	FutureScalar::Lerp(FutureScalarArg to, FutureScalarArg u) const
{
    return FutureScalar(m_vec + ((to.m_vec - m_vec) * u.m_vec));
}

inline FutureScalar	FutureScalar::AbsAndSave()
{
    m_vec &= 0x8FFFFFFF;
	return *this;
}
inline FutureScalar	FutureScalar::ComplementAndSave()
{
    m_vec = ~m_vec;
	return *this;
}
inline FutureScalar	FutureScalar::NegateAndSave()
{
    m_vec = -m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::IncrementAndSave()
{
    ++m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::DecrementAndSave()
{
    --m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::ReciprocalAndSave()
{
    m_vec = 1.f / m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::SquareRootAndSave()
{
    m_vec = sqrtf(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::ReciprocalSquareRootAndSave()
{
    m_vec = 1.0f / sqrtf(m_vec);
    return *this;
}
inline FutureScalar	FutureScalar::LerpAndSave(FutureScalarArg to, FutureScalarArg u)
{
    m_vec += ((to.m_vec - m_vec) * u.m_vec);
	return *this;
}

/*****************Get/Set Operations***********************************/

inline f32				FutureScalar::AsFloat() const
{
    return m_vec;
}
inline FutureVec4Float	FutureScalar::Vec4() const
{
    return (FutureVec4Float){m_vec, m_vec, m_vec, m_vec};
}

inline void				FutureScalar::Set(f32 value)
{
    m_vec = value;
}
inline void				FutureScalar::Set(FutureVec4Float value)
{
    m_vec = value.x;
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
    return m_vec < vec.x;
}
inline bool	FutureScalar::operator<=(FutureVec4Float vec) const
{
    return m_vec <= vec.x;
}
inline bool	FutureScalar::operator>(FutureVec4Float vec) const
{
    return m_vec > vec.x;
}
inline bool	FutureScalar::operator>=(FutureVec4Float vec) const
{
    return m_vec >= vec.x;
}
inline bool	FutureScalar::operator==(FutureVec4Float vec) const
{
    return m_vec == vec.x;
}
inline bool	FutureScalar::operator!=(FutureVec4Float vec) const
{
    return m_vec != vec.x;
}


inline bool	FutureScalar::operator<(FutureScalarArg vec) const
{
    return m_vec < vec.m_vec;
}
inline bool	FutureScalar::operator<=(FutureScalarArg vec) const
{
    return m_vec <= vec.m_vec;
}
inline bool	FutureScalar::operator>(FutureScalarArg vec) const
{
    return m_vec > vec.m_vec;
}
inline bool	FutureScalar::operator>=(FutureScalarArg vec) const
{
    return m_vec >= vec.m_vec;
}
inline bool	FutureScalar::operator==(FutureScalarArg vec) const
{
    return m_vec == vec.m_vec;
}
inline bool	FutureScalar::operator!=(FutureScalarArg vec) const
{
    return m_vec != vec.m_vec;
}


/********************* Assignment ****************/

inline FutureScalar	FutureScalar::operator=(FutureVec4Float vec)
{
    m_vec = vec.x;
    return *this;
}
inline FutureScalar	FutureScalar::operator=(FutureScalarArg vec)
{
    m_vec = vec.m_vec;
    return *this;
}
inline FutureScalar	FutureScalar::operator=(f32 vec)
{
    m_vec = vec;
    return *this;
}
inline FutureScalar	FutureScalar::operator=(u32 vec)
{
    m_vec = (f32)vec;
    return *this;
}


/********************* Casting ****************/

inline FutureScalar::operator f32() const
{
    return m_vec;
}
inline FutureScalar::operator u32() const
{
    return (u32)m_vec;
}
inline FutureScalar::operator FutureVec4Float() const
{
    return Vec4();
}
inline FutureScalar::operator bool() const
{
    return m_vec != 0;
}

/***************** String Operations ***********************************/

inline string			FutureScalar::ToString() const
{
    wchar_t str[256];
    swprintf(str, L"Scalar[%f]", m_vec);
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

