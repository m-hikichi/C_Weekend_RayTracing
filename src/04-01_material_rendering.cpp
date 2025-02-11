#include <iostream>
#include <optional>
#include "../header/aggregate.h"
#include "../header/camera.h"
#include "../header/material.h"
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
    PinholeCamera camera(image_width, image_height);

    Aggregate world;
    world.add(std::make_shared<MaterializedSphere>(Vec3(0, 0, -1), 0.5, std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3))));
    world.add(std::make_shared<MaterializedSphere>(Vec3(1, 0, -1), 0.5, std::make_shared<Mirror>(Color(0.8, 0.6, 0.2))));
    world.add(std::make_shared<MaterializedSphere>(Vec3(-1, 0, -1), 0.5, std::make_shared<Mirror>(Color(0.8))));
    world.add(std::make_shared<MaterializedSphere>(Vec3(0, -100.5, -1), 100, std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))));

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
    camera.get_image().gamma_correction();
    camera.get_image().save_png("../image/04-01_material_rendering.png");
}
