#pragma once

#include "percision.h"
#include "Vector3.h"
#include <cmath>
#include <algorithm>

namespace tachyon {

class Matrix3 {
public:
    real m[3][3];

    Matrix3() {
        m[0][0] = m[1][1] = m[2][2] = 1.0f;
        m[0][1] = m[0][2] = m[1][0] = 0.0f;
        m[1][2] = m[2][0] = m[2][1] = 0.0f;
    }

    void setDiagonal(real a, real b, real c) {
        m[0][0] = a; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = b; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = c;
    }

    Vector3 transform(const Vector3& v) const {
        return (*this) * v;
    }

    Vector3 operator*(const Vector3& v) const {
        return Vector3(
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        );
    }

    Matrix3 transpose() const {
        Matrix3 result;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                result.m[r][c] = m[c][r];
        return result;
    }

    Matrix3 inverse() const {
        real t4 = m[0][0]*m[1][1];
        real t6 = m[0][0]*m[1][2];
        real t8 = m[0][1]*m[1][0];
        real t10 = m[0][2]*m[1][0];
        real t12 = m[0][1]*m[2][0];
        real t14 = m[0][2]*m[2][0];

        real det = t4*m[2][2] - t6*m[2][1] - t8*m[2][2]
                 + t10*m[2][1] + t12*m[1][2] - t14*m[1][1];

        if (std::fabs(det) < 1e-10f) return Matrix3();

        real invDet = 1.0f / det;
        Matrix3 result;

        result.m[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]) * invDet;
        result.m[0][1] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]) * invDet;
        result.m[0][2] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]) * invDet;
        result.m[1][0] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]) * invDet;
        result.m[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]) * invDet;
        result.m[1][2] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]) * invDet;
        result.m[2][0] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]) * invDet;
        result.m[2][1] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]) * invDet;
        result.m[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]) * invDet;

        return result;
    }

    Matrix3 linearInterpolate(const Matrix3& other, real prop) const {
        Matrix3 result;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                result.m[r][c] = m[r][c] * (1.0f - prop) + other.m[r][c] * prop;
        return result;
    }
};

}
