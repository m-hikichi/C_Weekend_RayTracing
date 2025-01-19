#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "util.h"

class Material
{
public:
    virtual Ray sample_ray(const Ray &injection_ray, const Hit &hit) const
    {
        return Ray(Vec3(), Vec3());
    }

    virtual Color get_brdf() const
    {
        return Color();
    }
};

class Lambertian : public Material
{
private:
    Color albedo;

public:
    Lambertian(const Color &_albedo) : albedo(_albedo) {}

    Ray sample_ray(const Ray &infection_ray, const Hit &hit) const
    {
        Vec3 random_vector_on_sphere = spherical_to_cartesian(generate_random_in_range(0.0, M_PI), generate_random_in_range(0.0, 2 * M_PI));
        if (dot(hit.get_hit_normal(), random_vector_on_sphere) > 0)
        {
            // random_vector_on_sphere が normal と同じ半球（反射ベクトル）である場合
            return Ray(hit.get_hit_position(), hit.get_hit_position() + random_vector_on_sphere);
        }
        else
        {
            // random_vector_on_sphere が normal と異なる半球（屈折ベクトル）である場合
            return Ray(hit.get_hit_position(), hit.get_hit_position() + (-random_vector_on_sphere));
        }
    }

    Color get_brdf() const
    {
        return albedo;
    }
};

class Mirror : public Material
{
private:
    Color albedo;

    Vec3 mirror_reflect(const Vec3 &injection, const Vec3 &normal) const
    {
        Vec3 reflect = injection - 2 * dot(injection, normal) * normal;
        return reflect.normalize();
    }

public:
    Mirror(const Color &_albedo) : albedo(_albedo) {}

    Ray sample_ray(const Ray &injection_ray, const Hit &hit) const
    {
        return Ray(hit.get_hit_position(), mirror_reflect(injection_ray.get_direction(), hit.get_hit_normal()));
    }

    Color get_brdf() const
    {
        return albedo;
    }
};

#endif