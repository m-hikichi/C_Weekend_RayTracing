#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "vec3.h"

class Ray
{
private:
    // レイの始点座標
    const Vec3 origin;
    // レイの方向
    const Vec3 direction;

public:
    // コンストラクタ
    // レイの方向ベクトルは，正規化（単位ベクトル）して格納
    Ray(const Vec3 &_origin, const Vec3 &_direction)
        : origin(_origin), direction(_direction.normalize()) {}

    // ゲッター
    Vec3 get_origin() const
    {
        return origin;
    }

    Vec3 get_direction() const
    {
        return direction;
    }

    // r = o + t * d
    Vec3 operator()(double t) const
    {
        return origin + t * direction;
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Ray &r)
    {
        stream << "origin    : " << r.origin << "\ndirection : " << r.direction;
        return stream;
    }
};

#endif