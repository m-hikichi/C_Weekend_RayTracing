#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

class Color : public VecBase
{
public:
    // コンストラクタは親クラスのものをそのまま利用
    using VecBase::VecBase;

    // r, g, b メソッド
    double r() const { return v[0]; }
    double g() const { return v[1]; }
    double b() const { return v[2]; }

    // 代入演算
    inline Color &operator=(const VecBase &vb)
    {
        v[0] = vb.getV()[0];
        v[1] = vb.getV()[1];
        v[2] = vb.getV()[2];
        return *this;
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Color &c)
    {
        stream << "(" << c.r() << ", " << c.g() << ", " << c.b() << ")";
        return stream;
    }
};

#endif