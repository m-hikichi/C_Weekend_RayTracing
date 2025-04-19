#include <iostream>
#include "../header/camera.h"
#include "../header/ibl.h"
#include "../header/ray.h"

Color ray_color(const Ray &r, const ImageBasedLighting &ibl)
{
    return ibl.get_radiance(r);
}

int main()
{
    const int image_width = 640;
    const int image_height = 480;
    PinholeCamera camera(image_width, image_height);
    ImageBasedLighting ibl("Tokyo_BigSight_3k.hdr");

    for (int h = 0; h < image_height; h++)
    {
        for (int w = 0; w < image_width; w++)
        {
            Ray r = camera.get_ray(w, h);
            Color pixel_color = ray_color(r, ibl);
            camera.get_image().set_pixel(w, h, pixel_color);
        }
    }
    camera.get_image().gamma_correction();
    camera.get_image().save_png("../image/99_image_based_lighting.png");
}
