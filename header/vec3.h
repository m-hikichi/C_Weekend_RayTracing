#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class Vec3
{
public:
    double x, y, z;

    // コンストラクタ
    Vec3() : x(.0), y(.0), z(.0) {}
    Vec3(double _i) : x(_i), y(_i), z(_i) {}
    Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    // デストラクタ
    ~Vec3() {}

    // ベクトル同士の演算
    inline Vec3 operator+(const Vec3 &v) const
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    inline Vec3 operator+=(const Vec3 &v)
    {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }

    inline Vec3 operator-(const Vec3 &v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    inline Vec3 operator-=(const Vec3 &v)
    {
        x -= v.x, y -= v.y, z -= v.z;
        return *this;
    }

    inline Vec3 operator*(const Vec3 &v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    inline Vec3 operator*=(const Vec3 &v)
    {
        x *= v.x, y *= v.y, z *= v.z;
        return *this;
    }

    inline Vec3 operator/(const Vec3 &v) const
    {
        return Vec3(x / v.x, y / v.y, z / v.z);
    }

    inline Vec3 operator/=(const Vec3 &v)
    {
        x /= v.x, y /= v.y, z /= v.z;
        return *this;
    }

    // ベクトルとスカラーの演算
    inline Vec3 operator+(const double s) const
    {
        return Vec3(x + s, y + s, z + s);
    }

    inline friend Vec3 operator+(const double s, const Vec3 &v)
    {
        return Vec3(s + v.x, s + v.y, s + v.z);
    }

    inline Vec3 operator+=(const double s)
    {
        x += s, y += s, z += s;
        return *this;
    }

    inline Vec3 operator-(const double s) const
    {
        return Vec3(x - s, y - s, z - s);
    }

    inline friend Vec3 operator-(const double s, const Vec3 &v)
    {
        return Vec3(s - v.x, s - v.y, s - v.z);
    }

    inline Vec3 operator-=(const double s)
    {
        x -= s, y -= s, z -= s;
        return *this;
    }

    inline Vec3 operator*(const double s) const
    {
        return Vec3(x * s, y * s, z * s);
    }

    inline friend Vec3 operator*(const double s, const Vec3 &v)
    {
        return Vec3(s * v.x, s * v.y, s * v.z);
    }

    inline Vec3 operator*=(const double s)
    {
        x *= s, y *= s, z *= s;
        return *this;
    }

    inline Vec3 operator/(const double s) const
    {
        return Vec3(x / s, y / s, z / s);
    }

    inline friend Vec3 operator/(const double s, const Vec3 &v)
    {
        return Vec3(s / v.x, s / v.y, s / v.z);
    }

    inline Vec3 operator/=(const double s)
    {
        x /= s, y /= s, z /= s;
        return *this;
    }

    // イコール演算子
    inline bool operator==(const Vec3 &v) const
    {
        if (x == v.x && y == v.y && z == v.z)
            return true;
        else
            return false;
    }

    // マイナス演算
    inline Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    // ノルム値
    double norm() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    // 正規化
    Vec3 normalize() const
    {
        double norm = this->norm();
        return Vec3(
            x / norm,
            y / norm,
            z / norm);
    }

    // 内積
    inline friend double dot(const Vec3 &v1, const Vec3 &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    // 外積
    inline friend Vec3 cross(const Vec3 &v1, const Vec3 &v2)
    {
        return Vec3(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Vec3 &v)
    {
        stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return stream;
    }
};

#endif