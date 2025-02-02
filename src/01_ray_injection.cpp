#include <iostream>
#include "../header/image.h"
#include "../header/ray.h"

Color ray_color(const Ray &r)
{
    auto t = 0.5 * (r.get_direction().y + 1.0);
    return (1.0 - t) * Color(1) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
    const int image_width = 640;
    const int image_height = 480;
    Image image(image_width, image_height);

    const double aspect_ratio = double(image_width) / double(image_height);
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;

    Vec3 origin = Vec3(0);
    Vec3 horizon = Vec3(viewport_width, 0, 0);
    Vec3 vertical = Vec3(0, viewport_height, 0);
    Vec3 left_lower_corner = origin - horizon / 2 - vertical / 2 - Vec3(0, 0, focal_length);

    for (int h = 0; h < image_height; h++)
    {
        for (int w = 0; w < image_width; w++)
        {
            double u = (double(w) + 0.5) / double(image_width);
            double v = 1.0 - (double(h) + 0.5) / double(image_height);
            Ray r(origin, left_lower_corner + u * horizon + v * vertical - origin);
            Color pixel_color = ray_color(r);
            image.set_pixel(w, h, pixel_color);
        }
    }
    image.save_png("../image/01_ray_injection.png");
}
