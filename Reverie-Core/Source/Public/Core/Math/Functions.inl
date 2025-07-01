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
	inline TYPE Log( TYPE s ) { return TYPE(XMVectorLogE(s)); } \
	inline TYPE Log2( TYPE s ) { return TYPE(XMVectorLog2(s)); } \
	inline TYPE Log10( TYPE s ) { return TYPE(XMVectorLog10(s)); } \
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

#pragma region Vector2 Static Functions Implementations
	
	inline Scalar Vector2::Dot(Vector2 v1, Vector2 v2)
	{
	    return Scalar(XMVector2Dot(v1, v2));
	}

	inline Scalar Vector2::Cross(Vector2 v1, Vector2 v2)
	{
		return Scalar(XMVector2Cross(v1, v2));
	}

    inline Vector2 Vector2::Reflect(Vector2 v, Vector2 normal)
    {
        return Vector2(XMVector2Reflect(v, normal));
    }

	inline Scalar Vector2::Distance(Vector2 a, Vector2 b)
    {
        return (a - b).Length();
    }

	inline Scalar Vector2::SqrDistance(Vector2 a, Vector2 b)
    {
        return (a - b).SqrLength();
    }

	inline Vector2 Vector2::ClampLength(Vector2 v, float maxLength)
    {
        if (v.SqrLength() > maxLength * maxLength)
        {
            return v.Normalized() * maxLength;
        }
        return v;
    }

	inline Vector2 Vector2::SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime,
        float deltaTime, float maxSpeed)
    {
    	// Prevent div by zero
    	smoothTime = Math::Max(EPSILON, smoothTime);

    	const float k_omega = 2.0f / smoothTime;
    	const float x = k_omega * deltaTime;
    	const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

    	Vector2 change = target - current;
    	Vector2 originalTo = target;

    	change = Vector2::ClampLength(change, maxSpeed * smoothTime);

    	target = current - change;
    	Vector2 temp = (currentVelocity + k_omega * change) * deltaTime;
    	currentVelocity = (currentVelocity - k_omega * temp) * exp;
    	Vector2 output = target + (change + temp) * exp;

    	// Prevent overshooting
    	Vector2 origToCurrent = originalTo - current;
    	Vector2 outToOriginal = output - originalTo;
    	if(Vector2::Dot(origToCurrent, outToOriginal) > 0.0f)
    	{
    		output = originalTo;
    		currentVelocity = Vector2::zero;
    	}

    	return output;
    }
	
	inline Scalar Vector2::Angle(Vector2 from, Vector2 to)
    {
    	return Vector2::AngleNorm(from.Normalized(), to.Normalized());
    }

	inline Scalar Vector2::AngleNorm(Vector2 nFrom, Vector2 nTo)
    {
    	return Scalar(XMVector2AngleBetweenNormals(nFrom, nTo)) * RAD2DEG;
    }

	inline Scalar Vector2::AngleFast(Vector2 nFrom, Vector2 nTo)
    {
	    return Scalar(XMVector2AngleBetweenNormalsEst(nFrom, nTo)) * RAD2DEG;
    }
	
	inline Scalar Vector2::SignedAngle(Vector2 from, Vector2 to)
	{
		return Vector2::SignedAngleNorm(from.Normalized(), to.Normalized());
	}

	inline Scalar Vector2::SignedAngleNorm(Vector2 nFrom, Vector2 nTo)
    {
    	float dot = Vector2::Dot(nFrom, nTo);
    	float det = Vector2::Cross(nFrom, nTo);

    	return Scalar(ATan2(det, dot)) * RAD2DEG;
    }
	
	inline Vector2 Vector2::Perpendicular(Vector2 inDirection)
    {
	    return Vector2(-inDirection.y, inDirection.x);
    }
	
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

#pragma endregion

#pragma region Vector3 Static Functions Implementations

	inline Scalar Vector3::Dot(Vector3 v1, Vector3 v2)
	{
		return Scalar(XMVector3Dot(v1, v2));
	}

	inline Scalar Vector3::Cross(Vector3 v1, Vector3 v2)
	{
		return Scalar(XMVector3Cross(v1, v2));
	}

	inline Vector3 Vector3::Reflect(Vector3 v, Vector3 normal)
	{
		return Vector3(XMVector3Reflect(v, normal));
	}

	inline Scalar Vector3::Distance(Vector3 a, Vector3 b)
	{
		return (a - b).Length();
	}

	inline Scalar Vector3::SqrDistance(Vector3 a, Vector3 b)
	{
		return (a - b).SqrLength();
	}

	inline Vector3 Vector3::ClampLength(Vector3 v, float maxLength)
	{
		if (v.SqrLength() > maxLength * maxLength)
		{
			return v.Normalized() * maxLength;
		}
		return v;
	}

	inline Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity,
		float smoothTime, float deltaTime, float maxSpeed)
    {
    	// Prevent div by zero
    	smoothTime = Math::Max(EPSILON, smoothTime);

    	const float k_omega = 2.0f / smoothTime;
    	const float x = k_omega * deltaTime;
    	const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

    	Vector3 change = target - current;
    	Vector3 originalTo = target;

    	change = Vector3::ClampLength(change, maxSpeed * smoothTime);

    	target = current - change;
    	Vector3 temp = (currentVelocity + k_omega * change) * deltaTime;
    	currentVelocity = (currentVelocity - k_omega * temp) * exp;
    	Vector3 output = target + (change + temp) * exp;

    	// Prevent overshooting
    	Vector3 origToCurrent = originalTo - current;
    	Vector3 outToOriginal = output - originalTo;
    	if(Vector3::Dot(origToCurrent, outToOriginal) > 0.0f)
    	{
    		output = originalTo;
    		currentVelocity = Vector3::zero;
    	}

    	return output;
    }

	inline Scalar Vector3::Angle(Vector3 from, Vector3 to)
	{
		return Vector3::AngleNorm(from.Normalized(), to.Normalized());
	}

	inline Scalar Vector3::AngleNorm(Vector3 nFrom, Vector3 nTo)
	{
		return Scalar(XMVector3AngleBetweenNormals(nFrom, nTo)) * RAD2DEG;
	}

	inline Scalar Vector3::AngleFast(Vector3 nFrom, Vector3 nTo)
	{
		return Scalar(XMVector3AngleBetweenNormalsEst(nFrom, nTo)) * RAD2DEG;
	}

	inline Scalar Vector3::SignedAngle(Vector3 from, Vector3 to)
	{
		return Vector3::SignedAngleNorm(from.Normalized(), to.Normalized());
	}

	inline Scalar Vector3::SignedAngleNorm(Vector3 nFrom, Vector3 nTo)
	{
		float dot = Vector3::Dot(nFrom, nTo);
		float det = Vector3::Cross(nFrom, nTo);

		return Scalar(ATan2(det, dot)) * RAD2DEG;
	}

	inline Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
	{
		return Math::Lerp(a, b, t);
	}

	inline Vector3 Vector3::Lerp(Vector3 a, Vector3 b, Vector3 t)
	{
		return Math::Lerp(a, b, t);
	}

	inline Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
	{
		return Math::LerpUnclamped(a, b, t);
	}

	inline Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, Vector3 t)
	{
		return Math::LerpUnclamped(a, b, t);
	}

	inline Vector3 Vector3::Min(Vector3 a, Vector3 b)
	{
		return Math::Min(a, b);
	}

	inline Vector3 Vector3::Max(Vector3 a, Vector3 b)
	{
		return Math::Max(a, b);
	}

	inline Vector3 Vector3::Clamp(Vector3 v, Vector3 a, Vector3 b)
	{
		return Math::Clamp(v, a, b);
	}

	inline Vector3 Vector3::Clamp01(Vector3 v)
	{
		return Math::Clamp01(v);
	}

#pragma endregion
	
}
