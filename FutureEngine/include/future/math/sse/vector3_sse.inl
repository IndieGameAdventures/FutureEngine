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
*	A standard 3 coordinate vector (x, y, z, 0)
*/

#ifndef FUTURE_MATH_VECTOR_H
#   error This file should only be included by vector.h
#endif

inline FutureVector3::FutureTemplateVector()
: m_vec(FutureVec4CreateEmpty())
{}
inline FutureVector3::FutureTemplateVector(f32 value)
: m_vec(FutureVec4CreateOne(value))
{}
inline FutureVector3::FutureTemplateVector(FutureVec4Float value)
: m_vec(value)
{
	SetW(FutureScalar::ONE);
}
inline FutureVector3::FutureTemplateVector(FutureScalarArg value)
: m_vec(value.Vec4())
{
	SetW(FutureScalar::ONE);
}
inline FutureVector3::FutureTemplateVector(f32 x, f32 y, f32 z = 0, f32 w = 0)
: m_vec(FutureVec4CreateVec(x, y, z, 0))
{}
inline FutureVector3::FutureTemplateVector(FutureVector2Arg value)
: m_vec(value.Vec4())
{
	SetW(FutureScalar::ZERO);
}
inline FutureVector3::FutureTemplateVector(FutureVector3Arg value)
: m_vec(value.Vec4())
{
	SetW(FutureScalar::ZERO);
}
inline FutureVector3::FutureTemplateVector(FutureVector4Arg value)
: m_vec(value.Vec4())
{
	SetW(FutureScalar::ZERO);
}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/
inline FutureVector3	FutureVector3::Add(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Add(m_vec, vec));
}
inline FutureVector3	FutureVector3::Subtract(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Subtract(m_vec, vec));
}
inline FutureVector3	FutureVector3::Multiply(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Multiply(m_vec, vec));
}
inline FutureVector3	FutureVector3::Divide(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Divide(m_vec, vec));
}

inline FutureVector3	FutureVector3::And(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4And(m_vec, vec));
}
inline FutureVector3	FutureVector3::Or(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Or(m_vec, vec));
}
inline FutureVector3	FutureVector3::XOr(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4XOr(m_vec, vec));
}

inline FutureVector3	FutureVector3::Min(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Min(m_vec, vec));
}
inline FutureVector3	FutureVector3::Max(FutureVec4Float vec) const
{
    return FutureVector3(FutureVec4Max(m_vec, vec));
}
inline FutureVector3	FutureVector3::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return FutureVector3(FutureVec4Clamp(m_vec, min, max));
}
		
inline FutureVector3	FutureVector3::AddAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Add(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Divide(m_vec, vec);
    return *this;
}

inline FutureVector3	FutureVector3::AndAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4And(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Or(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4XOr(m_vec, vec);
    return *this;
}

inline FutureVector3	FutureVector3::MinAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Min(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Max(m_vec, vec);
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec = FutureVec4Clamp(m_vec, min, max);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector3	FutureVector3::Add(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Subtract(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Multiply(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Divide(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector3	FutureVector3::And(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Or(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::XOr(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector3	FutureVector3::Min(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Max(FutureScalarArg vec) const
{
    return FutureVector3(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Clamp(FutureScalarArg min, FutureScalarArg max) const
{
    return FutureVector3(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector3	FutureVector3::AddAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector3	FutureVector3::AndAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector3	FutureVector3::MinAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureScalarArg min, FutureScalarArg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}



/*********************Vector Operations***************************/
inline FutureVector3	FutureVector3::Add(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Subtract(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Multiply(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Divide(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector3	FutureVector3::And(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Or(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::XOr(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector3	FutureVector3::Min(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Max(FutureVector3Arg vec) const
{
    return FutureVector3(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector3	FutureVector3::Clamp(FutureVector3Arg min, FutureVector3Arg max) const
{
    return FutureVector3(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector3	FutureVector3::AddAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::SubtractAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::MultiplyAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::DivideAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector3	FutureVector3::AndAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::OrAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::XOrAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector3	FutureVector3::MinAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::MaxAndSave(FutureVector3Arg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector3	FutureVector3::ClampAndSave(FutureVector3Arg min, FutureVector3Arg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}

inline FutureVector3	FutureVector3::Cross(FutureVector3Arg vec) const
{
	return FutureVector3(FutureVec4Cross(m_vec, vec.Vec4()));
}
inline FutureScalar		FutureVector3::Dot(FutureVector3Arg vec) const
{
	return FutureVector3(FutureVec4Dot(m_vec, vec.Vec4()));
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
	return And(FUTURE_VECTOR_MASK_NO_SIGN);
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
	return FutureVector3(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
}

inline FutureVector3	FutureVector3::NormalizeAndSave()
{
	m_vec = FutureVector3(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
	return *this;
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector3::AsVec2() const
{
	return FutureVector2(m_vec).And(FUTURE_VECTOR_MASK_XY);
}
inline FutureVector3	FutureVector3::AsVec3() const
{
	return FutureVector3(m_vec);
}
inline FutureVector4	FutureVector3::AsVec4() const
{
	return FutureVector4(m_vec);
}
inline FutureVec4Float	FutureVector3::Vec4() const
{
	return m_vec;
}
    
inline FutureScalar     FutureVector3::Get(u8 i) const
{
	return FutureScalar(FutureVec4Replicate(m_vec, i));
}
    
inline FutureScalar     FutureVector3::X() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 0));
}
inline FutureScalar     FutureVector3::Y() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 1));
}
inline FutureScalar     FutureVector3::Z() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 2));
}
inline FutureScalar     FutureVector3::W() const
{
	return FutureScalar::ZERO;
}
    
inline void				FutureVector3::Set(FutureVector2Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XY).Vec4();
}
inline void				FutureVector3::Set(FutureVector3Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XYZ).Vec4();
}
inline void				FutureVector3::Set(FutureVector4Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XYZ).Vec4();
}
inline void				FutureVector3::Set(FutureVec4Float value)
{
	m_vec = FutureVec4And(value, FUTURE_VECTOR_MASK_XYZ);
}
    
inline void				FutureVector3::Set(u8 i, FutureScalarArg value)
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
		SetW(FutureScalar::ZERO);
		break;
	}
}
	
inline void             FutureVector3::SetX(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 1, 1), m_vec, 0, 2, 2, 3);
}
inline void             FutureVector3::SetY(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 0, 0), m_vec, 2, 0, 2, 3);
}
inline void             FutureVector3::SetZ(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(m_vec, FutureVec4Shuffle(value, m_vec, 0, 0, 3, 3), 0, 1, 0, 2);
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
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector3::operator!=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
}

inline bool	FutureVector3::operator==(FutureVector3Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector3::operator!=(FutureVector3Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
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
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, ZERO)) == 0xFFFF;
}

/***************** String Operations ***********************************/

inline string			FutureVector3::ToString() const
{
    f32 v[4];
	FutureVec4GetAll(m_vec, v);
    wchar_t str[256];
    swprintf(str, L"Vector3[%f, %f, %f, %f]", v[0], v[1], v[2], v[3]);
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
