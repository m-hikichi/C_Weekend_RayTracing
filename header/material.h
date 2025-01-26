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
    virtual Ray sample_ray(const Ray &incident_ray, const Hit &hit) const
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

    Ray sample_ray(const Ray &incident_ray, const Hit &hit) const
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

    Vec3 mirror_reflect(const Vec3 &incident, const Vec3 &normal) const
    {
        Vec3 reflect = incident - 2 * dot(incident, normal) * normal;
        return reflect.normalize();
    }

public:
    Mirror(const Color &_albedo) : albedo(_albedo) {}

    Ray sample_ray(const Ray &incident_ray, const Hit &hit) const
    {
        return Ray(hit.get_hit_position(), mirror_reflect(incident_ray.get_direction(), hit.get_hit_normal()));
    }

    Color get_brdf() const
    {
        return albedo;
    }
};

class Glass : public Material
{
private:
    double refractive_index;

    Vec3 refract(const Vec3 &incident, const Vec3 &normal, const double eta_incident, const double eta_transmitted) const
    {
        double cos_theta = dot(-incident, normal);
        Vec3 refract_parallel = (eta_incident / eta_transmitted) * (incident + cos_theta * normal);
        Vec3 refract_perpendicular = -sqrt(1.0 - refract_parallel.norm() * refract_parallel.norm()) * normal;
        return refract_parallel + refract_perpendicular;
    }

    Vec3 mirror_reflect(const Vec3 &incident, const Vec3 &normal) const
    {
        Vec3 reflect = incident - 2 * dot(incident, normal) * normal;
        return reflect.normalize();
    }

public:
    Glass(const double _refractive_index) : refractive_index(_refractive_index) {}

    Ray sample_ray(const Ray &incident_ray, const Hit &hit) const
    {
        double cos_theta = dot(-incident_ray.get_direction(), hit.get_hit_normal());
        double sin_theta = sqrt(1 - cos_theta * cos_theta);
        if (hit.check_ray_outside_sphere())
        {
            if ((1.0 / refractive_index) * sin_theta > 1.0)
                // 全反射
                return Ray(hit.get_hit_position(), mirror_reflect(incident_ray.get_direction(), hit.get_hit_normal()));
            else
                return Ray(hit.get_hit_position(), refract(incident_ray.get_direction(), hit.get_hit_normal(), 1.0, refractive_index));
        }
        else
        {
            if ((refractive_index / 1.0) * sin_theta > 1.0)
                // 全反射
                return Ray(hit.get_hit_position(), mirror_reflect(incident_ray.get_direction(), hit.get_hit_normal()));
            else
                // 法線が必ず物体の"外側"を向く仕様であるため，法線の向きを逆転
                return Ray(hit.get_hit_position(), refract(incident_ray.get_direction(), -hit.get_hit_normal(), refractive_index, 1.0));
        }
    }

    Color get_brdf() const
    {
        return Color(1.0);
    }
};

#endif