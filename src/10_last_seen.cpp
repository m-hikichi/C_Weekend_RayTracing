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
    const Vec3 look_from = Vec3(13, 2, 3);
    const Vec3 look_at = Vec3(0);
    const Ray view_direction = Ray(look_from, look_at - look_from);
    const double focus_distance = 10.0;
    const double vertical_fov = M_PI / 9;
    ThinLensCamera camera(image_width, image_height, view_direction, 0.2, focus_distance, vertical_fov);

    Aggregate world;
    std::shared_ptr<Material> ground_material = std::make_shared<Lambertian>(Color(0.5));
    world.add(std::make_shared<MaterializedSphere>(Vec3(0, -1000, 0), 1000, ground_material));

    std::shared_ptr<Material> material1 = std::make_shared<Glass>(1.5);
    world.add(std::make_shared<MaterializedSphere>(Vec3(0, 1, 0), 1.0, material1));

    std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<MaterializedSphere>(Vec3(-4, 1, 0), 1.0, material2));

    std::shared_ptr<Material> material3 = std::make_shared<Mirror>(Color(0.7, 0.6, 0.5));
    world.add(std::make_shared<MaterializedSphere>(Vec3(4, 1, 0), 1.0, material3));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            auto choose_mat = generate_random_in_range(.0, 1.0);
            Vec3 center(i + 0.9 * generate_random_in_range(.0, 1.0), 0.2, j + 0.9 * generate_random_in_range(.0, 1.0));

            if ((center - Vec3(4, 0.2, 0)).norm() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = Color(
                        generate_random_in_range(.0, 1.0),
                        generate_random_in_range(.0, 1.0),
                        generate_random_in_range(.0, 1.0));
                    std::shared_ptr<Material> sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<MaterializedSphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = Color(
                        generate_random_in_range(.5, 1.0),
                        generate_random_in_range(.5, 1.0),
                        generate_random_in_range(.5, 1.0));
                    std::shared_ptr<Material> sphere_material = std::make_shared<Mirror>(albedo);
                    world.add(std::make_shared<MaterializedSphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    std::shared_ptr<Material> sphere_material = std::make_shared<Glass>(1.5);
                    world.add(std::make_shared<MaterializedSphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

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
    camera.get_image().save_png("../image/10_last_seen.png");
}
