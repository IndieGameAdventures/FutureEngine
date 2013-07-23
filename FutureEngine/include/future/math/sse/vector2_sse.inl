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
*	A standard 2 coordinate vector (x, y, 0, 0)
*/

#ifndef FUTURE_MATH_VECTOR_H
#   error This file should only be included by vector.h
#endif

inline FutureVector2::FutureTemplateVector()
: m_vec(FutureVec4CreateEmpty())
{}
inline FutureVector2::FutureTemplateVector(f32 value)
: m_vec(FutureVec4CreateOne(value))
{}
inline FutureVector2::FutureTemplateVector(FutureVec4Float value)
: m_vec(value)
{
	SetW(FutureScalar::ONE);
}
inline FutureVector2::FutureTemplateVector(FutureScalarArg value)
: m_vec(value.Vec4())
{
	SetW(FutureScalar::ONE);
}
inline FutureVector2::FutureTemplateVector(f32 x, f32 y, f32 z = 0, f32 w = 0)
: m_vec(FutureVec4CreateVec(x, y, 0, 0))
{}
inline FutureVector2::FutureTemplateVector(FutureVector2Arg value)
: m_vec(value.Vec4())
{
	AndAndSave(FUTURE_VECTOR_MASK_XY);
}
inline FutureVector2::FutureTemplateVector(FutureVector3Arg value)
: m_vec(value.Vec4())
{
	AndAndSave(FUTURE_VECTOR_MASK_XY);
}
inline FutureVector2::FutureTemplateVector(FutureVector4Arg value)
: m_vec(value.Vec4())
{
	AndAndSave(FUTURE_VECTOR_MASK_XY);
}

/*****************Binary Operations***********************************/

/*********************Vec4 Operations***************************/
inline FutureVector2	FutureVector2::Add(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Add(m_vec, vec));
}
inline FutureVector2	FutureVector2::Subtract(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Subtract(m_vec, vec));
}
inline FutureVector2	FutureVector2::Multiply(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Multiply(m_vec, vec));
}
inline FutureVector2	FutureVector2::Divide(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Divide(m_vec, vec));
}

inline FutureVector2	FutureVector2::And(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4And(m_vec, vec));
}
inline FutureVector2	FutureVector2::Or(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Or(m_vec, vec));
}
inline FutureVector2	FutureVector2::XOr(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4XOr(m_vec, vec));
}

inline FutureVector2	FutureVector2::Min(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Min(m_vec, vec));
}
inline FutureVector2	FutureVector2::Max(FutureVec4Float vec) const
{
    return FutureVector2(FutureVec4Max(m_vec, vec));
}
inline FutureVector2	FutureVector2::Clamp(FutureVec4Float min, FutureVec4Float max) const
{
    return FutureVector2(FutureVec4Clamp(m_vec, min, max));
}
		
inline FutureVector2	FutureVector2::AddAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Add(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Divide(m_vec, vec);
    return *this;
}

inline FutureVector2	FutureVector2::AndAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4And(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Or(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4XOr(m_vec, vec);
    return *this;
}

inline FutureVector2	FutureVector2::MinAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Min(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureVec4Float vec)
{
    m_vec = FutureVec4Max(m_vec, vec);
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureVec4Float min, FutureVec4Float max)
{
    m_vec = FutureVec4Clamp(m_vec, min, max);
    return *this;
}

/*********************Scalar Operations***************************/
inline FutureVector2	FutureVector2::Add(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Subtract(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Multiply(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Divide(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector2	FutureVector2::And(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Or(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::XOr(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector2	FutureVector2::Min(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Max(FutureScalarArg vec) const
{
    return FutureVector2(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Clamp(FutureScalarArg min, FutureScalarArg max) const
{
    return FutureVector2(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector2	FutureVector2::AddAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector2	FutureVector2::AndAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector2	FutureVector2::MinAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureScalarArg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureScalarArg min, FutureScalarArg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}



/*********************Vector Operations***************************/
inline FutureVector2	FutureVector2::Add(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Add(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Subtract(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Subtract(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Multiply(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Multiply(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Divide(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Divide(m_vec, vec.Vec4()));
}

inline FutureVector2	FutureVector2::And(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4And(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Or(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Or(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::XOr(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4XOr(m_vec, vec.Vec4()));
}

inline FutureVector2	FutureVector2::Min(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Min(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Max(FutureVector2Arg vec) const
{
    return FutureVector2(FutureVec4Max(m_vec, vec.Vec4()));
}
inline FutureVector2	FutureVector2::Clamp(FutureVector2Arg min, FutureVector2Arg max) const
{
    return FutureVector2(FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4()));
}

inline FutureVector2	FutureVector2::AddAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Add(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::SubtractAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Subtract(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::MultiplyAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Multiply(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::DivideAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Divide(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector2	FutureVector2::AndAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4And(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::OrAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Or(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::XOrAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4XOr(m_vec, vec.Vec4());
    return *this;
}

inline FutureVector2	FutureVector2::MinAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Min(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::MaxAndSave(FutureVector2Arg vec)
{
    m_vec = FutureVec4Max(m_vec, vec.Vec4());
    return *this;
}
inline FutureVector2	FutureVector2::ClampAndSave(FutureVector2Arg min, FutureVector2Arg max)
{
    m_vec = FutureVec4Clamp(m_vec, min.Vec4(), max.Vec4());
    return *this;
}

inline FutureVector2	FutureVector2::Cross(FutureVector2Arg vec) const
{
	return FutureVector2::ZERO;
}
inline FutureScalar		FutureVector2::Dot(FutureVector2Arg vec) const
{
	return FutureVector2(FutureVec4Dot(m_vec, vec.Vec4()));
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
	return And(FUTURE_VECTOR_MASK_NO_SIGN);
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
	return FutureVector2(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
}

inline FutureVector2	FutureVector2::NormalizeAndSave()
{
	m_vec = FutureVector2(FutureVec4Multiply(m_vec, LengthSqr().ReciprocalSquareRoot().Vec4()));
	return *this;
}


/*****************Get/Set Operations***********************************/

inline FutureVector2	FutureVector2::AsVec2() const
{
	return FutureVector2(m_vec).And(FUTURE_VECTOR_MASK_XY);
}
inline FutureVector3	FutureVector2::AsVec3() const
{
	return FutureVector3(m_vec);
}
inline FutureVector4	FutureVector2::AsVec4() const
{
	return FutureVector4(m_vec);
}
inline FutureVec4Float	FutureVector2::Vec4() const
{
	return m_vec;
}
    
inline FutureScalar     FutureVector2::Get(u8 i) const
{
	return FutureScalar(FutureVec4Replicate(m_vec, i));
}
    
inline FutureScalar     FutureVector2::X() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 0));
}
inline FutureScalar     FutureVector2::Y() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 1));
}
inline FutureScalar     FutureVector2::Z() const
{
	return FutureScalar(FutureVec4Replicate(m_vec, 2));
}
inline FutureScalar     FutureVector2::W() const
{
	return FutureScalar::ZERO;
}
    
inline void				FutureVector2::Set(FutureVector2Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XY).Vec4();
}
inline void				FutureVector2::Set(FutureVector3Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XY).Vec4();
}
inline void				FutureVector2::Set(FutureVector4Arg value)
{
	m_vec = value.And(FUTURE_VECTOR_MASK_XY).Vec4();
}
inline void				FutureVector2::Set(FutureVec4Float value)
{
	m_vec = FutureVec4And(value, FUTURE_VECTOR_MASK_XY);
}
    
inline void				FutureVector2::Set(u8 i, FutureScalarArg value)
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
		SetW(FutureScalar::ZERO);
		break;
	case 3:
		SetW(FutureScalar::ZERO);
		break;
	}
}
	
inline void             FutureVector2::SetX(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 1, 1), m_vec, 0, 2, 2, 3);
}
inline void             FutureVector2::SetY(FutureScalarArg value)
{
	m_vec = FutureVec4Shuffle(FutureVec4Shuffle(value, m_vec, 0, 0, 0, 0), m_vec, 2, 0, 2, 3);
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
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector2::operator!=(FutureVec4Float vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
}

inline bool	FutureVector2::operator==(FutureVector2Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareEqual(m_vec, vec)) == 0xFFFF;
}
inline bool	FutureVector2::operator!=(FutureVector2Arg vec) const
{
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, vec)) == 0xFFFF;
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
    return FutureVec4CompareResult(FutureVec4CompareNotEqual(m_vec, ZERO)) == 0xFFFF;
}

/***************** String Operations ***********************************/

inline string			FutureVector2::ToString() const
{
    f32 v[4];
	FutureVec4GetAll(m_vec, v);
    wchar_t str[256];
    swprintf(str, L"Vector3[%f, %f, %f, %f]", v[0], v[1], v[2], v[3]);
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
