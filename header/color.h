#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color
{
public:
    double r, g, b;

    // コンストラクタ
    Color() : r(.0), g(.0), b(.0) {}
    Color(double _g) : r(_g), g(_g), b(_g) {}
    Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}

    // デストラクタ
    ~Color() {}

    // ベクトル同士の演算
    inline Color operator+(const Color &c) const
    {
        return Color(r + c.r, g + c.g, b + c.b);
    }

    inline Color operator+=(const Color &c)
    {
        r += c.r, g += c.g, b += c.b;
        return *this;
    }

    inline Color operator-(const Color &c) const
    {
        return Color(r - c.r, g - c.g, b - c.b);
    }

    inline Color operator-=(const Color &c)
    {
        r -= c.r, g -= c.g, b -= c.b;
        return *this;
    }

    inline Color operator*(const Color &c) const
    {
        return Color(r * c.r, g * c.g, b * c.b);
    }

    inline Color operator*=(const Color &c)
    {
        r *= c.r, g *= c.g, b *= c.b;
        return *this;
    }

    inline Color operator/(const Color &c) const
    {
        return Color(r / c.r, g / c.g, b / c.b);
    }

    inline Color operator/=(const Color &c)
    {
        r /= c.r, g /= c.g, b /= c.b;
        return *this;
    }

    // ベクトルとスカラーの演算
    inline Color operator+(const double s) const
    {
        return Color(r + s, g + s, b + s);
    }

    inline friend Color operator+(const double s, const Color &c)
    {
        return Color(s + c.r, s + c.g, s + c.b);
    }

    inline Color operator+=(const double s)
    {
        r += s, g += s, b += s;
        return *this;
    }

    inline Color operator-(const double s) const
    {
        return Color(r - s, g - s, b - s);
    }

    inline friend Color operator-(const double s, const Color &c)
    {
        return Color(s - c.r, s - c.g, s - c.b);
    }

    inline Color operator-=(const double s)
    {
        r -= s, g -= s, b -= s;
        return *this;
    }

    inline Color operator*(const double s) const
    {
        return Color(r * s, g * s, b * s);
    }

    inline friend Color operator*(const double s, const Color &c)
    {
        return Color(s * c.r, s * c.g, s * c.b);
    }

    inline Color operator*=(const double s)
    {
        r *= s, g *= s, b *= s;
        return *this;
    }

    inline Color operator/(const double s) const
    {
        return Color(r / s, g / s, b / s);
    }

    inline friend Color operator/(const double s, const Color &c)
    {
        return Color(s / c.r, s / c.g, s / c.b);
    }

    inline Color operator/=(const double s)
    {
        r /= s, g /= s, b /= s;
        return *this;
    }

    // イコール演算子
    inline bool operator==(const Color &c) const
    {
        if (r == c.r && g == c.g && b == c.b)
            return true;
        else
            return false;
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Color &c)
    {
        stream << "(" << c.r << ", " << c.g << ", " << c.b << ")";
        return stream;
    }
};

#endif