#pragma once

#include "Scalar.h"

using namespace DirectX;

namespace ReverieEngine
{
    namespace Math
    {
        class Vector3;
        class Vector4;

        class alignas(16) Vector2
        {
            public:
            union
            {
                struct
                {
                    float x, y;
                    // Unused but reserved for alignment
                    float z, w;
                };
                struct { float u, v; };
                XMVECTOR simdVector;
            };

            // Static constants for common vectors
            static const Vector2 zero;
            static const Vector2 one;
            static const Vector2 right;
            static const Vector2 left;
            static const Vector2 up;
            static const Vector2 down;
            static const Vector2 positiveInfinity;
            static const Vector2 negativeInfinity;
        
            Vector2() = default;
            Vector2(float _x, float _y) : simdVector(XMVectorSet(_x, _y, 0.0f, 0.0f)) {}
            Vector2(const XMFLOAT2& v) : simdVector(XMLoadFloat2(&v)) {}

            // Casting operators
            explicit Vector2(FXMVECTOR vec) : simdVector(vec) {}
            explicit Vector2(Scalar scalar) : simdVector(scalar) {}
            explicit Vector2(Vector3 vec);
            explicit Vector2(Vector4 vec);
            operator XMVECTOR() const { return simdVector; }

            Vector2(const Vector2& other) = default;
            Vector2& operator=(const Vector2& vec) = default;
        
            Vector2 operator- () const { return Vector2(XMVectorNegate(simdVector)); }
            Vector2 operator+ (Vector2 vec) const { return Vector2(XMVectorAdd(simdVector, vec.simdVector)); }
            Vector2 operator- (Vector2 vec) const { return Vector2(XMVectorSubtract(simdVector, vec.simdVector)); }
            Vector2 operator* (Vector2 vec) const { return Vector2(XMVectorMultiply(simdVector, vec.simdVector)); }
            Vector2 operator/ (Vector2 vec) const { return Vector2(XMVectorDivide(simdVector, vec.simdVector)); }
            Vector2 operator* (Scalar scalar) const { return Vector2(*this * Vector2(scalar)); }
            Vector2 operator/ (Scalar scalar) const { return Vector2(*this / Vector2(scalar)); }
            Vector2 operator* (float  v2) const { return *this * Scalar(v2); }
            Vector2 operator/ (float  v2) const { return *this / Scalar(v2); }

            Vector2& operator += ( Vector2 v ) { *this = *this + v; return *this; }
            Vector2& operator -= ( Vector2 v ) { *this = *this - v; return *this; }
            Vector2& operator *= ( Vector2 v ) { *this = *this * v; return *this; }
            Vector2& operator /= ( Vector2 v ) { *this = *this / v; return *this; }

            bool operator==(const Vector2& rhs) const { return XMVector2Equal(simdVector, rhs.simdVector); }
            bool operator!=(const Vector2& rhs) const { return !(*this == rhs); }
        
            friend Vector2 operator* (Scalar scalar, Vector2 vec) { return Vector2(scalar) * vec; }
            friend Vector2 operator/ (Scalar scalar, Vector2 vec) { return Vector2(scalar) / vec; }
            friend Vector2 operator* (float scalar, Vector2 vec) { return Scalar(scalar) * vec; }
            friend Vector2 operator/ (float scalar, Vector2 vec) { return Scalar(scalar) / vec; }
        
            // Non-const version for assignment: vec[0] = 1.0f;
            float& operator[](int index) {
                if (index == 0) return x;
                if (index == 1) return y;
                throw std::out_of_range("Index out of range for Vector2");
            }

            // Const version for read-only access: float a = vec[1];
            float operator[](int index) const {
                if (index == 0) return x;
                if (index == 1) return y;
                throw std::out_of_range("Index out of range for Vector2");
            }

#pragma region Math member functions
            Scalar Length() const { return Scalar(XMVector2Length(simdVector)); }
            Scalar SqrLength() const { return Scalar(XMVector2LengthSq(simdVector)); }
            Scalar RecipLength() const { return Scalar(XMVector2ReciprocalLength(simdVector)); }
            Vector2 Normalized() const { return Vector2(XMVector2Normalize(simdVector)); }
            void Normalize() { simdVector = XMVector2Normalize(simdVector); }
            /**
             * Returns an approximate normalized vector.
             * 
             * This uses a fast, lower-precision reciprocal square root estimate
             * for better performance at the cost of some accuracy.
             * 
             * Suitable for use cases where speed is more important than exact precision,
             * such as visual effects or non-critical math calculations.
             */
            Vector2 FastNormalized() const { return Vector2(XMVector2NormalizeEst(simdVector)); }
            /**
             * Normalizes the vector approximately in place using NormalizeEst.
             * 
             * This method uses a fast, lower-precision reciprocal square root estimate
             * to improve performance at the cost of some accuracy.
             * 
             * Use FastNormalize when speed is prioritized over exact precision,
             * such as in visual effects or non-critical calculations.
             */
            void FastNormalize() { simdVector = XMVector2NormalizeEst(simdVector); }
#pragma endregion

#pragma region Math static functions
            static Scalar Dot(Vector2 v1, Vector2 v2);
            static Scalar Cross(Vector2 v1, Vector2 v2);
            static Vector2 Reflect(Vector2 v, Vector2 normal);
            static Scalar Distance(Vector2 a, Vector2 b);
            static Scalar SqrDistance(Vector2 a, Vector2 b);
            static Vector2 ClampLength(Vector2 v, float maxLength);
            static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime,
                float deltaTime, float maxSpeed = std::numeric_limits<float>::infinity());
            // Gets the unsigned angle in degrees between from and to, two arbitrary vectors.
            static Scalar Angle(Vector2 from, Vector2 to);
            // Gets the unsigned angle in degrees between from and to, assuming both are normalized.
            static Scalar AngleNorm(Vector2 from, Vector2 to);
            // Gets the estimated unsigned angle in degrees between from and to, assuming both are normalized.
            // More efficient at the cost of accuracy.
            static Scalar AngleFast(Vector2 nFrom, Vector2 nTo);
            // Gets the signed angle in degrees between from and to.
            static Scalar SignedAngle(Vector2 from, Vector2 to);
            // Gets the signed angle in degrees between from and to, assuming both are normalized.
            static Scalar SignedAngleNorm(Vector2 nFrom, Vector2 nTo);
            static Vector2 Perpendicular(Vector2 inDirection);
            static Vector2 Lerp(Vector2 a, Vector2 b, float t);
            static Vector2 Lerp(Vector2 a, Vector2 b, Vector2 t);
            static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
            static Vector2 LerpUnclamped(Vector2 a, Vector2 b, Vector2 t);
            static Vector2 Min(Vector2 a, Vector2 b);
            static Vector2 Max(Vector2 a, Vector2 b);
            static Vector2 Clamp(Vector2 v, Vector2 a, Vector2 b);
            static Vector2 Clamp01(Vector2 v);
#pragma endregion
        
            // Swizzling support
            Vector2 GetYX() const { return Vector2(y, x); }
        
            std::string ToString() const { return std::format("Vector2({}, {})", x, y); }
            friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
            {
                os << "Vector2(" << vec.x << ", " << vec.y << ")";
                return os;
            }
        };

        const Vector2 Vector2::zero = Vector2(0.0f);
        const Vector2 Vector2::one = Vector2(1.0f);
        const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
        const Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
        const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
        const Vector2 Vector2::down = Vector2(0.0f, -1.0f);
        const Vector2 Vector2::positiveInfinity = Vector2(std::numeric_limits<float>::infinity());
        const Vector2 Vector2::negativeInfinity = Vector2(-std::numeric_limits<float>::infinity());

        class alignas(16) Vector3
        {
            public:
            union
            {
                struct {
                    float x, y, z;
                    // Unused but reserved for alignment
                    float w;
                };
                struct { float u, v; } uv;
                XMVECTOR simdVector;
            };

            // Static constants for common vectors
            static const Vector3 zero;
            static const Vector3 one;
            static const Vector3 right;
            static const Vector3 left;
            static const Vector3 forward;
            static const Vector3 backward;
            static const Vector3 up;
            static const Vector3 down;
            static const Vector3 positiveInfinity;
            static const Vector3 negativeInfinity;

            Vector3() = default;
            Vector3(float _x, float _y, float _z) : simdVector(XMVectorSet(_x, _y, _z, 0.0f)) {}
            Vector3(const XMFLOAT3& v) : simdVector(XMLoadFloat3(&v)) {}
            Vector3(Vector2& vec2, float _z) : simdVector(XMVectorSet(vec2.x, vec2.y, _z, 0.0f)) {}

            // Casting operators
            explicit Vector3(Scalar scalar) : simdVector(scalar) {}
            explicit Vector3(Vector2 vec) : simdVector(XMVectorSet(vec.x, vec.y, 0.0f, 0.0f)) {}
            explicit Vector3(Vector4 vec);
            explicit Vector3(FXMVECTOR vec) : simdVector(vec) {}
            operator XMVECTOR() const { return simdVector; }

            Vector3(const Vector3& other) = default;
            Vector3& operator=(const Vector3& vec) = default;
        
            Vector3 operator- () const { return Vector3(XMVectorNegate(simdVector)); }
            Vector3 operator+ (Vector3 vec) const { return Vector3(XMVectorAdd(simdVector, vec.simdVector)); }
            Vector3 operator- (Vector3 vec) const { return Vector3(XMVectorSubtract(simdVector, vec.simdVector)); }
            Vector3 operator* (Vector3 vec) const { return Vector3(XMVectorMultiply(simdVector, vec.simdVector)); }
            Vector3 operator/ (Vector3 vec) const { return Vector3(XMVectorDivide(simdVector, vec.simdVector)); }
            Vector3 operator* (Scalar scalar) const { return Vector3(*this * Vector3(scalar)); }
            Vector3 operator/ (Scalar scalar) const { return Vector3(*this / Vector3(scalar)); }
            Vector3 operator* (float scalar) const { return *this * Scalar(scalar); }
            Vector3 operator/ (float scalar) const { return *this / Scalar(scalar); }

            Vector3& operator += ( Vector3 v ) { *this = *this + v; return *this; }
            Vector3& operator -= ( Vector3 v ) { *this = *this - v; return *this; }
            Vector3& operator *= ( Vector3 v ) { *this = *this * v; return *this; }
            Vector3& operator /= ( Vector3 v ) { *this = *this / v; return *this; }

            bool operator==(const Vector3& rhs) const { return XMVector3Equal(simdVector, rhs.simdVector); }
            bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }
        
            friend Vector3 operator* (Scalar scalar, Vector3 vec) { return Vector3(scalar) * vec; }
            friend Vector3 operator/ (Scalar scalar, Vector3 vec) { return Vector3(scalar) / vec; }
            friend Vector3 operator* (float scalar, Vector3 vec) { return Scalar(scalar) * vec; }
            friend Vector3 operator/ (float scalar, Vector3 vec) { return Scalar(scalar) / vec; }
        
            // Non-const version for assignment: vec[0] = 1.0f;
            float& operator[](int index) {
                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                throw std::out_of_range("Index out of range for Vector3");
            }

            // Const version for read-only access: float a = vec[1];
            float operator[](int index) const {
                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                throw std::out_of_range("Index out of range for Vector3");
            }

#pragma region Math member functions
            Scalar Length() const { return Scalar(XMVector3Length(simdVector)); }
            Scalar SqrLength() const { return Scalar(XMVector3LengthSq(simdVector)); }
            Scalar RecipLength() const { return Scalar(XMVector3ReciprocalLength(simdVector)); }
            Vector3 Normalized() const { return Vector3(XMVector3Normalize(simdVector)); }
            void Normalize() { simdVector = XMVector3Normalize(simdVector); }
            /**
             * Returns an approximate normalized vector.
             * 
             * This uses a fast, lower-precision reciprocal square root estimate
             * for better performance at the cost of some accuracy.
             * 
             * Suitable for use cases where speed is more important than exact precision,
             * such as visual effects or non-critical math calculations.
             */
            Vector3 FastNormalized() const { return Vector3(XMVector3NormalizeEst(simdVector)); }
            /**
             * Normalizes the vector approximately in place using NormalizeEst.
             * 
             * This method uses a fast, lower-precision reciprocal square root estimate
             * to improve performance at the cost of some accuracy.
             * 
             * Use FastNormalize when speed is prioritized over exact precision,
             * such as in visual effects or non-critical calculations.
             */
            void FastNormalize() { simdVector = XMVector3NormalizeEst(simdVector); }
#pragma endregion

#pragma region Math static functions
            static Scalar Dot(Vector3 v1, Vector3 v2);
            static Scalar Cross(Vector3 v1, Vector3 v2);
            static Vector3 Reflect(Vector3 v, Vector3 normal);
            static Scalar Distance(Vector3 a, Vector3 b);
            static Scalar SqrDistance(Vector3 a, Vector3 b);
            static Vector3 ClampLength(Vector3 v, float maxLength);
            static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, float smoothTime,
                float deltaTime, float maxSpeed = std::numeric_limits<float>::infinity());
            // Gets the unsigned angle in degrees between from and to, two arbitrary vectors.
            static Scalar Angle(Vector3 from, Vector3 to);
            // Gets the unsigned angle in degrees between from and to, assuming both are normalized.
            static Scalar AngleNorm(Vector3 from, Vector3 to);
            // Gets the estimated unsigned angle in degrees between from and to, assuming both are normalized.
            // More efficient at the cost of accuracy.
            static Scalar AngleFast(Vector3 nFrom, Vector3 nTo);
            // Gets the signed angle in degrees between from and to.
            static Scalar SignedAngle(Vector3 from, Vector3 to);
            // Gets the signed angle in degrees between from and to, assuming both are normalized.
            static Scalar SignedAngleNorm(Vector3 nFrom, Vector3 nTo);
            static Vector3 Lerp(Vector3 a, Vector3 b, float t);
            static Vector3 Lerp(Vector3 a, Vector3 b, Vector3 t);
            static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
            static Vector3 LerpUnclamped(Vector3 a, Vector3 b, Vector3 t);
            static Vector3 Min(Vector3 a, Vector3 b);
            static Vector3 Max(Vector3 a, Vector3 b);
            static Vector3 Clamp(Vector3 v, Vector3 a, Vector3 b);
            static Vector3 Clamp01(Vector3 v);
#pragma endregion
        
#pragma region Swizzling Support
            Vector2 GetXY() const { return Vector2(x, y); }
            Vector2 GetXZ() const { return Vector2(x, z); }
            Vector2 GetYZ() const { return Vector2(y, z); }
            Vector2 GetYX() const { return Vector2(y, x); }
            Vector2 GetZX() const { return Vector2(z, x); }
            Vector2 GetZY() const { return Vector2(z, y); }
        
            Vector3 GetXZY() const {return Vector3(x, z, y); }
            Vector3 GetYXZ() const {return Vector3(y, x, z); }
            Vector3 GetYZX() const {return Vector3(y, z, x); }
            Vector3 GetZXY() const {return Vector3(z, x, y); }
            Vector3 GetZYX() const {return Vector3(z, y, x); }
#pragma endregion
 
            void SetXY(Vector2 vec) { x = vec.x; y = vec.y; }
            void SetXY(float _x, float _y) { x = _x, y = _y; }
            void SetXZ(Vector2 vec) { x = vec.x; z = vec.y; }
            void SetXZ(float _x, float _z) { x = _x; z = _z; }
            void SetYZ(Vector2 vec) { y = vec.x; z = vec.y; }
            void SetYZ(float _y, float _z) { y = _y; z = _z; }
        
            std::string ToString() const { return std::format("Vector3({}, {}, {})", x, y, z); }
            friend std::ostream& operator<<(std::ostream& os, const Vector3& vec)
            {
                os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
                return os;
            }
        };

        // Static constants for Vector3
        const Vector3 Vector3::zero = Vector3(XMVectorZero());
        const Vector3 Vector3::one = Vector3(1.0f);
        const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
        const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
        const Vector3 Vector3::forward = Vector3(0.0f, 1.0f, 0.0f);
        const Vector3 Vector3::backward = Vector3(0.0f, -1.0f, 0.0f);
        const Vector3 Vector3::up = Vector3(0.0f, 0.0f, 1.0f);
        const Vector3 Vector3::down = Vector3(0.0f, 0.0f, -1.0f);
        const Vector3 Vector3::positiveInfinity = Vector3(std::numeric_limits<float>::infinity());
        const Vector3 Vector3::negativeInfinity = Vector3(-std::numeric_limits<float>::infinity());
    
        class alignas(16) Vector4
        {
            public:
            union
            {
                struct { float x, y, z, w; };
                struct { float u, v; } uv;
                XMVECTOR simdVector;
            };

            // Static constants for common vectors
            static const Vector4 zero;
            static const Vector4 one;
            static const Vector4 positiveInfinity;
            static const Vector4 negativeInfinity;

            Vector4() = default;
            Vector4(float _x, float _y, float _z, float _w) : simdVector(XMVectorSet(_x, _y, _z, _w)) {}
            Vector4(const XMFLOAT4& v) : simdVector(XMLoadFloat4(&v)) {}
            Vector4(Vector2 vec2, float _z, float _w) : simdVector(XMVectorSet(vec2.x, vec2.y, _z, _w)) {}
            Vector4(Vector3 vec3, float _w) : simdVector(XMVectorSetW(vec3, _w)) {}

            // Casting operators
            explicit Vector4(Scalar scalar) : simdVector(scalar) {}
            explicit Vector4(Vector2 vec) : simdVector(XMVectorSet(vec.x, vec.y, 0.0f, 0.0f)) {}
            explicit Vector4(Vector3 vec) : simdVector(XMVectorSet(vec.x, vec.y, vec.z, 0.0f)) {}
            explicit Vector4(FXMVECTOR vec) : simdVector(vec) {}
            operator XMVECTOR() const { return simdVector; }

            Vector4(const Vector4& other) = default;
            Vector4& operator=(const Vector4& vec) = default;
        
            Vector4 operator- () const { return Vector4(XMVectorNegate(simdVector)); }
            Vector4 operator+ (Vector4 vec) const { return Vector4(XMVectorAdd(simdVector, vec.simdVector)); }
            Vector4 operator- (Vector4 vec) const { return Vector4(XMVectorSubtract(simdVector, vec.simdVector)); }
            Vector4 operator* (Vector4 vec) const { return Vector4(XMVectorMultiply(simdVector, vec.simdVector)); }
            Vector4 operator/ (Vector4 vec) const { return Vector4(XMVectorDivide(simdVector, vec.simdVector)); }
            Vector4 operator* (Scalar scalar) const { return Vector4(*this * Vector4(scalar)); }
            Vector4 operator/ (Scalar scalar) const { return Vector4(*this / Vector4(scalar)); }
            Vector4 operator* (float scalar) const { return *this * Scalar(scalar); }
            Vector4 operator/ (float scalar) const { return *this / Scalar(scalar); }

            Vector4& operator += ( Vector4 v ) { *this = *this + v; return *this; }
            Vector4& operator -= ( Vector4 v ) { *this = *this - v; return *this; }
            Vector4& operator *= ( Vector4 v ) { *this = *this * v; return *this; }
            Vector4& operator /= ( Vector4 v ) { *this = *this / v; return *this; }

            bool operator==(const Vector4& rhs) const { return XMVector4Equal(simdVector, rhs.simdVector); }
            bool operator!=(const Vector4& rhs) const { return !(*this == rhs); }

            friend Vector4 operator* (Scalar scalar, Vector4 vec) { return Vector4(scalar) * vec; }
            friend Vector4 operator/ (Scalar scalar, Vector4 vec) { return Vector4(scalar) / vec; }
            friend Vector4 operator* (float scalar, Vector4 vec) { return Scalar(scalar) * vec; }
            friend Vector4 operator/ (float scalar, Vector4 vec) { return Scalar(scalar) / vec; }

            // Non-const version for assignment: vec[0] = 1.0f;
            float& operator[](int index) {
                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                if (index == 3) return w;
                throw std::out_of_range("Index out of range for Vector4");
            }

            // Const version for read-only access: float a = vec[1];
            float operator[](int index) const {
                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                if (index == 3) return w;
                throw std::out_of_range("Index out of range for Vector4");
            }

#pragma region Math member functions
            Scalar Length() const { return Scalar(XMVector4Length(simdVector)); }
            Scalar SqrLength() const { return Scalar(XMVector4LengthSq(simdVector)); }
            Scalar RecipLength() const { return Scalar(XMVector4ReciprocalLength(simdVector)); }
            Vector4 Normalized() const { return Vector4(XMVector4Normalize(simdVector)); }
            void Normalize() { simdVector = XMVector4Normalize(simdVector); }
            /**
             * Returns an approximate normalized vector.
             * 
             * This uses a fast, lower-precision reciprocal square root estimate
             * for better performance at the cost of some accuracy.
             * 
             * Suitable for use cases where speed is more important than exact precision,
             * such as visual effects or non-critical math calculations.
             */
            Vector4 FastNormalized() const { return Vector4(XMVector4NormalizeEst(simdVector)); }
            /**
             * Normalizes the vector approximately in place using NormalizeEst.
             * 
             * This method uses a fast, lower-precision reciprocal square root estimate
             * to improve performance at the cost of some accuracy.
             * 
             * Use FastNormalize when speed is prioritized over exact precision,
             * such as in visual effects or non-critical calculations.
             */
            void FastNormalize() { simdVector = XMVector4NormalizeEst(simdVector); }
#pragma endregion

#pragma region Math static functions
        
#pragma endregion
        
#pragma region Swizzling Support
            Vector2 GetXY() const { return Vector2(x, y); }
            Vector2 GetXZ() const { return Vector2(x, z); }
            Vector2 GetXW() const { return Vector2(x, w); }
            Vector2 GetYX() const { return Vector2(y, x); }
            Vector2 GetYZ() const { return Vector2(y, z); }
            Vector2 GetYW() const { return Vector2(y, w); }
            Vector2 GetZX() const { return Vector2(z, x); }
            Vector2 GetZY() const { return Vector2(z, y); }
            Vector2 GetZW() const { return Vector2(z, w); }
            Vector2 GetWX() const { return Vector2(w, x); }
            Vector2 GetWY() const { return Vector2(w, y); }
            Vector2 GetWZ() const { return Vector2(w, z); }
        
            Vector3 GetXYZ() const { return Vector3(x, y, z); }
            Vector3 GetXYW() const { return Vector3(x, y, w); }
            Vector3 GetXZY() const { return Vector3(x, z, y); }
            Vector3 GetXZW() const { return Vector3(x, z, w); }
            Vector3 GetXWY() const { return Vector3(x, w, y); }
            Vector3 GetXWZ() const { return Vector3(x, w, z); }
            Vector3 GetYXZ() const { return Vector3(y, x, z); }
            Vector3 GetYXW() const { return Vector3(y, x, w); }
            Vector3 GetYZX() const { return Vector3(y, z, x); }
            Vector3 GetYZW() const { return Vector3(y, z, w); }
            Vector3 GetYWX() const { return Vector3(y, w, x); }
            Vector3 GetYWZ() const { return Vector3(y, w, z); } 
            Vector3 GetZXY() const { return Vector3(z, x, y); }
            Vector3 GetZXW() const { return Vector3(z, x, w); }
            Vector3 GetZYX() const { return Vector3(z, y, x); }
            Vector3 GetZYW() const { return Vector3(z, y, w); }
            Vector3 GetZWX() const { return Vector3(z, w, x); }
            Vector3 GetZWY() const { return Vector3(z, w, y); }
            Vector3 GetWXY() const { return Vector3(w, x, y); }
            Vector3 GetWXZ() const { return Vector3(w, x, z); }
            Vector3 GetWYX() const { return Vector3(w, y, x); }
            Vector3 GetWYZ() const { return Vector3(w, y, z); }
            Vector3 GetWZX() const { return Vector3(w, z, x); }
            Vector3 GetWZY() const { return Vector3(w, z, y); }

            Vector4 GetXYWZ() const { return Vector4(x, y, w, z); }
            Vector4 GetXZYW() const { return Vector4(x, z, y, w); }
            Vector4 GetXZWY() const { return Vector4(x, z, w, y); }
            Vector4 GetXWYZ() const { return Vector4(x, w, y, z); }
            Vector4 GetXWZY() const { return Vector4(x, w, z, y); }
            Vector4 GetYXZW() const { return Vector4(y, x, z, w); }
            Vector4 GetYXWZ() const { return Vector4(y, x, w, z); }
            Vector4 GetYZXW() const { return Vector4(y, z, x, w); }
            Vector4 GetYZWX() const { return Vector4(y, z, w, x); }
            Vector4 GetYWXZ() const { return Vector4(y, w, x, z); }
            Vector4 GetYWZX() const { return Vector4(y, w, z, x); }
            Vector4 GetZXYW() const { return Vector4(z, x, y, w); }
            Vector4 GetZXWY() const { return Vector4(z, x, w, y); }
            Vector4 GetZYXW() const { return Vector4(z, y, x, w); }
            Vector4 GetZYWX() const { return Vector4(z, y, w, x); }
            Vector4 GetZWXY() const { return Vector4(z, w, x, y); }
            Vector4 GetZWYX() const { return Vector4(z, w, y, x); }
            Vector4 GetWXYZ() const { return Vector4(w, x, y, z); }
            Vector4 GetWXZY() const { return Vector4(w, x, z, y); }
            Vector4 GetWYZX() const { return Vector4(w, y, z, x); }
            Vector4 GetWYXZ() const { return Vector4(w, y, x, z); }
            Vector4 GetWZXY() const { return Vector4(w, z, x, y); }
            Vector4 GetWZYX() const { return Vector4(w, z, y, x); }
#pragma endregion

            void SetXY(Vector2 vec) { x = vec.x; y = vec.y; }
            void SetXY(float _x, float _y) { x = _x; y = _y; }
            void SetXZ(Vector2 vec) { x = vec.x; z = vec.y; }
            void SetXZ(float _x, float _z) { x = _x; z = _z; }
            void SetXW(Vector2 vec) { x = vec.x; w = vec.y; }
            void SetXW(float _x, float _w) { x = _x; w = _w; }
            void SetYZ(Vector2 vec) { y = vec.x; z = vec.y; }
            void SetYZ(float _y, float _z) { y = _y; z = _z; }
            void SetYW(Vector2 vec) { y = vec.x; w = vec.y; }
            void SetYW(float _y, float _w) { y = _y; w = _w; }
            void SetZW(Vector2 vec) { z = vec.x; w = vec.y; }
            void SetZW(float _z, float _w) { z = _z; w = _w; }
        
            void SetXYZ(Vector3 vec) { x = vec.x; y = vec.y; z = vec.z; }
            void SetXYZ(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
            void SetXYW(Vector3 vec) { x = vec.x; y = vec.y; w = vec.z; }
            void SetXYW(float _x, float _y, float _w) { x = _x; y = _y; w = _w; }
            void SetXZW(Vector3 vec) { x = vec.x; z = vec.y; w = vec.z; }
            void SetXZW(float _x, float _z, float _w) { x = _x; z = _z; w = _w; }
            void SetYZW(Vector3 vec) { y = vec.x; z = vec.y; w = vec.z; }
            void SetYZW(float _y, float _z, float _w) { y = _y; z = _z; w = _w; }
        
            std::string ToString() const { return std::format("Vector4({}, {}, {}, {})", x, y, z, w); }
            friend std::ostream& operator<<(std::ostream& os, const Vector4& vec)
            {
                os << "Vector4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
                return os;
            }
        };

        // Static constants for Vector3
        const Vector4 Vector4::zero = Vector4(XMVectorZero());
        const Vector4 Vector4::one = Vector4(XMVectorSplatOne());
        const Vector4 Vector4::positiveInfinity = Vector4(std::numeric_limits<float>::infinity());
        const Vector4 Vector4::negativeInfinity = Vector4(-std::numeric_limits<float>::infinity());
    
        inline Vector2::Vector2(Vector3 vec) :
            simdVector(XMVectorSelect(vec.simdVector, XMVectorZero(), XMVectorSet(0, 0, 1, 1)))
        { }

        inline Vector2::Vector2(Vector4 vec) :
            simdVector(XMVectorSelect(vec.simdVector, XMVectorZero(), XMVectorSet(0, 0, 1, 1)))
        { }

        inline Vector3::Vector3(Vector4 vec) :
            simdVector(XMVectorSelect(vec.simdVector, XMVectorZero(), XMVectorSet(0, 0, 0, 1)))
        { }

        // For W != 1, divide XYZ by W.  If W == 0, do nothing
        // Also called a perspective divide
        inline Vector3 MakeHomogeneous(Vector4 v)
        {
            Scalar W = v.w;
            return Vector3(XMVectorSelect(XMVectorDivide(v, W), v, XMVectorEqual(W, XMVectorZero())));
        }
    
        class alignas(16) BoolVector
        {
            public:
            BoolVector( FXMVECTOR vec ) { m_vec = vec; }
            operator XMVECTOR() const { return m_vec; }
            protected:
            XMVECTOR m_vec;
        };
    }

    using Math::Vector2;
    using Math::Vector3;
    using Math::Vector4;
    using Math::BoolVector;
}