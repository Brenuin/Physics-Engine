#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"

namespace tachyon {

class Matrix4 {
public:
    real data[12];

    Matrix4() { std::fill(data, data + 12, 0.0f); }

    Vector3 operator*(const Vector3 &vector) const {
        return {
            data[0]*vector.x + data[1]*vector.y + data[2]*vector.z + data[3],
            data[4]*vector.x + data[5]*vector.y + data[6]*vector.z + data[7],
            data[8]*vector.x + data[9]*vector.y + data[10]*vector.z + data[11]
        };
    }

    static Matrix4 fromPositionOrientation(const Vector3 &pos, const Quaternion &q) {
        Matrix4 result;
        real w = q.r, x = q.i, y = q.j, z = q.k;

        result.data[0] = 1 - 2*y*y - 2*z*z;
        result.data[1] = 2*x*y - 2*z*w;
        result.data[2] = 2*x*z + 2*y*w;
        result.data[3] = pos.x;

        result.data[4] = 2*x*y + 2*z*w;
        result.data[5] = 1 - 2*x*x - 2*z*z;
        result.data[6] = 2*y*z - 2*x*w;
        result.data[7] = pos.y;

        result.data[8] = 2*x*z - 2*y*w;
        result.data[9] = 2*y*z + 2*x*w;
        result.data[10] = 1 - 2*x*x - 2*y*y;
        result.data[11] = pos.z;

        return result;
    }

    Matrix3 toMatrix3() const {
        Matrix3 m3;
        m3.m[0][0] = data[0];  m3.m[0][1] = data[1];  m3.m[0][2] = data[2];
        m3.m[1][0] = data[4];  m3.m[1][1] = data[5];  m3.m[1][2] = data[6];
        m3.m[2][0] = data[8];  m3.m[2][1] = data[9];  m3.m[2][2] = data[10];
        return m3;
    }
};

}
