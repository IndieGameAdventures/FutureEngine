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
#   error This file should only be included by vector.h
#endif


inline FutureVector3::FutureTemplateVector()
{
    m_vec = {0.f, 0.f, 0.f, 0.f};
}
inline FutureVector3::FutureTemplateVector(f32 value)
{
    m_vec = {value, value, value, 0.f};
}
inline FutureVector3::FutureTemplateVector(FutureVec4Float value)
{
    m_vec = {value.x, value.y, value.z, 0.f};
}
inline FutureVector3::FutureTemplateVector(FutureScalarArg value)
{
    m_vec = {value.AsFloat(), value.AsFloat(), value.AsFloat(), 0.f};
}
inline FutureVector3::FutureTemplateVector(f32 x, f32 y, f32 z, f32 w)
{
    m_vec = {x, y, z, 0.f};
}
inline FutureVector3::FutureTemplateVector(FutureVector2Arg value)
{
    m_vec = {value.X(), value.Y(), 0.f, 0.f};
}
inline FutureVector3::FutureTemplateVector(FutureVector3Arg value)
{
    m_vec = {value.X(), value.Y(), value.Z(), 0.f};
}
inline FutureVector3::FutureTemplateVector(FutureVector4Arg value)
{
    m_vec = {value.X(), value.Y(), value.Z(), 0.f};
}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/

inline FutureVector3	FutureVector3::Add(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x + vec.x,
        m_vec.y + vec.y,
        m_vec.z + vec.z
    };
}
inline FutureVector3	FutureVector3::Subtract(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x - vec.x,
        m_vec.y - vec.y,
        m_vec.z - vec.z
    };
}
inline FutureVector3	FutureVector3::Multiply(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x * vec.x,
        m_vec.y * vec.y,
        m_vec.z * vec.z
    };
}
inline FutureVector3	FutureVector3::Divide(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x / vec.x,
        m_vec.y / vec.y,
        m_vec.z / vec.z
    };
}

inline FutureVector3	FutureVector3::And(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x & vec.x,
        m_vec.y & vec.y,
        m_vec.z & vec.z
    };
}
inline FutureVector3	FutureVector3::Or(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x | vec.x,
        m_vec.y | vec.y,
        m_vec.z | vec.z
    };
}
inline FutureVector3	FutureVector3::XOr(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x ^ vec.x,
        m_vec.y ^ vec.y,
        m_vec.z ^ vec.z
    };
}

inline FutureVector3	FutureVector3::Min(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x < vec.x ? m_vec.x : vec.x,
        m_vec.y < vec.y ? m_vec.y : vec.y,
        m_vec.z < vec.z ? m_vec.z : vec.z
    };
}
inline FutureVector3	FutureVector3::Max(FutureVec4Float vec) const
{
    return (FutureVector3){
        m_vec.x > vec.x ? m_vec.x : vec.x,
        m_vec.y > vec.y ? m_vec.y : vec.y,
        m_vec.z > vec.z ? m_vec.z : vec.z
    };
}
inline FutureVector3	FutureVector3::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return (FutureVector3){
        m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.x ? min.x : m_vec.x),
        m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.y ? min.y : m_vec.y),
        m_vec.z > max.m_vec.z ? max.m_vec.z : (m_vec.z < min.z ? min.z : m_vec.z)
    };
}
		
inline FutureVector3	FutureVector3::AddAndSave(FutureVec4Float vec)
{
    m_vec.x += vec.x;
    m_vec.y += vec.y;
    m_vec.z += vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureVec4Float vec)
{
    m_vec.x -= vec.x;
    m_vec.y -= vec.y;
    m_vec.z -= vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec.x *= vec.x;
    m_vec.y *= vec.y;
    m_vec.z *= vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureVec4Float vec)
{
    m_vec.x /= vec.x;
    m_vec.y /= vec.y;
    m_vec.z /= vec.z;
    return *this;
}

inline FutureVector3	FutureVector3::AndAndSave(FutureVec4Float vec)
{
    m_vec.x &= vec.x;
    m_vec.y &= vec.y;
    m_vec.z &= vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureVec4Float vec)
{
    m_vec.x |= vec.x;
    m_vec.y |= vec.y;
    m_vec.z |= vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureVec4Float vec)
{
    m_vec.x ^= vec.x;
    m_vec.y ^= vec.y;
    m_vec.z ^= vec.z;
    return *this;
}

inline FutureVector3	FutureVector3::MinAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.y;
    m_vec.z = m_vec.z < vec.z ? m_vec.z : vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.y;
    m_vec.z = m_vec.z > vec.z ? m_vec.z : vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec.x = m_vec.x > max.x ? max.x : (m_vec.x < min.x ? min.x : m_vec.x);
    m_vec.y = m_vec.y > max.y ? max.y : (m_vec.y < min.y ? min.y : m_vec.y);
    m_vec.z = m_vec.z > max.z ? max.z : (m_vec.z < min.z ? min.z : m_vec.z);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector3	FutureVector3::Add(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x + vec.m_vec,
        m_vec.y + vec.m_vec,
        m_vec.z + vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Subtract(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x - vec.m_vec,
        m_vec.y - vec.m_vec,
        m_vec.z - vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Multiply(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x * vec.m_vec,
        m_vec.y * vec.m_vec,
        m_vec.z * vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Divide(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x / vec.m_vec,
        m_vec.y / vec.m_vec,
        m_vec.z / vec.m_vec
    };
}
                                         
inline FutureVector3	FutureVector3::And(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x & vec.m_vec,
        m_vec.y & vec.m_vec,
        m_vec.z & vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Or(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x | vec.m_vec,
        m_vec.y | vec.m_vec,
        m_vec.z | vec.m_vec
    };
}
inline FutureVector3	FutureVector3::XOr(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x ^ vec.m_vec,
        m_vec.y ^ vec.m_vec,
        m_vec.z ^ vec.m_vec
    };
}
                                         
inline FutureVector3	FutureVector3::Min(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x < vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y < vec.m_vec ? m_vec.y : vec.m_vec,
        m_vec.z < vec.m_vec ? m_vec.z : vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Max(FutureScalar vec) const
{
    return (FutureVector3){
        m_vec.x > vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y > vec.m_vec ? m_vec.y : vec.m_vec,
        m_vec.z > vec.m_vec ? m_vec.z : vec.m_vec
    };
}
inline FutureVector3	FutureVector3::Clamp(FutureScalar min, FutureScalar max) const
{
    return (FutureVector3){
        m_vec.x > max.m_vec ? max.m_vec : (m_vec.x < min.m_vec ? min.m_vec : m_vec.x),
        m_vec.y > max.m_vec ? max.m_vec : (m_vec.y < min.m_vec ? min.m_vec : m_vec.y),
        m_vec.z > max.m_vec ? max.m_vec : (m_vec.z < min.m_vec ? min.m_vec : m_vec.z)
    };
}
                                         
inline FutureVector3	FutureVector3::AddAndSave(FutureScalar vec)
{
    m_vec.x += vec.m_vec;
    m_vec.y += vec.m_vec;
    m_vec.z += vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureScalar vec)
{
    m_vec.x -= vec.m_vec;
    m_vec.y -= vec.m_vec;
    m_vec.z -= vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureScalar vec)
{
    m_vec.x *= vec.m_vec;
    m_vec.y *= vec.m_vec;
    m_vec.z *= vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureScalar vec)
{
    m_vec.x /= vec.m_vec;
    m_vec.y /= vec.m_vec;
    m_vec.z /= vec.m_vec;
    return *this;
}
                                         
inline FutureVector3	FutureVector3::AndAndSave(FutureScalar vec)
{
    m_vec.x &= vec.m_vec;
    m_vec.y &= vec.m_vec;
    m_vec.z &= vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureScalar vec)
{
    m_vec.x |= vec.m_vec;
    m_vec.y |= vec.m_vec;
    m_vec.z |= vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureScalar vec)
{
    m_vec.x ^= vec.m_vec;
    m_vec.y ^= vec.m_vec;
    m_vec.z ^= vec.m_vec;
    return *this;
}
                                         
inline FutureVector3	FutureVector3::MinAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.m_vec;
    m_vec.z = m_vec.z < vec.z ? m_vec.z : vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.m_vec;
    m_vec.z = m_vec.z > vec.z ? m_vec.z : vec.m_vec;
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureScalar min, FutureScalar max)
{
    m_vec.x = m_vec.x > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.y);
    m_vec.z = m_vec.z > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.z);
    return *this;
}


/*********************Vector Operations***************************/
inline FutureVector3	FutureVector3::Add(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x + vec.m_vec.x,
        m_vec.y + vec.m_vec.y,
        m_vec.z + vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Subtract(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x - vec.m_vec.x,
        m_vec.y - vec.m_vec.y,
        m_vec.z - vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Multiply(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x * vec.m_vec.x,
        m_vec.y * vec.m_vec.y,
        m_vec.z * vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Divide(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x / vec.m_vec.x,
        m_vec.y / vec.m_vec.y,
        m_vec.z / vec.m_vec.z
    };
}
                                                 
inline FutureVector3	FutureVector3::And(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x & vec.m_vec.x,
        m_vec.y & vec.m_vec.y,
        m_vec.z & vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Or(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x | vec.m_vec.x,
        m_vec.y | vec.m_vec.y,
        m_vec.z | vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::XOr(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x ^ vec.m_vec.x,
        m_vec.y ^ vec.m_vec.y,
        m_vec.z ^ vec.m_vec.z
    };
}
                                                 
inline FutureVector3	FutureVector3::Min(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y,
        m_vec.z < vec.m_vec.z ? m_vec.z : vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Max(FutureVector3Arg vec) const
{
    return (FutureVector3){
        m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y,
        m_vec.z > vec.m_vec.z ? m_vec.z : vec.m_vec.z
    };
}
inline FutureVector3	FutureVector3::Clamp(FutureVector3Arg min, FutureVector3Arg max) const
{
    return (FutureVector3){
        m_vec.x > max.x ? max.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x),
        m_vec.y > max.y ? max.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y),
        m_vec.z > max.z ? max.z : (m_vec.z < min.m_vec.z ? min.m_vec.z : m_vec.z)
    };
}
                                                 
inline FutureVector3	FutureVector3::AddAndSave(FutureVector3Arg vec)
{
    m_vec.x += vec.m_vec.x;
    m_vec.y += vec.m_vec.y;
    m_vec.z += vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureVector3Arg vec)
{
    m_vec.x -= vec.m_vec.x;
    m_vec.y -= vec.m_vec.y;
    m_vec.z -= vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureVector3Arg vec)
{
    m_vec.x *= vec.m_vec.x;
    m_vec.y *= vec.m_vec.y;
    m_vec.z *= vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureVector3Arg vec)
{
    m_vec.x /= vec.m_vec.x;
    m_vec.y /= vec.m_vec.y;
    m_vec.z /= vec.m_vec.z;
    return *this;
}
                                             
inline FutureVector3	FutureVector3::AndAndSave(FutureVector3Arg vec)
{
    m_vec.x &= vec.m_vec.x;
    m_vec.y &= vec.m_vec.y;
    m_vec.z &= vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureVector3Arg vec)
{
    m_vec.x |= vec.m_vec.x;
    m_vec.y |= vec.m_vec.y;
    m_vec.z |= vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureVector3Arg vec)
{
    m_vec.x ^= vec.m_vec.x;
    m_vec.y ^= vec.m_vec.y;
    m_vec.z ^= vec.m_vec.z;
    return *this;
}
                                             
inline FutureVector3	FutureVector3::MinAndSave(FutureVector3Arg vec)
{
    m_vec.x = m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    m_vec.z = m_vec.z < vec.m_vec.z ? m_vec.z : vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureVector3Arg vec)
{
    m_vec.x = m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    m_vec.z = m_vec.z > vec.m_vec.z ? m_vec.z : vec.m_vec.z;
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureVector3Arg min, FutureVector3Arg max)
{
    m_vec.x = m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y);
    m_vec.z = m_vec.z > max.m_vec.z ? max.m_vec.z : (m_vec.z < min.m_vec.z ? min.m_vec.z : m_vec.z);
    return *this;
}

inline FutureVector3	FutureVector3::Cross(FutureVector3Arg vec) const
{
    return FutureVector3(m_vec.y * vec.m_vec.z - m_vec.z * vec.m_vec.y,
                         m_vec.z * vec.m_vec.x - m_vec.x * vec.m_vec.z,
                         m_vec.x * vec.m_vec.y - m_vec.y * vec.m_vec.x );
}
inline FutureScalar		FutureVector3::Dot(FutureVector3Arg vec) const
{
	return FutureScalar((m_vec.x * vec.m_vec.x) + (m_vec.y * vec.m_vec.y) + (m_vec.z * vec.m_vec.z));
}
inline FutureScalar		FutureVector3::Projection(FutureVector3Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= vec.Length();
	return dot;
}

inline FutureScalar		FutureVector3::CosAngle(FutureVector3Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= (Length() * vec.Length());
	return dot;
}

/*****************Unary Operations***********************************/

inline FutureVector3	FutureVector3::Abs() const
{
	return FutureVector3(
                         m_vec.x & 0x8FFFFFFF,
                         m_vec.y & 0x8FFFFFFF,
                         m_vec.z & 0x8FFFFFFF);
}

inline FutureScalar 	FutureVector3::Length() const
{
	return LengthSqr().SquareRoot();
}

inline FutureScalar 	FutureVector3::LengthSqr() const
{
	return Dot(*this);
}

inline FutureVector3	FutureVector3::Normalize() const
{
	return Multiply(LengthSqr().ReciprocalSquareRoot());
}

inline FutureVector3	FutureVector3::NormalizeAndSave()
{
	return MultiplyAndSave(LengthSqr().ReciprocalSquareRoot());
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector3::AsVec2() const
{
	return FutureVector2(m_vec);
}
inline FutureVector3	FutureVector3::AsVec3() const
{
	return FutureVector3(m_vec);
}
inline FutureVector4	FutureVector3::AsVec4() const
{
	return *this;
}
inline FutureVec4Float	FutureVector3::Vec4() const
{
	return (FutureVec4Float){m_vec.x, m_vec.y, m_vec.z, 0};
}
    
inline FutureScalar     FutureVector3::Get(u8 i) const
{
	return FutureScalar(((float*)*m_vec)[i]);
}
    
inline FutureScalar     FutureVector3::X() const
{
	return m_vec.x;
}
inline FutureScalar     FutureVector3::Y() const
{
	return m_vec.y;
}
inline FutureScalar     FutureVector3::Z() const
{
	return m_vec.z;
}
inline FutureScalar     FutureVector3::W() const
{
	return 0;
}
    
inline void				FutureVector3::Set(FutureVector2Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
	m_vec.z = 0;
}
inline void				FutureVector3::Set(FutureVector3Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
	m_vec.z = value.m_vec.z;
}
inline void				FutureVector3::Set(FutureVector4Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
	m_vec.z = value.m_vec.z;
}
inline void				FutureVector3::Set(FutureVec4Float value)
{
	m_vec.x = value.x;
	m_vec.y = value.y;
	m_vec.z = value.z;
}
    
inline void				FutureVector3::Set(u8 i, FutureScalarArg value)
{
	((float*)*m_vec)[i] = value.m_vec;
}
	
inline void             FutureVector3::SetX(FutureScalarArg value)
{
    m_vec.x = value.m_vec;
}
inline void             FutureVector3::SetY(FutureScalarArg value)
{
    m_vec.y = value.m_vec;
}
inline void             FutureVector3::SetZ(FutureScalarArg value)
{
    m_vec.z = value.m_vec;
}
inline void             FutureVector3::SetW(FutureScalarArg value)
{
}


/***************** Operators ***********************************/

/********************* Binary ****************/
	
inline FutureVector3	FutureVector3::operator+(FutureVec4Float vec) const
{
    return Add(vec);
}
inline FutureVector3	FutureVector3::operator-(FutureVec4Float vec) const
{
    return Subtract(vec);
}
inline FutureVector3	FutureVector3::operator*(FutureVec4Float vec) const
{
    return Multiply(vec);
}
inline FutureVector3	FutureVector3::operator/(FutureVec4Float vec) const
{
    return Divide(vec);
}
inline FutureVector3	FutureVector3::operator&(FutureVec4Float vec) const
{
    return And(vec);
}
inline FutureVector3	FutureVector3::operator|(FutureVec4Float vec) const
{
    return Or(vec);
}
inline FutureVector3	FutureVector3::operator^(FutureVec4Float vec) const
{
    return XOr(vec);
}
		
inline FutureVector3	FutureVector3::operator+=(FutureVec4Float vec)
{
    return AddAndSave(vec);
}
inline FutureVector3	FutureVector3::operator-=(FutureVec4Float vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector3	FutureVector3::operator*=(FutureVec4Float vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector3	FutureVector3::operator/=(FutureVec4Float vec)
{
    return DivideAndSave(vec);
}

inline FutureVector3	FutureVector3::operator&=(FutureVec4Float vec)
{
    return AndAndSave(vec);
}
inline FutureVector3	FutureVector3::operator|=(FutureVec4Float vec)
{
    return OrAndSave(vec);
}
inline FutureVector3	FutureVector3::operator^=(FutureVec4Float vec)
{
    return XOrAndSave(vec);
}


inline FutureVector3	FutureVector3::operator+(FutureScalarArg vec) const
{
    return Add(vec);
}
inline FutureVector3	FutureVector3::operator-(FutureScalarArg vec) const
{
    return Subtract(vec);
}
inline FutureVector3	FutureVector3::operator*(FutureScalarArg vec) const
{
    return Multiply(vec);
}
inline FutureVector3	FutureVector3::operator/(FutureScalarArg vec) const
{
    return Divide(vec);
}

inline FutureVector3	FutureVector3::operator&(FutureScalarArg vec) const
{
    return And(vec);
}
inline FutureVector3	FutureVector3::operator|(FutureScalarArg vec) const
{
    return Or(vec);
}
inline FutureVector3	FutureVector3::operator^(FutureScalarArg vec) const
{
    return XOr(vec);
}

inline FutureVector3	FutureVector3::operator+=(FutureScalarArg vec)
{
    return AddAndSave(vec);
}
inline FutureVector3	FutureVector3::operator-=(FutureScalarArg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector3	FutureVector3::operator*=(FutureScalarArg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector3	FutureVector3::operator/=(FutureScalarArg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector3	FutureVector3::operator&=(FutureScalarArg vec)
{
    return AndAndSave(vec);
}
inline FutureVector3	FutureVector3::operator|=(FutureScalarArg vec)
{
    return OrAndSave(vec);
}
inline FutureVector3	FutureVector3::operator^=(FutureScalarArg vec)
{
    return XOrAndSave(vec);
}


inline FutureVector3	FutureVector3::operator+(FutureVector3Arg vec) const
{
    return Add(vec);
}
inline FutureVector3	FutureVector3::operator-(FutureVector3Arg vec) const
{
    return Subtract(vec);
}
inline FutureVector3	FutureVector3::operator*(FutureVector3Arg vec) const
{
    return Multiply(vec);
}
inline FutureVector3	FutureVector3::operator/(FutureVector3Arg vec) const
{
    return Divide(vec);
}

inline FutureVector3	FutureVector3::operator&(FutureVector3Arg vec) const
{
    return And(vec);
}
inline FutureVector3	FutureVector3::operator|(FutureVector3Arg vec) const
{
    return Or(vec);
}
inline FutureVector3	FutureVector3::operator^(FutureVector3Arg vec) const
{
    return XOr(vec);
}

inline FutureVector3	FutureVector3::operator+=(FutureVector3Arg vec)
{
    return AddAndSave(vec);
}
inline FutureVector3	FutureVector3::operator-=(FutureVector3Arg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector3	FutureVector3::operator*=(FutureVector3Arg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector3	FutureVector3::operator/=(FutureVector3Arg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector3	FutureVector3::operator&=(FutureVector3Arg vec)
{
    return AndAndSave(vec);
}
inline FutureVector3	FutureVector3::operator|=(FutureVector3Arg vec)
{
    return OrAndSave(vec);
}
inline FutureVector3	FutureVector3::operator^=(FutureVector3Arg vec)
{
    return XOrAndSave(vec);
}

/********************* Comparison ****************/

inline bool	FutureVector3::operator==(FutureVec4Float vec) const
{
    return (m_vec.x == vec.x) && (m_vec.y == vec.y) && (m_vec.z == vec.z) && (0 == vec.w);
}
inline bool	FutureVector3::operator!=(FutureVec4Float vec) const
{
    return (m_vec.x != vec.x) || (m_vec.y != vec.y) || (m_vec.z != vec.z) || (0 != vec.w);
}

inline bool	FutureVector3::operator==(FutureVector3Arg vec) const
{
    return (m_vec.x == vec.m_vec.x) && (m_vec.y == vec.m_vec.y) && (m_vec.z == vec.m_vec.z);
}
inline bool	FutureVector3::operator!=(FutureVector3Arg vec) const
{
    return (m_vec.x != vec.m_vec.x) || (m_vec.y != vec.m_vec.y) || (m_vec.z != vec.m_vec.z);
}


/********************* Assignment ****************/

inline FutureVector3	FutureVector3::operator=(FutureVec4Float vec)
{
    Set(vec);
    return *this;
}
inline FutureVector3	FutureVector3::operator=(FutureVector2Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector3	FutureVector3::operator=(FutureVector3Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector3	FutureVector3::operator=(FutureVector4Arg vec)
{
    Set(vec);
    return *this;
}

/********************* Casting ****************/

inline FutureVector3::operator FutureVec4Float() const
{
	return Vec4();
}
inline FutureVector3::operator FutureVector2() const
{
	return AsVec2();
}
inline FutureVector3::operator FutureVector3() const
{
	return AsVec3();
}
inline FutureVector3::operator FutureVector4() const
{
	return AsVec4();
}
inline FutureVector3::operator bool() const
{
    return (m_vec.x != 0) || (m_vec.y != 0) || (m_vec.z != 0);
}

/***************** String Operations ***********************************/

inline string			FutureVector3::ToString() const
{
    wchar_t str[256];
    swprintf(str, L"Vector3[%f, %f, %f]", m_vec.x, m_vec.y, m_vec.z);
    return str;
}
inline FutureVector3		FutureVector3::SetFromString(string str)
{
    return ZERO;
}

inline FutureVector3::operator string() const
{
    return ToString();
}


/***************** Static ***********************************/

inline FutureVector3		FutureVector3::Parse(string str)
{
    return ZERO;
}

const FutureVector3		NEGATIVE_ONE = FutureVector3(-1.f);
const FutureVector3		ZERO = FutureVector3();
const FutureVector3		ONE = FutureVector3(1.f);

const FutureVector3		AXIS_X = FutureVector3(1.f, 0, 0);
const FutureVector3		AXIS_Y = FutureVector3(0, 1.f, 0);
const FutureVector3		AXIS_Z = FutureVector3(0, 0, 1.f);
const FutureVector3		AXIS_W = FutureVector3(0, 0, 0);
