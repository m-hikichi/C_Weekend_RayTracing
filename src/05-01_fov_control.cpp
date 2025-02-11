#include <iostream>
#include <optional>
#include "../header/aggregate.h"
#include "../header/camera.h"
#include "../header/ray.h"
#include "../header/sphere.h"
#include "../header/util.h"

Color ray_color(const Ray &r, const Aggregate &world, int interaction_count = 0)
{
    const int max_interaction_count = 10;
    if (interaction_count > max_interaction_count)
        return Color();

    std::optional<Hit> result = world.intersect(r);
    if (result)
    {
        Hit hit = *result;
        const Sphere *sphere = hit.get_sphere();
        Ray ray = sphere->get_material()->sample_ray(r, hit);
        return sphere->get_material()->get_brdf() * ray_color(ray, world, interaction_count + 1);
    }
    auto t = 0.5 * (r.get_direction().y + 1.0);
    return (1.0 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    const int image_width = 640;
    const int image_height = 480;
    const double vertical_fov = M_PI / 2;
    PinholeCamera camera(image_width, image_height, Ray(Vec3(), Vec3(0, 0, -1)), vertical_fov);

    Aggregate world;
    double radius = cos(M_PI / 4);
    world.add(std::make_shared<MaterializedSphere>(Vec3(-radius, 0, -1), radius, std::make_shared<Lambertian>(Color(0, 0, 1))));
    world.add(std::make_shared<MaterializedSphere>(Vec3(radius, 0, -1), radius, std::make_shared<Lambertian>(Color(1, 0, 0))));

    const int samples_per_pixel = 100;

    for (int h = 0; h < image_height; h++)
    {
        for (int w = 0; w < image_width; w++)
        {
            Color pixel_color(0);
            for (int s = 0; s < samples_per_pixel; s++)
            {
                Ray r = camera.get_ray(w, h);
                pixel_color += ray_color(r, world);
            }
            camera.get_image().set_pixel(w, h, pixel_color / samples_per_pixel);
        }
    }
    camera.get_image().save_png("../image/05-01_fov_control.png");
}
