#pragma once

namespace ReverieEngine::Math
{
    // To allow floats to implicitly construct Scalars, we need to clarify these operators and suppress
    // upconversion.
    inline bool operator<  ( Scalar lhs, float rhs ) { return static_cast<float>(lhs) <  rhs; }
    inline bool operator<= ( Scalar lhs, float rhs ) { return static_cast<float>(lhs) <= rhs; }
    inline bool operator>  ( Scalar lhs, float rhs ) { return static_cast<float>(lhs) >  rhs; }
    inline bool operator>= ( Scalar lhs, float rhs ) { return static_cast<float>(lhs) >= rhs; }
    inline bool operator== ( Scalar lhs, float rhs ) { return static_cast<float>(lhs) == rhs; }
    inline bool operator<  ( float lhs, Scalar rhs ) { return lhs <  static_cast<float>(rhs); }
    inline bool operator<= ( float lhs, Scalar rhs ) { return lhs <= static_cast<float>(rhs); }
    inline bool operator>  ( float lhs, Scalar rhs ) { return lhs >  static_cast<float>(rhs); }
    inline bool operator>= ( float lhs, Scalar rhs ) { return lhs >= static_cast<float>(rhs); }
    inline bool operator== ( float lhs, Scalar rhs ) { return lhs == static_cast<float>(rhs); }

    #define CREATE_SIMD_FUNCTIONS( TYPE ) \
	inline TYPE Sqrt( TYPE s ) { return TYPE(XMVectorSqrt(s)); } \
	inline TYPE Recip( TYPE s ) { return TYPE(XMVectorReciprocal(s)); } \
	inline TYPE RecipSqrt( TYPE s ) { return TYPE(XMVectorReciprocalSqrt(s)); } \
	inline TYPE Floor( TYPE s ) { return TYPE(XMVectorFloor(s)); } \
	inline TYPE Ceiling( TYPE s ) { return TYPE(XMVectorCeiling(s)); } \
	inline TYPE Round( TYPE s ) { return TYPE(XMVectorRound(s)); } \
	inline TYPE Abs( TYPE s ) { return TYPE(XMVectorAbs(s)); } \
	inline TYPE Exp( TYPE s ) { return TYPE(XMVectorExp(s)); } \
	inline TYPE Pow( TYPE b, TYPE e ) { return TYPE(XMVectorPow(b, e)); } \
	inline TYPE Log( TYPE s ) { return TYPE(XMVectorLog(s)); } \
	inline TYPE Sin( TYPE s ) { return TYPE(XMVectorSin(s)); } \
	inline TYPE Cos( TYPE s ) { return TYPE(XMVectorCos(s)); } \
	inline TYPE Tan( TYPE s ) { return TYPE(XMVectorTan(s)); } \
	inline TYPE ASin( TYPE s ) { return TYPE(XMVectorASin(s)); } \
	inline TYPE ACos( TYPE s ) { return TYPE(XMVectorACos(s)); } \
	inline TYPE ATan( TYPE s ) { return TYPE(XMVectorATan(s)); } \
	inline TYPE ATan2( TYPE y, TYPE x ) { return TYPE(XMVectorATan2(y, x)); } \
	inline TYPE Max( TYPE a, TYPE b ) { return TYPE(XMVectorMax(a, b)); } \
	inline TYPE Min( TYPE a, TYPE b ) { return TYPE(XMVectorMin(a, b)); } \
	inline TYPE Clamp( TYPE v, TYPE a, TYPE b ) { return Min(Max(v, a), b); } \
	inline TYPE Clamp01( TYPE s ) { return Clamp(s, TYPE(0.0f), TYPE(1.0f)); } \
	inline TYPE Lerp( TYPE a, TYPE b, TYPE t ) { return TYPE(XMVectorLerpV(a, b, Clamp01(t))); } \
	inline TYPE Lerp( TYPE a, TYPE b, float t ) { return TYPE(XMVectorLerp(a, b, Clamp01(t))); } \
	inline TYPE LerpUnclamped( TYPE a, TYPE b, TYPE t ) { return TYPE(XMVectorLerpV(a, b, t)); } \
	inline TYPE LerpUnclamped( TYPE a, TYPE b, float t ) { return TYPE(XMVectorLerp(a, b, t)); } \
	inline BoolVector operator<  ( TYPE lhs, TYPE rhs ) { return XMVectorLess(lhs, rhs); } \
	inline BoolVector operator<= ( TYPE lhs, TYPE rhs ) { return XMVectorLessOrEqual(lhs, rhs); } \
	inline BoolVector operator>  ( TYPE lhs, TYPE rhs ) { return XMVectorGreater(lhs, rhs); } \
	inline BoolVector operator>= ( TYPE lhs, TYPE rhs ) { return XMVectorGreaterOrEqual(lhs, rhs); } \
	inline BoolVector operator== ( TYPE lhs, TYPE rhs ) { return XMVectorEqual(lhs, rhs); } \
	inline TYPE Select( TYPE lhs, TYPE rhs, BoolVector mask ) { return TYPE(XMVectorSelect(lhs, rhs, mask)); }
	
	CREATE_SIMD_FUNCTIONS(Scalar)
	CREATE_SIMD_FUNCTIONS(Vector2)
	CREATE_SIMD_FUNCTIONS(Vector3)
	CREATE_SIMD_FUNCTIONS(Vector4)

#undef CREATE_SIMD_FUNCTIONS

	inline float Sqrt( float s ) { return Sqrt(Scalar(s)); }
	inline float Recip( float s ) { return Recip(Scalar(s)); }
	inline float RecipSqrt( float s ) { return RecipSqrt(Scalar(s)); }
	inline float Floor( float s ) { return Floor(Scalar(s)); }
	inline float Ceiling( float s ) { return Ceiling(Scalar(s)); }
	inline float Round( float s ) { return Round(Scalar(s)); }
	inline float Abs( float s ) { return s < 0.0f ? -s : s; }
	inline float Exp( float s ) { return Exp(Scalar(s)); }
	inline float Pow( float b, float e ) { return Pow(Scalar(b), Scalar(e)); }
	inline float Log( float s ) { return Log(Scalar(s)); }
	inline float Sin( float s ) { return Sin(Scalar(s)); }
	inline float Cos( float s ) { return Cos(Scalar(s)); }
	inline float Tan( float s ) { return Tan(Scalar(s)); }
	inline float ASin( float s ) { return ASin(Scalar(s)); }
	inline float ACos( float s ) { return ACos(Scalar(s)); }
	inline float ATan( float s ) { return ATan(Scalar(s)); }
	inline float ATan2( float y, float x ) { return ATan2(Scalar(y), Scalar(x)); }
	inline float Clamp( float v, float a, float b ) { return Min(Max(v, a), b); }
	inline float Clamp01( float s ) { return Clamp(s, 0.0f, 1.0f); }
	inline float Lerp( float a, float b, float t ) { return a + (b - a) * Clamp01(t); }
	inline float LerpUnclamped( float a, float b, float t ) { return a + (b - a) * t; }
	inline float Max( float a, float b ) { return a > b ? a : b; }
	inline float Min( float a, float b ) { return a < b ? a : b; }

	inline Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
	{
    	return Math::Lerp(a, b, t);
	}

	inline Vector2 Vector2::Lerp(Vector2 a, Vector2 b, Vector2 t)
	{
		return Math::Lerp(a, b, t);
	}

	inline Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t)
    {
    	return Math::LerpUnclamped(a, b, t);
	}

	inline Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, Vector2 t)
    {
	    return Math::LerpUnclamped(a, b, t);
    }
	
	inline Vector2 Vector2::Min(Vector2 a, Vector2 b)
    {
	    return Math::Min(a, b);
    }

	inline Vector2 Vector2::Max(Vector2 a, Vector2 b)
	{
	    return Math::Max(a, b);
	}

	inline Vector2 Vector2::Clamp(Vector2 v, Vector2 a, Vector2 b)
	{
    	return Math::Clamp(v, a, b);
	}

	inline Vector2 Vector2::Clamp01(Vector2 v)
	{
    	return Math::Clamp01(v);
	}
}
