#ifndef HIT_H
#define HIT_H
#include "vec3.h"

class Sphere;

class Hit
{
private:
    const double distance;
    const Vec3 hit_position;
    const Vec3 hit_normal;
    const Sphere *hit_sphere;

public:
    static constexpr double MAX_DISTANCE{10000.0};
    static constexpr double MIN_DISTANCE{0.0};

    Hit(double distance, const Vec3 &position, const Vec3 &normal, const Sphere *sphere) : distance(distance), hit_position(position), hit_normal(normal.normalize()), hit_sphere(sphere) {}

    const double get_distance() const {
        return distance;
    }

    const Vec3 get_hit_position() const {
        return hit_position;
    }

    const Vec3 get_hit_normal() const {
        return hit_normal;
    }

    const Sphere* get_sphere() const {
        return hit_sphere;
    }
};

#endif