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
*	A standard 2 coordinate vector (x, y)
*/

#ifndef FUTURE_MATH_VECTOR_H
#   error This file should only be included by vector.h
#endif


inline FutureVector2::FutureTemplateVector()
{
    m_vec = {0.f, 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(f32 value)
{
    m_vec = {value, value, 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(FutureVec4Float value)
{
    m_vec = {value.x, value.y, 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(FutureScalarArg value)
{
    m_vec = {value.AsFloat(), value.AsFloat(), 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(f32 x, f32 y, f32 z, f32 w)
{
    m_vec = {x, y, 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(FutureVector2Arg value)
{
    m_vec = {value.X(), value.Y(), 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(FutureVector3Arg value)
{
    m_vec = {value.X(), value.Y(), 0.f, 0.f};
}
inline FutureVector2::FutureTemplateVector(FutureVector4Arg value)
{
    m_vec = {value.X(), value.Y(), 0.f, 0.f};
}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/

inline FutureVector2	FutureVector2::Add(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x + vec.x,
        m_vec.y + vec.y
    };
}
inline FutureVector2	FutureVector2::Subtract(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x - vec.x,
        m_vec.y - vec.y
    };
}
inline FutureVector2	FutureVector2::Multiply(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x * vec.x,
        m_vec.y * vec.y
    };
}
inline FutureVector2	FutureVector2::Divide(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x / vec.x,
        m_vec.y / vec.y
    };
}

inline FutureVector2	FutureVector2::And(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x & vec.x,
        m_vec.y & vec.y
    };
}
inline FutureVector2	FutureVector2::Or(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x | vec.x,
        m_vec.y | vec.y
    };
}
inline FutureVector2	FutureVector2::XOr(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x ^ vec.x,
        m_vec.y ^ vec.y
    };
}

inline FutureVector2	FutureVector2::Min(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x < vec.x ? m_vec.x : vec.x,
        m_vec.y < vec.y ? m_vec.y : vec.y
    };
}
inline FutureVector2	FutureVector2::Max(FutureVec4Float vec) const
{
    return (FutureVector2){
        m_vec.x > vec.x ? m_vec.x : vec.x,
        m_vec.y > vec.y ? m_vec.y : vec.y
    };
}
inline FutureVector2	FutureVector2::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return (FutureVector2){
        m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.x ? min.x : m_vec.x),
        m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.y ? min.y : m_vec.y)
    };
}
		
inline FutureVector2	FutureVector2::AddAndSave(FutureVec4Float vec)
{
    m_vec.x += vec.x;
    m_vec.y += vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureVec4Float vec)
{
    m_vec.x -= vec.x;
    m_vec.y -= vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec.x *= vec.x;
    m_vec.y *= vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureVec4Float vec)
{
    m_vec.x /= vec.x;
    m_vec.y /= vec.y;
    return *this;
}

inline FutureVector2	FutureVector2::AndAndSave(FutureVec4Float vec)
{
    m_vec.x &= vec.x;
    m_vec.y &= vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureVec4Float vec)
{
    m_vec.x |= vec.x;
    m_vec.y |= vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureVec4Float vec)
{
    m_vec.x ^= vec.x;
    m_vec.y ^= vec.y;
    return *this;
}

inline FutureVector2	FutureVector2::MinAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec.x = m_vec.x > max.x ? max.x : (m_vec.x < min.x ? min.x : m_vec.x);
    m_vec.y = m_vec.y > max.y ? max.y : (m_vec.y < min.y ? min.y : m_vec.y);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector2	FutureVector2::Add(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x + vec.m_vec,
        m_vec.y + vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Subtract(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x - vec.m_vec,
        m_vec.y - vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Multiply(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x * vec.m_vec,
        m_vec.y * vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Divide(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x / vec.m_vec,
        m_vec.y / vec.m_vec
    };
}
                                         
inline FutureVector2	FutureVector2::And(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x & vec.m_vec,
        m_vec.y & vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Or(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x | vec.m_vec,
        m_vec.y | vec.m_vec
    };
}
inline FutureVector2	FutureVector2::XOr(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x ^ vec.m_vec,
        m_vec.y ^ vec.m_vec
    };
}
                                         
inline FutureVector2	FutureVector2::Min(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x < vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y < vec.m_vec ? m_vec.y : vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Max(FutureScalar vec) const
{
    return (FutureVector2){
        m_vec.x > vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y > vec.m_vec ? m_vec.y : vec.m_vec
    };
}
inline FutureVector2	FutureVector2::Clamp(FutureScalar min, FutureScalar max) const
{
    return (FutureVector2){
        m_vec.x > max.m_vec ? max.m_vec : (m_vec.x < min.m_vec ? min.m_vec : m_vec.x),
        m_vec.y > max.m_vec ? max.m_vec : (m_vec.y < min.m_vec ? min.m_vec : m_vec.y)
    };
}
                                         
inline FutureVector2	FutureVector2::AddAndSave(FutureScalar vec)
{
    m_vec.x += vec.m_vec;
    m_vec.y += vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureScalar vec)
{
    m_vec.x -= vec.m_vec;
    m_vec.y -= vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureScalar vec)
{
    m_vec.x *= vec.m_vec;
    m_vec.y *= vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureScalar vec)
{
    m_vec.x /= vec.m_vec;
    m_vec.y /= vec.m_vec;
    return *this;
}
                                         
inline FutureVector2	FutureVector2::AndAndSave(FutureScalar vec)
{
    m_vec.x &= vec.m_vec;
    m_vec.y &= vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureScalar vec)
{
    m_vec.x |= vec.m_vec;
    m_vec.y |= vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureScalar vec)
{
    m_vec.x ^= vec.m_vec;
    m_vec.y ^= vec.m_vec;
    return *this;
}
                                         
inline FutureVector2	FutureVector2::MinAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.m_vec;
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureScalar min, FutureScalar max)
{
    m_vec.x = m_vec.x > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.y);
    return *this;
}


/*********************Vector Operations***************************/
inline FutureVector2	FutureVector2::Add(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x + vec.m_vec.x,
        m_vec.y + vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Subtract(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x - vec.m_vec.x,
        m_vec.y - vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Multiply(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x * vec.m_vec.x,
        m_vec.y * vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Divide(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x / vec.m_vec.x,
        m_vec.y / vec.m_vec.y,
    };
}
                                                 
inline FutureVector2	FutureVector2::And(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x & vec.m_vec.x,
        m_vec.y & vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Or(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x | vec.m_vec.x,
        m_vec.y | vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::XOr(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x ^ vec.m_vec.x,
        m_vec.y ^ vec.m_vec.y,
    };
}
                                                 
inline FutureVector2	FutureVector2::Min(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Max(FutureVector2Arg vec) const
{
    return (FutureVector2){
        m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y,
    };
}
inline FutureVector2	FutureVector2::Clamp(FutureVector2Arg min, FutureVector2Arg max) const
{
    return (FutureVector2){
        m_vec.x > max.x ? max.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x),
        m_vec.y > max.y ? max.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y),
    };
}
                                                 
inline FutureVector2	FutureVector2::AddAndSave(FutureVector2Arg vec)
{
    m_vec.x += vec.m_vec.x;
    m_vec.y += vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureVector2Arg vec)
{
    m_vec.x -= vec.m_vec.x;
    m_vec.y -= vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureVector2Arg vec)
{
    m_vec.x *= vec.m_vec.x;
    m_vec.y *= vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureVector2Arg vec)
{
    m_vec.x /= vec.m_vec.x;
    m_vec.y /= vec.m_vec.y;
    return *this;
}
                                             
inline FutureVector2	FutureVector2::AndAndSave(FutureVector2Arg vec)
{
    m_vec.x &= vec.m_vec.x;
    m_vec.y &= vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureVector2Arg vec)
{
    m_vec.x |= vec.m_vec.x;
    m_vec.y |= vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureVector2Arg vec)
{
    m_vec.x ^= vec.m_vec.x;
    m_vec.y ^= vec.m_vec.y;
    return *this;
}
                                             
inline FutureVector2	FutureVector2::MinAndSave(FutureVector2Arg vec)
{
    m_vec.x = m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureVector2Arg vec)
{
    m_vec.x = m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureVector2Arg min, FutureVector2Arg max)
{
    m_vec.x = m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y);
    return *this;
}

inline FutureVector2	FutureVector2::Cross(FutureVector2Arg vec) const
{
    return FutureVector2(0.f, 0.f);
}
inline FutureScalar		FutureVector2::Dot(FutureVector2Arg vec) const
{
	return FutureScalar((m_vec.x * vec.m_vec.x) + (m_vec.y * vec.m_vec.y));
}
inline FutureScalar		FutureVector2::Projection(FutureVector2Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= vec.Length();
	return dot;
}

inline FutureScalar		FutureVector2::CosAngle(FutureVector2Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= (Length() * vec.Length());
	return dot;
}

/*****************Unary Operations***********************************/

inline FutureVector2	FutureVector2::Abs() const
{
	return FutureVector2(
                         m_vec.x & 0x8FFFFFFF,
                         m_vec.y & 0x8FFFFFFF);
}

inline FutureScalar 	FutureVector2::Length() const
{
	return LengthSqr().SquareRoot();
}

inline FutureScalar 	FutureVector2::LengthSqr() const
{
	return Dot(*this);
}

inline FutureVector2	FutureVector2::Normalize() const
{
	return Multiply(LengthSqr().ReciprocalSquareRoot());
}

inline FutureVector2	FutureVector2::NormalizeAndSave()
{
	return MultiplyAndSave(LengthSqr().ReciprocalSquareRoot());
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector2::AsVec2() const
{
	return FutureVector2(m_vec);
}
inline FutureVector3	FutureVector2::AsVec3() const
{
	return FutureVector3(m_vec);
}
inline FutureVector4	FutureVector2::AsVec4() const
{
	return *this;
}
inline FutureVec4Float	FutureVector2::Vec4() const
{
	return (FutureVec4Float){m_vec.x, m_vec.y, 0, 0};
}
    
inline FutureScalar     FutureVector2::Get(u8 i) const
{
	return FutureScalar(((float*)*m_vec)[i]);
}
    
inline FutureScalar     FutureVector2::X() const
{
	return m_vec.x;
}
inline FutureScalar     FutureVector2::Y() const
{
	return m_vec.y;
}
inline FutureScalar     FutureVector2::Z() const
{
	return 0;
}
inline FutureScalar     FutureVector2::W() const
{
	return 0;
}
    
inline void				FutureVector2::Set(FutureVector2Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
}
inline void				FutureVector2::Set(FutureVector3Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
}
inline void				FutureVector2::Set(FutureVector4Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
}
inline void				FutureVector2::Set(FutureVec4Float value)
{
	m_vec.x = value.x;
	m_vec.y = value.y;
}
    
inline void				FutureVector2::Set(u8 i, FutureScalarArg value)
{
	((float*)*m_vec)[i] = value.m_vec;
}
	
inline void             FutureVector2::SetX(FutureScalarArg value)
{
    m_vec.x = value.m_vec;
}
inline void             FutureVector2::SetY(FutureScalarArg value)
{
    m_vec.y = value.m_vec;
}
inline void             FutureVector2::SetZ(FutureScalarArg value)
{
}
inline void             FutureVector2::SetW(FutureScalarArg value)
{
}


/***************** Operators ***********************************/

/********************* Binary ****************/
	
inline FutureVector2	FutureVector2::operator+(FutureVec4Float vec) const
{
    return Add(vec);
}
inline FutureVector2	FutureVector2::operator-(FutureVec4Float vec) const
{
    return Subtract(vec);
}
inline FutureVector2	FutureVector2::operator*(FutureVec4Float vec) const
{
    return Multiply(vec);
}
inline FutureVector2	FutureVector2::operator/(FutureVec4Float vec) const
{
    return Divide(vec);
}
inline FutureVector2	FutureVector2::operator&(FutureVec4Float vec) const
{
    return And(vec);
}
inline FutureVector2	FutureVector2::operator|(FutureVec4Float vec) const
{
    return Or(vec);
}
inline FutureVector2	FutureVector2::operator^(FutureVec4Float vec) const
{
    return XOr(vec);
}
		
inline FutureVector2	FutureVector2::operator+=(FutureVec4Float vec)
{
    return AddAndSave(vec);
}
inline FutureVector2	FutureVector2::operator-=(FutureVec4Float vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector2	FutureVector2::operator*=(FutureVec4Float vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector2	FutureVector2::operator/=(FutureVec4Float vec)
{
    return DivideAndSave(vec);
}

inline FutureVector2	FutureVector2::operator&=(FutureVec4Float vec)
{
    return AndAndSave(vec);
}
inline FutureVector2	FutureVector2::operator|=(FutureVec4Float vec)
{
    return OrAndSave(vec);
}
inline FutureVector2	FutureVector2::operator^=(FutureVec4Float vec)
{
    return XOrAndSave(vec);
}


inline FutureVector2	FutureVector2::operator+(FutureScalarArg vec) const
{
    return Add(vec);
}
inline FutureVector2	FutureVector2::operator-(FutureScalarArg vec) const
{
    return Subtract(vec);
}
inline FutureVector2	FutureVector2::operator*(FutureScalarArg vec) const
{
    return Multiply(vec);
}
inline FutureVector2	FutureVector2::operator/(FutureScalarArg vec) const
{
    return Divide(vec);
}

inline FutureVector2	FutureVector2::operator&(FutureScalarArg vec) const
{
    return And(vec);
}
inline FutureVector2	FutureVector2::operator|(FutureScalarArg vec) const
{
    return Or(vec);
}
inline FutureVector2	FutureVector2::operator^(FutureScalarArg vec) const
{
    return XOr(vec);
}

inline FutureVector2	FutureVector2::operator+=(FutureScalarArg vec)
{
    return AddAndSave(vec);
}
inline FutureVector2	FutureVector2::operator-=(FutureScalarArg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector2	FutureVector2::operator*=(FutureScalarArg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector2	FutureVector2::operator/=(FutureScalarArg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector2	FutureVector2::operator&=(FutureScalarArg vec)
{
    return AndAndSave(vec);
}
inline FutureVector2	FutureVector2::operator|=(FutureScalarArg vec)
{
    return OrAndSave(vec);
}
inline FutureVector2	FutureVector2::operator^=(FutureScalarArg vec)
{
    return XOrAndSave(vec);
}


inline FutureVector2	FutureVector2::operator+(FutureVector2Arg vec) const
{
    return Add(vec);
}
inline FutureVector2	FutureVector2::operator-(FutureVector2Arg vec) const
{
    return Subtract(vec);
}
inline FutureVector2	FutureVector2::operator*(FutureVector2Arg vec) const
{
    return Multiply(vec);
}
inline FutureVector2	FutureVector2::operator/(FutureVector2Arg vec) const
{
    return Divide(vec);
}

inline FutureVector2	FutureVector2::operator&(FutureVector2Arg vec) const
{
    return And(vec);
}
inline FutureVector2	FutureVector2::operator|(FutureVector2Arg vec) const
{
    return Or(vec);
}
inline FutureVector2	FutureVector2::operator^(FutureVector2Arg vec) const
{
    return XOr(vec);
}

inline FutureVector2	FutureVector2::operator+=(FutureVector2Arg vec)
{
    return AddAndSave(vec);
}
inline FutureVector2	FutureVector2::operator-=(FutureVector2Arg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector2	FutureVector2::operator*=(FutureVector2Arg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector2	FutureVector2::operator/=(FutureVector2Arg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector2	FutureVector2::operator&=(FutureVector2Arg vec)
{
    return AndAndSave(vec);
}
inline FutureVector2	FutureVector2::operator|=(FutureVector2Arg vec)
{
    return OrAndSave(vec);
}
inline FutureVector2	FutureVector2::operator^=(FutureVector2Arg vec)
{
    return XOrAndSave(vec);
}

/********************* Comparison ****************/

inline bool	FutureVector2::operator==(FutureVec4Float vec) const
{
    return (m_vec.x == vec.x) && (m_vec.y == vec.y) && (0 == vec.z) && (0 == vec.w);
}
inline bool	FutureVector2::operator!=(FutureVec4Float vec) const
{
    return (m_vec.x != vec.x) || (m_vec.y != vec.y) || (0 != vec.z) || (0 != vec.w);
}

inline bool	FutureVector2::operator==(FutureVector2Arg vec) const
{
    return (m_vec.x == vec.m_vec.x) && (m_vec.y == vec.m_vec.y);
}
inline bool	FutureVector2::operator!=(FutureVector2Arg vec) const
{
    return (m_vec.x != vec.m_vec.x) || (m_vec.y != vec.m_vec.y);
}


/********************* Assignment ****************/

inline FutureVector2	FutureVector2::operator=(FutureVec4Float vec)
{
    Set(vec);
    return *this;
}
inline FutureVector2	FutureVector2::operator=(FutureVector2Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector2	FutureVector2::operator=(FutureVector3Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector2	FutureVector2::operator=(FutureVector4Arg vec)
{
    Set(vec);
    return *this;
}

/********************* Casting ****************/

inline FutureVector2::operator FutureVec4Float() const
{
	return Vec4();
}
inline FutureVector2::operator FutureVector2() const
{
	return AsVec2();
}
inline FutureVector2::operator FutureVector3() const
{
	return AsVec3();
}
inline FutureVector2::operator FutureVector4() const
{
	return AsVec4();
}
inline FutureVector2::operator bool() const
{
    return (m_vec.x != 0) || (m_vec.y != 0);
}

/***************** String Operations ***********************************/

inline string			FutureVector2::ToString() const
{
    wchar_t str[256];
    swprintf(str, L"Vector2[%f, %f]", m_vec.x, m_vec.y);
    return str;
}
inline FutureVector2		FutureVector2::SetFromString(string str)
{
    return ZERO;
}

inline FutureVector2::operator string() const
{
    return ToString();
}


/***************** Static ***********************************/

inline FutureVector2		FutureVector2::Parse(string str)
{
    return ZERO;
}

const FutureVector2		NEGATIVE_ONE = FutureVector2(-1.f);
const FutureVector2		ZERO = FutureVector2();
const FutureVector2		ONE = FutureVector2(1.f);

const FutureVector2		AXIS_X = FutureVector2(1.f, 0);
const FutureVector2		AXIS_Y = FutureVector2(0, 1.f);
const FutureVector2		AXIS_Z = FutureVector2(0, 0);
const FutureVector2		AXIS_W = FutureVector2(0, 0);
