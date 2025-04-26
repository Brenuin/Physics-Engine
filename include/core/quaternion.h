#pragma once
#include "Vector3.h"

namespace tachyon {

class Quaternion {
public:
    union {
        struct {
            real r, i, j, k;
        };
        real data[4];
    };

    Quaternion() : r(1), i(0), j(0), k(0) {}
    Quaternion(real r, real i, real j, real k) : r(r), i(i), j(j), k(k) {}

    void normalize() {
        real d = r*r + i*i + j*j + k*k;
        if (d == 0) {
            r = 1; return;
        }
        d = ((real)1.0) / sqrt(d);
        r *= d; i *= d; j *= d; k *= d;
    }

    void operator*=(const Quaternion &mult) {
        Quaternion q = *this;
        r = q.r*mult.r - q.i*mult.i - q.j*mult.j - q.k*mult.k;
        i = q.r*mult.i + q.i*mult.r + q.j*mult.k - q.k*mult.j;
        j = q.r*mult.j + q.j*mult.r + q.k*mult.i - q.i*mult.k;
        k = q.r*mult.k + q.k*mult.r + q.i*mult.j - q.j*mult.i;
    }

    void rotateByVector(const Vector3 &vector) {
        Quaternion q(0, vector.x, vector.y, vector.z);
        *this *= q;
    }

    void addScaledVector(const Vector3 &vector, real scale) {
        Quaternion q(0, vector.x * scale, vector.y * scale, vector.z * scale);
        q *= *this;
        r += q.r * 0.5f;
        i += q.i * 0.5f;
        j += q.j * 0.5f;
        k += q.k * 0.5f;
    }
};

}
