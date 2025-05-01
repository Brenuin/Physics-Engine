#pragma once

#include <cmath>
#include "percision.h"

#define real_sqrt sqrtf

namespace tachyon {

    class Vector3 {

    public:
        real x, y, z;

    private:
        real pad; // Padding for alignment or future use

    public:
        Vector3() : x(0), y(0), z(0) {}

        Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

        void invert() {
            x = -x;
            y = -y;
            z = -z;
        }

        real magnitude() const {
            return real_sqrt(x * x + y * y + z * z);
        }
        real magnitudeSquared() const {
            return (x * x + y * y + z * z);
        }

        void normalize() {
            real mag = magnitude();
            if (mag > 0) {
                x /= mag;
                y /= mag;
                z /= mag;
            }
        }
        Vector3 normalized() const {
            Vector3 copy = *this;
            copy.normalize();
            return copy;
        }
        void clear() {
            x = y = z = 0.0f;
        }
        

        void operator*=(const real value) {
            x *= value;
            y *= value;
            z *= value;
        }

        Vector3 operator*(const real value) const {
            return Vector3(x * value, y * value, z * value);
        }

        void operator+=(const Vector3& v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        Vector3 operator+(const Vector3& v) const {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        void operator-=(const Vector3& v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        Vector3 operator-(const Vector3& v) const {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }
        Vector3 operator-() const {
            return Vector3(-x, -y, -z);
        }
        


        void addScaledVector(const Vector3& vector, real scale){
            x += vector.x*scale;
            y += vector.y*scale;
            z += vector.z*scale;
        }

        Vector3 componentProduct(const Vector3 &vector) const{
            return Vector3(x * vector.x, y * vector.y, z * vector.z);
        }

        void componentProductUpdate(const Vector3 &vector){
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;
        }
        real scalarProduct(const Vector3 &vector) const{
            return x*vector.x + y*vector.y + z*vector.z;
        }
        real operator *(const Vector3 &vector) const{
            return x*vector.x + y*vector.y + z*vector.z;
        }
        Vector3 operator/(const real value) const {
            return Vector3(x / value, y / value, z / value);
        }
        
        Vector3 vectorProduct(const Vector3 &vector) const{
            return Vector3(y*vector.z-z*vector.y, z*vector.x-x*vector.z, x*vector.y-y*vector.x);
        }
        void operator %=(const Vector3 &vector){
            *this = vectorProduct(vector);
        }
        Vector3 operator%(const Vector3 &vector) const{
            return Vector3(y*vector.z-z*vector.y, z*vector.x-x*vector.z, x*vector.y-y*vector.x);
        }
    };

} // namespace cyclone


