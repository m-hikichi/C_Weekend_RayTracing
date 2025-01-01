#include <iostream>
#include <optional>
#include "../header/ray.h"
#include "../header/sphere.h"
#include "../header/aggregate.h"
#include "../header/camera.h"
#include "../header/util.h"

Color ray_color(const Ray &r, const Aggregate &world, int max_reflection_depth)
{
    if (max_reflection_depth > 10)
        return Color(0);

    std::optional<Hit> result = world.intersect(r);
    if (result)
    {
        Hit hit = *result;
        Vec3 reflect_ray = (hit.get_hit_position() + hit.get_hit_normal() + spherical_to_cartesian(generate_random_in_range(0.0, M_PI), generate_random_in_range(0.0, 2 * M_PI))) - hit.get_hit_position();
        return 0.5 * ray_color(Ray(hit.get_hit_position(), reflect_ray), world, max_reflection_depth + 1);
    }
    auto t = 0.5 * (r.get_direction().y + 1.0);
    return (1.0 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    const int image_width = 640;
    const int image_height = 480;
    Camera camera(image_width, image_height);

    Aggregate world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    const int samples_per_pixel = 100;

    for (int h = 0; h < image_height; h++)
    {
        for (int w = 0; w < image_width; w++)
        {
            Color pixel_color(0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                Ray r = camera.get_ray(w, h);
                pixel_color += ray_color(r, world, 0);
            }
            camera.get_image().set_pixel(w, h, pixel_color / samples_per_pixel);
        }
    }
    camera.get_image().gamma_correction();
    camera.get_image().save_png("../image/material_rendering.png");
}
