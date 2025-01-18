#ifndef HIT_H
#define HIT_H
#include "vec3.h"

class Sphere;

class Hit
{
private:
    double distance;
    Vec3 hit_position;
    Vec3 hit_normal; // 法線は必ず物体の"外側"を向く仕様とする
    const Sphere *hit_sphere;
    bool is_ray_outside_sphere;

public:
    static constexpr double MAX_DISTANCE{10000.0};
    static constexpr double MIN_DISTANCE{1e-6};

    Hit(double _distance, const Vec3 &_hit_position, const Vec3 &_hit_normal, const Sphere *_hit_sphere, const bool _is_ray_outside_sphere) : distance(_distance), hit_position(_hit_position), hit_normal(_hit_normal.normalize()), hit_sphere(_hit_sphere), is_ray_outside_sphere(_is_ray_outside_sphere) {}

    Hit operator=(const Hit &h)
    {
        distance = h.get_distance();
        hit_position = h.get_hit_position();
        hit_normal = h.get_hit_normal();
        hit_sphere = h.get_sphere();
        is_ray_outside_sphere = h.check_ray_outside_sphere();
        return *this;
    }

    const double get_distance() const
    {
        return distance;
    }

    const Vec3 get_hit_position() const
    {
        return hit_position;
    }

    const Vec3 get_hit_normal() const
    {
        return hit_normal;
    }

    const Sphere *get_sphere() const
    {
        return hit_sphere;
    }

    const bool check_ray_outside_sphere() const
    {
        return is_ray_outside_sphere;
    }
};

#endif