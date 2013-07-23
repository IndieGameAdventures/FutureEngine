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
*	A standard 4 coordinate vector (x, y, z, w)
*/

#ifndef FUTURE_MATH_VECTOR_H
#   error This file should only be included by vector.h
#endif

inline FutureVector4::FutureTemplateVector()
{
    m_vec = (FutureVec4Float){0.f, 0.f, 0.f, 0.f};
}
inline FutureVector4::FutureTemplateVector(f32 value)
{
    m_vec = (FutureVec4Float){value, value, value, value};
}
inline FutureVector4::FutureTemplateVector(FutureVec4Float value)
: m_vec(value)
{}
inline FutureVector4::FutureTemplateVector(FutureScalarArg value)
{
    m_vec = (FutureVec4Float){value.AsFloat(), value.AsFloat(), value.AsFloat(), value.AsFloat()};
}
inline FutureVector4::FutureTemplateVector(f32 x, f32 y, f32 z, f32 w)
{
    m_vec = (FutureVec4Float){x, y, z, w};
}
inline FutureVector4::FutureTemplateVector(FutureVector2Arg value)
{
    m_vec = (FutureVec4Float){value.X(), value.Y(), 0.f, 0.f};
}
inline FutureVector4::FutureTemplateVector(FutureVector3Arg value)
{
    m_vec = (FutureVec4Float){value.X(), value.Y(), value.Z(), 0.f};
}
inline FutureVector4::FutureTemplateVector(FutureVector4Arg value)
: m_vec(value.Vec4())
{}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/

inline FutureVector4	FutureVector4::Add(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x + vec.x,
        m_vec.y + vec.y,
        m_vec.z + vec.z,
        m_vec.w + vec.w
    };
}
inline FutureVector4	FutureVector4::Subtract(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x - vec.x,
        m_vec.y - vec.y,
        m_vec.z - vec.z,
        m_vec.w - vec.w
    };
}
inline FutureVector4	FutureVector4::Multiply(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x * vec.x,
        m_vec.y * vec.y,
        m_vec.z * vec.z,
        m_vec.w * vec.w
    };
}
inline FutureVector4	FutureVector4::Divide(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x / vec.x,
        m_vec.y / vec.y,
        m_vec.z / vec.z,
        m_vec.w / vec.w
    };
}

inline FutureVector4	FutureVector4::And(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x & vec.x,
        m_vec.y & vec.y,
        m_vec.z & vec.z,
        m_vec.w & vec.w
    };
}
inline FutureVector4	FutureVector4::Or(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x | vec.x,
        m_vec.y | vec.y,
        m_vec.z | vec.z,
        m_vec.w | vec.w
    };
}
inline FutureVector4	FutureVector4::XOr(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x ^ vec.x,
        m_vec.y ^ vec.y,
        m_vec.z ^ vec.z,
        m_vec.w ^ vec.w
    };
}

inline FutureVector4	FutureVector4::Min(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x < vec.x ? m_vec.x : vec.x,
        m_vec.y < vec.y ? m_vec.y : vec.y,
        m_vec.z < vec.z ? m_vec.z : vec.z,
        m_vec.w < vec.w ? m_vec.w : vec.w
    };
}
inline FutureVector4	FutureVector4::Max(FutureVec4Float vec) const
{
    return (FutureVector4){
        m_vec.x > vec.x ? m_vec.x : vec.x,
        m_vec.y > vec.y ? m_vec.y : vec.y,
        m_vec.z > vec.z ? m_vec.z : vec.z,
        m_vec.w > vec.w ? m_vec.w : vec.w
    };
}
inline FutureVector4	FutureVector4::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return (FutureVector4){
        m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.x ? min.x : m_vec.x),
        m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.y ? min.y : m_vec.y),
        m_vec.z > max.m_vec.z ? max.m_vec.z : (m_vec.z < min.z ? min.z : m_vec.z),
        m_vec.w > max.m_vec.w ? max.m_vec.w : (m_vec.w < min.w ? min.w : m_vec.w)
    };
}
		
inline FutureVector4	FutureVector4::AddAndSave(FutureVec4Float vec)
{
    m_vec.x += vec.x;
    m_vec.y += vec.y;
    m_vec.z += vec.z;
    m_vec.w += vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureVec4Float vec)
{
    m_vec.x -= vec.x;
    m_vec.y -= vec.y;
    m_vec.z -= vec.z;
    m_vec.w -= vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec.x *= vec.x;
    m_vec.y *= vec.y;
    m_vec.z *= vec.z;
    m_vec.w *= vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureVec4Float vec)
{
    m_vec.x /= vec.x;
    m_vec.y /= vec.y;
    m_vec.z /= vec.z;
    m_vec.w /= vec.w;
    return *this;
}

inline FutureVector4	FutureVector4::AndAndSave(FutureVec4Float vec)
{
    m_vec.x &= vec.x;
    m_vec.y &= vec.y;
    m_vec.z &= vec.z;
    m_vec.w &= vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureVec4Float vec)
{
    m_vec.x |= vec.x;
    m_vec.y |= vec.y;
    m_vec.z |= vec.z;
    m_vec.w |= vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureVec4Float vec)
{
    m_vec.x ^= vec.x;
    m_vec.y ^= vec.y;
    m_vec.z ^= vec.z;
    m_vec.w ^= vec.w;
    return *this;
}

inline FutureVector4	FutureVector4::MinAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.y;
    m_vec.z = m_vec.z < vec.z ? m_vec.z : vec.z;
    m_vec.w = m_vec.w < vec.w ? m_vec.w : vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureVec4Float vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.x;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.y;
    m_vec.z = m_vec.z > vec.z ? m_vec.z : vec.z;
    m_vec.w = m_vec.w > vec.w ? m_vec.w : vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec.x = m_vec.x > max.x ? max.x : (m_vec.x < min.x ? min.x : m_vec.x);
    m_vec.y = m_vec.y > max.y ? max.y : (m_vec.y < min.y ? min.y : m_vec.y);
    m_vec.z = m_vec.z > max.z ? max.z : (m_vec.z < min.z ? min.z : m_vec.z);
    m_vec.w = m_vec.w > max.w ? max.w : (m_vec.w < min.w ? min.w : m_vec.w);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector4	FutureVector4::Add(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x + vec.m_vec,
        m_vec.y + vec.m_vec,
        m_vec.z + vec.m_vec,
        m_vec.w + vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Subtract(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x - vec.m_vec,
        m_vec.y - vec.m_vec,
        m_vec.z - vec.m_vec,
        m_vec.w - vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Multiply(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x * vec.m_vec,
        m_vec.y * vec.m_vec,
        m_vec.z * vec.m_vec,
        m_vec.w * vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Divide(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x / vec.m_vec,
        m_vec.y / vec.m_vec,
        m_vec.z / vec.m_vec,
        m_vec.w / vec.m_vec
    };
}
                                         
inline FutureVector4	FutureVector4::And(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x & vec.m_vec,
        m_vec.y & vec.m_vec,
        m_vec.z & vec.m_vec,
        m_vec.w & vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Or(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x | vec.m_vec,
        m_vec.y | vec.m_vec,
        m_vec.z | vec.m_vec,
        m_vec.w | vec.m_vec
    };
}
inline FutureVector4	FutureVector4::XOr(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x ^ vec.m_vec,
        m_vec.y ^ vec.m_vec,
        m_vec.z ^ vec.m_vec,
        m_vec.w ^ vec.m_vec
    };
}
                                         
inline FutureVector4	FutureVector4::Min(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x < vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y < vec.m_vec ? m_vec.y : vec.m_vec,
        m_vec.z < vec.m_vec ? m_vec.z : vec.m_vec,
        m_vec.w < vec.m_vec ? m_vec.w : vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Max(FutureScalar vec) const
{
    return (FutureVector4){
        m_vec.x > vec.m_vec ? m_vec.x : vec.m_vec,
        m_vec.y > vec.m_vec ? m_vec.y : vec.m_vec,
        m_vec.z > vec.m_vec ? m_vec.z : vec.m_vec,
        m_vec.w > vec.m_vec ? m_vec.w : vec.m_vec
    };
}
inline FutureVector4	FutureVector4::Clamp(FutureScalar min, FutureScalar max) const
{
    return (FutureVector4){
        m_vec.x > max.m_vec ? max.m_vec : (m_vec.x < min.m_vec ? min.m_vec : m_vec.x),
        m_vec.y > max.m_vec ? max.m_vec : (m_vec.y < min.m_vec ? min.m_vec : m_vec.y),
        m_vec.z > max.m_vec ? max.m_vec : (m_vec.z < min.m_vec ? min.m_vec : m_vec.z),
        m_vec.w > max.m_vec ? max.m_vec : (m_vec.w < min.m_vec ? min.m_vec : m_vec.w)
    };
}
                                         
inline FutureVector4	FutureVector4::AddAndSave(FutureScalar vec)
{
    m_vec.x += vec.m_vec;
    m_vec.y += vec.m_vec;
    m_vec.z += vec.m_vec;
    m_vec.w += vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureScalar vec)
{
    m_vec.x -= vec.m_vec;
    m_vec.y -= vec.m_vec;
    m_vec.z -= vec.m_vec;
    m_vec.w -= vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureScalar vec)
{
    m_vec.x *= vec.m_vec;
    m_vec.y *= vec.m_vec;
    m_vec.z *= vec.m_vec;
    m_vec.w *= vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureScalar vec)
{
    m_vec.x /= vec.m_vec;
    m_vec.y /= vec.m_vec;
    m_vec.z /= vec.m_vec;
    m_vec.w /= vec.m_vec;
    return *this;
}
                                         
inline FutureVector4	FutureVector4::AndAndSave(FutureScalar vec)
{
    m_vec.x &= vec.m_vec;
    m_vec.y &= vec.m_vec;
    m_vec.z &= vec.m_vec;
    m_vec.w &= vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureScalar vec)
{
    m_vec.x |= vec.m_vec;
    m_vec.y |= vec.m_vec;
    m_vec.z |= vec.m_vec;
    m_vec.w |= vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureScalar vec)
{
    m_vec.x ^= vec.m_vec;
    m_vec.y ^= vec.m_vec;
    m_vec.z ^= vec.m_vec;
    m_vec.w ^= vec.m_vec;
    return *this;
}
                                         
inline FutureVector4	FutureVector4::MinAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x < vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y < vec.y ? m_vec.y : vec.m_vec;
    m_vec.z = m_vec.z < vec.z ? m_vec.z : vec.m_vec;
    m_vec.w = m_vec.w < vec.w ? m_vec.w : vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureScalar vec)
{
    m_vec.x = m_vec.x > vec.x ? m_vec.x : vec.m_vec;
    m_vec.y = m_vec.y > vec.y ? m_vec.y : vec.m_vec;
    m_vec.z = m_vec.z > vec.z ? m_vec.z : vec.m_vec;
    m_vec.w = m_vec.w > vec.w ? m_vec.w : vec.m_vec;
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureScalar min, FutureScalar max)
{
    m_vec.x = m_vec.x > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.y);
    m_vec.z = m_vec.z > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.z);
    m_vec.w = m_vec.w > max.m_vec ? max.m_vec : (m_vec.m_vec < min.m_vec ? min.m_vec : m_vec.w);
    return *this;
}


/*********************Vector Operations***************************/
inline FutureVector4	FutureVector4::Add(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x + vec.m_vec.x,
        m_vec.y + vec.m_vec.y,
        m_vec.z + vec.m_vec.z,
        m_vec.w + vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Subtract(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x - vec.m_vec.x,
        m_vec.y - vec.m_vec.y,
        m_vec.z - vec.m_vec.z,
        m_vec.w - vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Multiply(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x * vec.m_vec.x,
        m_vec.y * vec.m_vec.y,
        m_vec.z * vec.m_vec.z,
        m_vec.w * vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Divide(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x / vec.m_vec.x,
        m_vec.y / vec.m_vec.y,
        m_vec.z / vec.m_vec.z,
        m_vec.w / vec.m_vec.w
    };
}
                                                 
inline FutureVector4	FutureVector4::And(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x & vec.m_vec.x,
        m_vec.y & vec.m_vec.y,
        m_vec.z & vec.m_vec.z,
        m_vec.w & vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Or(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x | vec.m_vec.x,
        m_vec.y | vec.m_vec.y,
        m_vec.z | vec.m_vec.z,
        m_vec.w | vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::XOr(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x ^ vec.m_vec.x,
        m_vec.y ^ vec.m_vec.y,
        m_vec.z ^ vec.m_vec.z,
        m_vec.w ^ vec.m_vec.w
    };
}
                                                 
inline FutureVector4	FutureVector4::Min(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y,
        m_vec.z < vec.m_vec.z ? m_vec.z : vec.m_vec.z,
        m_vec.w < vec.m_vec.w ? m_vec.w : vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Max(FutureVector4Arg vec) const
{
    return (FutureVector4){
        m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x,
        m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y,
        m_vec.z > vec.m_vec.z ? m_vec.z : vec.m_vec.z,
        m_vec.w > vec.m_vec.w ? m_vec.w : vec.m_vec.w
    };
}
inline FutureVector4	FutureVector4::Clamp(FutureVector4Arg min, FutureVector4Arg max) const
{
    return (FutureVector4){
        m_vec.x > max.x ? max.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x),
        m_vec.y > max.y ? max.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y),
        m_vec.z > max.z ? max.z : (m_vec.z < min.m_vec.z ? min.m_vec.z : m_vec.z),
        m_vec.w > max.w ? max.w : (m_vec.w < min.m_vec.w ? min.m_vec.w : m_vec.w)
    };
}
                                                 
inline FutureVector4	FutureVector4::AddAndSave(FutureVector4Arg vec)
{
    m_vec.x += vec.m_vec.x;
    m_vec.y += vec.m_vec.y;
    m_vec.z += vec.m_vec.z;
    m_vec.w += vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureVector4Arg vec)
{
    m_vec.x -= vec.m_vec.x;
    m_vec.y -= vec.m_vec.y;
    m_vec.z -= vec.m_vec.z;
    m_vec.w -= vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureVector4Arg vec)
{
    m_vec.x *= vec.m_vec.x;
    m_vec.y *= vec.m_vec.y;
    m_vec.z *= vec.m_vec.z;
    m_vec.w *= vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureVector4Arg vec)
{
    m_vec.x /= vec.m_vec.x;
    m_vec.y /= vec.m_vec.y;
    m_vec.z /= vec.m_vec.z;
    m_vec.w /= vec.m_vec.w;
    return *this;
}
                                             
inline FutureVector4	FutureVector4::AndAndSave(FutureVector4Arg vec)
{
    m_vec.x &= vec.m_vec.x;
    m_vec.y &= vec.m_vec.y;
    m_vec.z &= vec.m_vec.z;
    m_vec.w &= vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureVector4Arg vec)
{
    m_vec.x |= vec.m_vec.x;
    m_vec.y |= vec.m_vec.y;
    m_vec.z |= vec.m_vec.z;
    m_vec.w |= vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureVector4Arg vec)
{
    m_vec.x ^= vec.m_vec.x;
    m_vec.y ^= vec.m_vec.y;
    m_vec.z ^= vec.m_vec.z;
    m_vec.w ^= vec.m_vec.w;
    return *this;
}
                                             
inline FutureVector4	FutureVector4::MinAndSave(FutureVector4Arg vec)
{
    m_vec.x = m_vec.x < vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y < vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    m_vec.z = m_vec.z < vec.m_vec.z ? m_vec.z : vec.m_vec.z;
    m_vec.w = m_vec.w < vec.m_vec.w ? m_vec.w : vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureVector4Arg vec)
{
    m_vec.x = m_vec.x > vec.m_vec.x ? m_vec.x : vec.m_vec.x;
    m_vec.y = m_vec.y > vec.m_vec.y ? m_vec.y : vec.m_vec.y;
    m_vec.z = m_vec.z > vec.m_vec.z ? m_vec.z : vec.m_vec.z;
    m_vec.w = m_vec.w > vec.m_vec.w ? m_vec.w : vec.m_vec.w;
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureVector4Arg min, FutureVector4Arg max)
{
    m_vec.x = m_vec.x > max.m_vec.x ? max.m_vec.x : (m_vec.x < min.m_vec.x ? min.m_vec.x : m_vec.x);
    m_vec.y = m_vec.y > max.m_vec.y ? max.m_vec.y : (m_vec.y < min.m_vec.y ? min.m_vec.y : m_vec.y);
    m_vec.z = m_vec.z > max.m_vec.z ? max.m_vec.z : (m_vec.z < min.m_vec.z ? min.m_vec.z : m_vec.z);
    m_vec.w = m_vec.w > max.m_vec.w ? max.m_vec.w : (m_vec.w < min.m_vec.w ? min.m_vec.w : m_vec.w);
    return *this;
}

inline FutureVector4	FutureVector4::Cross(FutureVector4Arg vec) const
{
    return FutureVector4(m_vec.y * vec.m_vec.z - m_vec.z * vec.m_vec.y,
                         m_vec.z * vec.m_vec.x - m_vec.x * vec.m_vec.z,
                         m_vec.x * vec.m_vec.y - m_vec.y * vec.m_vec.x,
                         0);
}
inline FutureScalar		FutureVector4::Dot(FutureVector4Arg vec) const
{
	return FutureScalar((m_vec.x * vec.m_vec.x) + (m_vec.y * vec.m_vec.y) + (m_vec.z * vec.m_vec.z) + (m_vec.w * vec.m_vec.w));
}
inline FutureScalar		FutureVector4::Projection(FutureVector4Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= vec.Length();
	return dot;
}

inline FutureScalar		FutureVector4::CosAngle(FutureVector4Arg vec) const
{
	FutureScalar dot = Dot(vec);
	dot /= (Length() * vec.Length());
	return dot;
}

/*****************Unary Operations***********************************/

inline FutureVector4	FutureVector4::Abs() const
{
	return FutureVector4(
                         m_vec.x & 0x8FFFFFFF,
                         m_vec.y & 0x8FFFFFFF,
                         m_vec.z & 0x8FFFFFFF,
                         m_vec.w & 0x8FFFFFFF);
}

inline FutureScalar 	FutureVector4::Length() const
{
	return LengthSqr().SquareRoot();
}

inline FutureScalar 	FutureVector4::LengthSqr() const
{
	return Dot(*this);
}

inline FutureVector4	FutureVector4::Normalize() const
{
	return Multiply(LengthSqr().ReciprocalSquareRoot());
}

inline FutureVector4	FutureVector4::NormalizeAndSave()
{
	return MultiplyAndSave(LengthSqr().ReciprocalSquareRoot());
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector4::AsVec2() const
{
	return FutureVector2(m_vec);
}
inline FutureVector3	FutureVector4::AsVec3() const
{
	return FutureVector3(m_vec);
}
inline FutureVector4	FutureVector4::AsVec4() const
{
	return *this;
}
inline FutureVec4Float	FutureVector4::Vec4() const
{
	return m_vec;
}
    
inline FutureScalar     FutureVector4::Get(u8 i) const
{
	return FutureScalar(((float*)*m_vec)[i]);
}
    
inline FutureScalar     FutureVector4::X() const
{
	return m_vec.x;
}
inline FutureScalar     FutureVector4::Y() const
{
	return m_vec.y;
}
inline FutureScalar     FutureVector4::Z() const
{
	return m_vec.z;
}
inline FutureScalar     FutureVector4::W() const
{
	return m_vec.w;
}
    
inline void				FutureVector4::Set(FutureVector2Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
	m_vec.z = 0;
	m_vec.w = 0;
}
inline void				FutureVector4::Set(FutureVector3Arg value)
{
	m_vec.x = value.m_vec.x;
	m_vec.y = value.m_vec.y;
	m_vec.z = value.m_vec.z;
	m_vec.w = 0;
}
inline void				FutureVector4::Set(FutureVector4Arg value)
{
	m_vec = value.m_vec;
}
inline void				FutureVector4::Set(FutureVec4Float value)
{
	m_vec = value;
}
    
inline void				FutureVector4::Set(u8 i, FutureScalarArg value)
{
	((float*)*m_vec)[i] = value.m_vec;
}
	
inline void             FutureVector4::SetX(FutureScalarArg value)
{
    m_vec.x = value.m_vec;
}
inline void             FutureVector4::SetY(FutureScalarArg value)
{
    m_vec.y = value.m_vec;
}
inline void             FutureVector4::SetZ(FutureScalarArg value)
{
    m_vec.z = value.m_vec;
}
inline void             FutureVector4::SetW(FutureScalarArg value)
{
    m_vec.w = value.m_vec;
}


/***************** Operators ***********************************/

/********************* Binary ****************/
	
inline FutureVector4	FutureVector4::operator+(FutureVec4Float vec) const
{
    return Add(vec);
}
inline FutureVector4	FutureVector4::operator-(FutureVec4Float vec) const
{
    return Subtract(vec);
}
inline FutureVector4	FutureVector4::operator*(FutureVec4Float vec) const
{
    return Multiply(vec);
}
inline FutureVector4	FutureVector4::operator/(FutureVec4Float vec) const
{
    return Divide(vec);
}
inline FutureVector4	FutureVector4::operator&(FutureVec4Float vec) const
{
    return And(vec);
}
inline FutureVector4	FutureVector4::operator|(FutureVec4Float vec) const
{
    return Or(vec);
}
inline FutureVector4	FutureVector4::operator^(FutureVec4Float vec) const
{
    return XOr(vec);
}
		
inline FutureVector4	FutureVector4::operator+=(FutureVec4Float vec)
{
    return AddAndSave(vec);
}
inline FutureVector4	FutureVector4::operator-=(FutureVec4Float vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector4	FutureVector4::operator*=(FutureVec4Float vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector4	FutureVector4::operator/=(FutureVec4Float vec)
{
    return DivideAndSave(vec);
}

inline FutureVector4	FutureVector4::operator&=(FutureVec4Float vec)
{
    return AndAndSave(vec);
}
inline FutureVector4	FutureVector4::operator|=(FutureVec4Float vec)
{
    return OrAndSave(vec);
}
inline FutureVector4	FutureVector4::operator^=(FutureVec4Float vec)
{
    return XOrAndSave(vec);
}


inline FutureVector4	FutureVector4::operator+(FutureScalarArg vec) const
{
    return Add(vec);
}
inline FutureVector4	FutureVector4::operator-(FutureScalarArg vec) const
{
    return Subtract(vec);
}
inline FutureVector4	FutureVector4::operator*(FutureScalarArg vec) const
{
    return Multiply(vec);
}
inline FutureVector4	FutureVector4::operator/(FutureScalarArg vec) const
{
    return Divide(vec);
}

inline FutureVector4	FutureVector4::operator&(FutureScalarArg vec) const
{
    return And(vec);
}
inline FutureVector4	FutureVector4::operator|(FutureScalarArg vec) const
{
    return Or(vec);
}
inline FutureVector4	FutureVector4::operator^(FutureScalarArg vec) const
{
    return XOr(vec);
}

inline FutureVector4	FutureVector4::operator+=(FutureScalarArg vec)
{
    return AddAndSave(vec);
}
inline FutureVector4	FutureVector4::operator-=(FutureScalarArg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector4	FutureVector4::operator*=(FutureScalarArg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector4	FutureVector4::operator/=(FutureScalarArg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector4	FutureVector4::operator&=(FutureScalarArg vec)
{
    return AndAndSave(vec);
}
inline FutureVector4	FutureVector4::operator|=(FutureScalarArg vec)
{
    return OrAndSave(vec);
}
inline FutureVector4	FutureVector4::operator^=(FutureScalarArg vec)
{
    return XOrAndSave(vec);
}


inline FutureVector4	FutureVector4::operator+(FutureVector4Arg vec) const
{
    return Add(vec);
}
inline FutureVector4	FutureVector4::operator-(FutureVector4Arg vec) const
{
    return Subtract(vec);
}
inline FutureVector4	FutureVector4::operator*(FutureVector4Arg vec) const
{
    return Multiply(vec);
}
inline FutureVector4	FutureVector4::operator/(FutureVector4Arg vec) const
{
    return Divide(vec);
}

inline FutureVector4	FutureVector4::operator&(FutureVector4Arg vec) const
{
    return And(vec);
}
inline FutureVector4	FutureVector4::operator|(FutureVector4Arg vec) const
{
    return Or(vec);
}
inline FutureVector4	FutureVector4::operator^(FutureVector4Arg vec) const
{
    return XOr(vec);
}

inline FutureVector4	FutureVector4::operator+=(FutureVector4Arg vec)
{
    return AddAndSave(vec);
}
inline FutureVector4	FutureVector4::operator-=(FutureVector4Arg vec)
{
    return SubtractAndSave(vec);
}
inline FutureVector4	FutureVector4::operator*=(FutureVector4Arg vec)
{
    return MultiplyAndSave(vec);
}
inline FutureVector4	FutureVector4::operator/=(FutureVector4Arg vec)
{
    return DivideAndSave(vec);
}

inline FutureVector4	FutureVector4::operator&=(FutureVector4Arg vec)
{
    return AndAndSave(vec);
}
inline FutureVector4	FutureVector4::operator|=(FutureVector4Arg vec)
{
    return OrAndSave(vec);
}
inline FutureVector4	FutureVector4::operator^=(FutureVector4Arg vec)
{
    return XOrAndSave(vec);
}

/********************* Comparison ****************/

inline bool	FutureVector4::operator==(FutureVec4Float vec) const
{
    return (m_vec.x == vec.x) && (m_vec.y == vec.y) && (m_vec.z == vec.z) && (m_vec.w == vec.w);
}
inline bool	FutureVector4::operator!=(FutureVec4Float vec) const
{
    return (m_vec.x != vec.x) || (m_vec.y != vec.y) || (m_vec.z != vec.z) || (m_vec.w != vec.w);
}

inline bool	FutureVector4::operator==(FutureVector4Arg vec) const
{
    return (m_vec.x == vec.m_vec.x) && (m_vec.y == vec.m_vec.y) && (m_vec.z == vec.m_vec.z) && (m_vec.w == vec.m_vec.w);
}
inline bool	FutureVector4::operator!=(FutureVector4Arg vec) const
{
    return (m_vec.x != vec.m_vec.x) || (m_vec.y != vec.m_vec.y) || (m_vec.z != vec.m_vec.z) || (m_vec.w != vec.m_vec.w);
}


/********************* Assignment ****************/

inline FutureVector4	FutureVector4::operator=(FutureVec4Float vec)
{
    Set(vec);
    return *this;
}
inline FutureVector4	FutureVector4::operator=(FutureVector2Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector4	FutureVector4::operator=(FutureVector3Arg vec)
{
    Set(vec);
    return *this;
}
inline FutureVector4	FutureVector4::operator=(FutureVector4Arg vec)
{
    Set(vec);
    return *this;
}

/********************* Casting ****************/

inline FutureVector4::operator FutureVec4Float() const
{
	return Vec4();
}
inline FutureVector4::operator FutureVector2() const
{
	return AsVec2();
}
inline FutureVector4::operator FutureVector3() const
{
	return AsVec3();
}
inline FutureVector4::operator FutureVector4() const
{
	return AsVec4();
}
inline FutureVector4::operator bool() const
{
    return (m_vec.x != 0) || (m_vec.y != 0) || (m_vec.z != 0) || (m_vec.w != 0);
}

/***************** String Operations ***********************************/

inline string			FutureVector4::ToString() const
{
    wchar_t str[256];
    swprintf(str, L"Vector4[%f, %f, %f, %f]", m_vec.x, m_vec.y, m_vec.z, m_vec.w);
    return str;
}
inline FutureVector4		FutureVector4::SetFromString(string str)
{
    return ZERO;
}

inline FutureVector4::operator string() const
{
    return ToString();
}


/***************** Static ***********************************/

inline FutureVector4		FutureVector4::Parse(string str)
{
    return ZERO;
}

const FutureVector4		NEGATIVE_ONE = FutureVector4(-1.f);
const FutureVector4		ZERO = FutureVector4();
const FutureVector4		ONE = FutureVector4(1.f);

const FutureVector4		AXIS_X = FutureVector4(1.f, 0, 0, 0);
const FutureVector4		AXIS_Y = FutureVector4(0, 1.f, 0, 0);
const FutureVector4		AXIS_Z = FutureVector4(0, 0, 1.f, 0);
const FutureVector4		AXIS_W = FutureVector4(0, 0, 0, 1.f);
