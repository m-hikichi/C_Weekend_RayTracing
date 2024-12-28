#ifndef HIT_H
#define HIT_H
#include "vec3.h"

class Sphere;

class Hit
{
private:
    const double distance;
    const Vec3 hit_position;
    const Vec3 hit_normal; // 法線は必ず物体の"外側"を向く仕様とする
    const Sphere *hit_sphere;
    const bool is_ray_outside_sphere;

public:
    static constexpr double MAX_DISTANCE{10000.0};
    static constexpr double MIN_DISTANCE{0.0};

    Hit(double _distance, const Vec3 &_hit_position, const Vec3 &_hit_normal, const Sphere *_hit_sphere, const bool _is_ray_outside_sphere) : distance(_distance), hit_position(_hit_position), hit_normal(_hit_normal.normalize()), hit_sphere(_hit_sphere), is_ray_outside_sphere(_is_ray_outside_sphere) {}

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