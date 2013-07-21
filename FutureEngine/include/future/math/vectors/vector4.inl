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

#include <future/core/type/type.h>
#include <future/math/type/vec4.h>
#include <future/math/scalar.h>
#include <future/math/vector.h>

#ifndef FUTURE_MATH_VECTOR_H
#   error This file should only be included by vector.h
#endif

inline FutureVector4::FutureTemplateVector()
: m_vec(FutureVec4CreateEmpty())
{}
inline FutureVector4::FutureTemplateVector(f32 value)
: m_vec(FutureVec4CreateOne(value))
{}
inline FutureVector4::FutureTemplateVector(FutureVec4Float value)
: m_vec(value)
{}
inline FutureVector4::FutureTemplateVector(FutureScalarArg value)
: m_vec(value.Vec4())
{}
inline FutureVector4::FutureTemplateVector(f32 x, f32 y, f32 z = 0, f32 w = 0)
: m_vec(FutureVec4CreateVec(x, y, z, w))
{}
inline FutureVector4::FutureTemplateVector(FutureVector2Arg value)
: m_vec(value.Vec4())
{}
inline FutureVector4::FutureTemplateVector(FutureVector3Arg value)
: m_vec(value.Vec4())
{}
inline FutureVector4::FutureTemplateVector(FutureVector4Arg value)
: m_vec(value.Vec4())
{}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/
inline FutureVector4	FutureVector4::Add(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Add(m_vec, vec));
}
inline FutureVector4	FutureVector4::Subtract(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Subtract(m_vec, vec));
}
inline FutureVector4	FutureVector4::Multiply(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Multiply(m_vec, vec));
}
inline FutureVector4	FutureVector4::Divide(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Divide(m_vec, vec));
}

inline FutureVector4	FutureVector4::And(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4And(m_vec, vec));
}
inline FutureVector4	FutureVector4::Or(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Or(m_vec, vec));
}
inline FutureVector4	FutureVector4::XOr(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4XOr(m_vec, vec));
}

inline FutureVector4	FutureVector4::Min(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Min(m_vec, vec));
}
inline FutureVector4	FutureVector4::Max(FutureVec4Float vec) const
{
    return FutureVector4(FutureVec4Max(m_vec, vec));
}
inline FutureVector4	FutureVector4::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return FutureVector4(FutureVec4Clamp(m_vec, min, max));
}
		
inline FutureVector4	FutureVector4::AddAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Add(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Divide(m_vec, vec);
    return *this;
}

inline FutureVector4	FutureVector4::AndAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4And(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Or(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4XOr(m_vec, vec);
    return *this;
}

inline FutureVector4	FutureVector4::MinAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Min(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Max(m_vec, vec);
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec = FutureVec4Clamp(m_vec, min, max);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector4	FutureVector4::Add(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Subtract(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Multiply(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Divide(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector4	FutureVector4::And(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Or(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::XOr(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector4	FutureVector4::Min(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Max(FutureScalarArg vec) const
{
    return FutureVector4(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Clamp(FutureScalarArg min, FutureScalarArg max) const
{
    return FutureVector4(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector4	FutureVector4::AddAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector4	FutureVector4::AndAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector4	FutureVector4::MinAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureScalarArg min, FutureScalarArg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}



/*********************Vector Operations***************************/
inline FutureVector4	FutureVector4::Add(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Subtract(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Multiply(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Divide(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector4	FutureVector4::And(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Or(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::XOr(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector4	FutureVector4::Min(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Max(FutureVector4Arg vec) const
{
    return FutureVector4(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector4	FutureVector4::Clamp(FutureVector4Arg min, FutureVector4Arg max) const
{
    return FutureVector4(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector4	FutureVector4::AddAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::SubtractAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::MultiplyAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::DivideAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector4	FutureVector4::AndAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::OrAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::XOrAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector4	FutureVector4::MinAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::MaxAndSave(FutureVector4Arg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector4	FutureVector4::ClampAndSave(FutureVector4Arg min, FutureVector4Arg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}

inline FutureVector4	FutureVector4::Cross(FutureVector4Arg vec) const
{
	return FutureVector4(FutureVec4Cross(m_vec, vec.Vec4()));
}
inline FutureScalar		FutureVector4::Dot(FutureVector4Arg vec) const
{
	return FutureVector4(FutureVec4Dot(m_vec, vec.Vec4()));
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
	return And(FUTURE_VECTOR_MASK_NO_SIGN);
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
	return FutureVector4(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
}

inline FutureVector4	FutureVector4::NormalizeAndSave()
{
	m_vec = FutureVector4(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
	return *this;
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector4::AsVec2() const
{
	return FutureVector2(m_vec).And(FUTURE_VECTOR_MASK_XY);
}
inline FutureVector3	FutureVector4::AsVec3() const
{
	return FutureVector3(m_vec).And(FUTURE_VECTOR_MASK_XYZ);
}
inline FutureVector4	FutureVector4::AsVec4() const
{
	return FutureVector4(m_vec);
}
inline FutureVec4Float	FutureVector4::Vec4() const
{
	return m_vec;
}
    
inline FutureScalar     FutureVector4::Get(u8 i) const
{
	return FutureScalar(FutureVec4Replicate(m_vec, i));
}
    
inline FutureScalar     FutureVector4::X() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 0));
}
inline FutureScalar     FutureVector4::Y() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 1));
}
inline FutureScalar     FutureVector4::Z() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 2));
}
inline FutureScalar     FutureVector4::W() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 3));
}
    
inline void				FutureVector4::Set(FutureVector2Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XY).Vec4();
}
inline void				FutureVector4::Set(FutureVector3Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XYZ).Vec4();
}
inline void				FutureVector4::Set(FutureVector4Arg value)
{
	m_vec = value.Vec4();
}
inline void				FutureVector4::Set(FutureVec4Float value)
{
	m_vec = value;
}
    
inline void				FutureVector4::Set(u8 i, FutureScalarArg value)
{
	switch(i)
	{
	case 0:
		SetX(value);
		break;
	case 1:
		SetY(value);
		break;
	case 2:
		SetZ(value);
		break;
	case 3:
		SetW(value);
		break;
	}
}
	
inline void             FutureVector4::SetX(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 1, 1), m_vec, 0, 2, 2, 3);
}
inline void             FutureVector4::SetY(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 0, 0), m_vec, 2, 0, 2, 3);
}
inline void             FutureVector4::SetZ(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(m_vec, FutureVec4Shuffle(value, m_vec, 0, 0, 3, 3), 0, 1, 0, 2);
}
inline void             FutureVector4::SetW(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(m_vec, FutureVec4Shuffle(value, m_vec, 0, 0, 2, 2), 0, 1, 2, 0);
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
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector4::operator!=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
}

inline bool	FutureVector4::operator==(FutureVector4Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector4::operator!=(FutureVector4Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
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
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, ZERO)) == 0xFFFF;
}

/***************** String Operations ***********************************/

inline string			FutureVector4::ToString() const
{
    f32 v[4];
	FutureVec4GetAll(m_vec, v);
    wchar_t str[256];
    swprintf(str, L"Vector4[%f, %f, %f, %f]", v[0], v[1], v[2], v[3]);
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
