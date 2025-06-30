#pragma once

using namespace DirectX;

namespace ReverieEngine::Math
{
    class Scalar
    {
    public:
        static const Scalar zero;
        static const Scalar one;
        
        Scalar() = default;
        Scalar(const Scalar& other) { m_simdVector = other.m_simdVector; }
        Scalar(float f) { m_simdVector = XMVectorReplicate(f); }
        explicit Scalar(FXMVECTOR vec) : m_simdVector(vec) {}

        operator XMVECTOR() const { return m_simdVector; }
        operator float() const { return XMVectorGetX(m_simdVector); }

    private:
        XMVECTOR m_simdVector;
    };

    inline Scalar operator- (Scalar s) { return Scalar(XMVectorNegate(s)); }
    inline Scalar operator+ (Scalar s1, Scalar s2) { return Scalar(XMVectorAdd(s1, s2)); }
    inline Scalar operator- (Scalar s1, Scalar s2) { return Scalar(XMVectorSubtract(s1, s2)); }
    inline Scalar operator* ( Scalar s1, Scalar s2 ) { return Scalar(XMVectorMultiply(s1, s2)); }
    inline Scalar operator/ ( Scalar s1, Scalar s2 ) { return Scalar(XMVectorDivide(s1, s2)); }
    inline Scalar operator+ ( Scalar s1, float s2 ) { return s1 + Scalar(s2); }
    inline Scalar operator- ( Scalar s1, float s2 ) { return s1 - Scalar(s2); }
    inline Scalar operator* ( Scalar s1, float s2 ) { return s1 * Scalar(s2); }
    inline Scalar operator/ ( Scalar s1, float s2 ) { return s1 / Scalar(s2); }
    inline Scalar operator+ ( float s1, Scalar s2 ) { return Scalar(s1) + s2; }
    inline Scalar operator- ( float s1, Scalar s2 ) { return Scalar(s1) - s2; }
    inline Scalar operator* ( float s1, Scalar s2 ) { return Scalar(s1) * s2; }
    inline Scalar operator/ ( float s1, Scalar s2 ) { return Scalar(s1) / s2; }
}