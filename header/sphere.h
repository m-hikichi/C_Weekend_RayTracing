#ifndef SPHERE_H
#define SPHERE_H
#include <cmath>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hit.h"

class Sphere
{
private:
    const Vec3 center;
    const double radius;

    bool is_ray_outside_sphere(const Ray &ray, const Vec3 &normal) const
    {
        if (dot(ray.get_direction(), normal.normalize()) > 0)
        {
            // 内積が正の場合、レイと法線が同じ方向を向いているならレイは物体の内部にあり、falseを返す
            return false;
        }
        else
        {
            // 内積が負の場合、レイと法線が逆方向を向いているならレイはオブジェクトの外側にあり、trueを返す
            return true;
        }
    }

public:
    // コンストラクタ
    Sphere(const Vec3 &_center, const double _radius) : center(_center), radius(_radius)
    {
        if (_radius <= 0)
        {
            throw radius_exception();
        }
    }

    // コンソール出力
    inline friend std::ostream &operator<<(std::ostream &stream, const Sphere &s)
    {
        stream << "center : " << s.center << "\nradius : " << s.radius;
        return stream;
    }

    // ゲッター
    Vec3 get_center() const
    {
        return center;
    }

    double get_radius() const
    {
        return radius;
    }

    // 与えられたレイとの衝突判定
    std::optional<Hit> intersect(const Ray &ray) const
    {
        double a = 1.0;
        double b = dot(ray.get_direction(), ray.get_origin() - center);
        double c = pow((ray.get_origin() - center).norm(), 2) - pow(radius, 2);

        double D = b * b - a * c;
        double distance;

        // D < 0 の場合，交差していない
        if (D < 0)
            return std::nullopt;

        // D = 0 の場合，接する
        else if (D == 0)
        {
            distance = -b;
        }

        // D > 0 の場合，2点で交差する
        else
        {
            double d1 = -b - std::sqrt(D);
            double d2 = -b + std::sqrt(D);

            // レイの飛ばした逆方向で交差している場合
            if (d1 < 0 && d2 < 0)
                return std::nullopt;

            // 交差地点が非常に遠い場合
            if (d1 > Hit::MAX_DISTANCE && d2 > Hit::MAX_DISTANCE)
                return std::nullopt;

            if (Hit::MIN_DISTANCE < d1 && d1 < Hit::MAX_DISTANCE)
            {
                distance = d1;
            }
            else if (Hit::MIN_DISTANCE < d2 && d2 < Hit::MAX_DISTANCE)
            {
                distance = d2;
            }
        }

        Vec3 surface_normal = ray(distance) - center;
        return Hit(distance, ray(distance), surface_normal, this, is_ray_outside_sphere(ray, surface_normal));
    }

    class radius_exception
    {
    private:
        const char *msg = "\x1b[31mError : The radius of the sphere is set less than or equal to 0.\x1b[39m";

    public:
        radius_exception() {}
        const char *get_msg() const { return msg; }
    };
};

#endif