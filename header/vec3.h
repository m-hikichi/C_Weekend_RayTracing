#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class VecBase
{
protected:
    double v[3];

public:
    // コンストラクタ
    VecBase() : v{.0, .0, .0} {}
    VecBase(double _i) : v{_i, _i, _i} {}
    VecBase(double _x, double _y, double _z) : v{_x, _y, _z} {}

    // デストラクタ
    ~VecBase() {}

    const double *getV() const { return v; }

    // イコール演算子
    inline bool operator==(const VecBase &vb) const
    {
        return v[0] == vb.v[0] && v[1] == vb.v[1] && v[2] == vb.v[2];
    }

    // マイナス演算
    inline VecBase operator-() const
    {
        return VecBase(-v[0], -v[1], -v[2]);
    }

    // ベクトル同士の演算
    inline VecBase operator+(const VecBase &vb) const
    {
        return VecBase(v[0] + vb.v[0], v[1] + vb.v[1], v[2] + vb.v[2]);
    }

    inline VecBase operator+=(const VecBase &vb)
    {
        v[0] += vb.v[0];
        v[1] += vb.v[1];
        v[2] += vb.v[2];
        return *this;
    }

    inline VecBase operator-(const VecBase &vb) const
    {
        return VecBase(v[0] - vb.v[0], v[1] - vb.v[1], v[2] - vb.v[2]);
    }

    inline VecBase operator-=(const VecBase &vb)
    {
        v[0] -= vb.v[0];
        v[1] -= vb.v[1];
        v[2] -= vb.v[2];
        return *this;
    }

    inline VecBase operator*(const VecBase &vb) const
    {
        return VecBase(v[0] * vb.v[0], v[1] * vb.v[1], v[2] * vb.v[2]);
    }

    inline VecBase operator*=(const VecBase &vb)
    {
        v[0] *= vb.v[0];
        v[1] *= vb.v[1];
        v[2] *= vb.v[2];
        return *this;
    }

    inline VecBase operator/(const VecBase &vb) const
    {
        return VecBase(v[0] / vb.v[0], v[1] / vb.v[1], v[2] / vb.v[2]);
    }

    inline VecBase operator/=(const VecBase &vb)
    {
        v[0] /= vb.v[0];
        v[1] /= vb.v[1];
        v[2] /= vb.v[2];
        return *this;
    }

    // ベクトルとスカラーの演算
    inline VecBase operator+(const double s) const
    {
        return VecBase(v[0] + s, v[1] + s, v[2] + s);
    }

    inline friend VecBase operator+(const double s, const VecBase &vb)
    {
        return VecBase(s + vb.v[0], s + vb.v[1], s + vb.v[2]);
    }

    inline VecBase operator+=(const double s)
    {
        v[0] += s;
        v[1] += s;
        v[2] += s;
        return *this;
    }

    inline VecBase operator-(const double s) const
    {
        return VecBase(v[0] - s, v[1] - s, v[2] - s);
    }

    inline friend VecBase operator-(const double s, const VecBase &vb)
    {
        return VecBase(s - vb.v[0], s - vb.v[1], s - vb.v[2]);
    }

    inline VecBase operator-=(const double s)
    {
        v[0] -= s;
        v[1] -= s;
        v[2] -= s;
        return *this;
    }

    inline VecBase operator*(const double s) const
    {
        return VecBase(v[0] * s, v[1] * s, v[2] * s);
    }

    inline friend VecBase operator*(const double s, const VecBase &vb)
    {
        return VecBase(s * vb.v[0], s * vb.v[1], s * vb.v[2]);
    }

    inline VecBase operator*=(const double s)
    {
        v[0] *= s;
        v[1] *= s;
        v[2] *= s;
        return *this;
    }

    inline VecBase operator/(const double s) const
    {
        return VecBase(v[0] / s, v[1] / s, v[2] / s);
    }

    inline friend VecBase operator/(const double s, const VecBase &vb)
    {
        return VecBase(s / vb.v[0], s / vb.v[1], s / vb.v[2]);
    }

    inline VecBase operator/=(const double s)
    {
        v[0] /= s;
        v[1] /= s;
        v[2] /= s;
        return *this;
    }
};

class Vec3 : public VecBase
{
public:
    // コンストラクタは親クラスのものをそのまま利用
    using VecBase::VecBase;

    // x, y, z メソッド
    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }

    // 代入演算
    inline Vec3 &operator=(const VecBase &vb)
    {
        v[0] = vb.getV()[0];
        v[1] = vb.getV()[1];
        v[2] = vb.getV()[2];
        return *this;
    }

    // 逆ベクトルを取得する関数
    inline Vec3 inverse() const
    {
        return Vec3(-x(), -y(), -z());
    }

    // ノルム値
    double norm() const
    {
        return std::sqrt(x() * x() + y() * y() + z() * z());
    }

    // 正規化
    Vec3 normalize() const
    {
        double norm = this->norm();
        return Vec3(
            x() / norm,
            y() / norm,
            z() / norm);
    }

    // 内積
    inline friend double dot(const Vec3 &v1, const Vec3 &v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }

    // 外積
    inline friend Vec3 cross(const Vec3 &v1, const Vec3 &v2)
    {
        return Vec3(
            v1.y() * v2.z() - v1.z() * v2.y(),
            v1.z() * v2.x() - v1.x() * v2.z(),
            v1.x() * v2.y() - v1.y() * v2.x());
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Vec3 &v)
    {
        stream << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
        return stream;
    }
};

#endif