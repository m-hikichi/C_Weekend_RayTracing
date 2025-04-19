#ifndef IBL_H
#define IBL_H

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "color.h"
#include "image.h"
#include "ray.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class ImageBasedLighting
{
private:
    Image hdr_image;

public:
    ImageBasedLighting(const char *_filename) : hdr_image(Image(_filename)) {}

    Color get_radiance(const Ray &r) const
    {
        // 与えられたベクトルを球面座標系に変換
        double theta = acos(r.get_direction().y);
        double phi = atan2(r.get_direction().z, r.get_direction().x);
        while (phi < 0)
            phi += 2 * M_PI;

        int u = phi / (2 * M_PI) * hdr_image.get_width();
        int v = theta / M_PI * hdr_image.get_height();

        return hdr_image.get_pixel(u, v);
    }
};

#endif