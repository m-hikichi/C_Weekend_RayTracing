#include <iostream>
#include <optional>
#include "../header/image.h"
#include "../header/ray.h"
#include "../header/sphere.h"
#include "../header/hit.h"
#include "../header/aggregate.h"
#include "../header/util.h"

Color ray_color(const Ray &r, const Aggregate& world)
{
    std::optional<Hit> result = world.intersect(r);
    if (result)
    {
        Hit hit = *result;
        return 0.5 * Color(hit.get_hit_normal().x + 1, hit.get_hit_normal().y + 1, hit.get_hit_normal().z + 1);
    }
    auto t = 0.5 * (r.get_direction().y + 1.0);
    return (1.0 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    const int image_width = 640;
    const int image_height = 480;
    Image i(image_width, image_height);

    const double aspect_ratio = double(image_width) / double(image_height);
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;
    const int samples_per_pixel = 100;

    Vec3 origin = Vec3(0);
    Vec3 horizon = Vec3(viewport_width, 0, 0);
    Vec3 vertical = Vec3(0, viewport_height, 0);
    Vec3 left_lower_corner = origin - horizon / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    Aggregate world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    for (int h = 0; h < image_height; h++)
    {
        for (int w = 0; w < image_width; w++)
        {
            Color pixel_color(0);
            for (int s = 0; s < samples_per_pixel; s++) {
                double u = (double(w) + generate_random_in_range(0.0, 1.0)) / double(image_width);
                double v = 1.0 - (double(h) + generate_random_in_range(0.0, 1.0)) / double(image_height);
                Ray r(origin, left_lower_corner + u * horizon + v * vertical - origin);
                pixel_color += ray_color(r, world);
            }
            i.set_pixel(w, h, pixel_color / samples_per_pixel);
        }
    }
    i.save_png("../image/anti_aliasing.png");
}
