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
    Ray sample_ray(const Hit &hit) const
    {
        Vec3 random_vector_on_sphere = spherical_to_cartesian(generate_random_in_range(0.0, M_PI), generate_random_in_range(0.0, 2 * M_PI));
        if (dot(hit.get_hit_normal(), random_vector_on_sphere) > 0) {
            // random_vector_on_sphere が normal と同じ半球（反射ベクトル）である場合
            return Ray(hit.get_hit_position(), hit.get_hit_position() + random_vector_on_sphere);
        }
        else {
            // random_vector_on_sphere が normal と異なる半球（屈折ベクトル）である場合
            return Ray(hit.get_hit_position(), hit.get_hit_position() + (-random_vector_on_sphere));
        }
    }

    Color get_brdf() const
    {
        return Color(0.5);
    }
};

#endif