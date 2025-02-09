#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"
#include "image.h"
#include "util.h"

class Camera
{
private:
    const double vertical_field_of_view; // 垂直方向の視野角（弧度法）
    const Image image;
    Vec3 origin;
    Vec3 horizon;
    Vec3 vertical;
    Vec3 left_lower_corner;

public:
    Camera(int _image_width, int _image_height, const double _vertical_fov = M_PI / 2)
        : image(Image(_image_width, _image_height)), vertical_field_of_view(_vertical_fov)
    {
        const double aspect_ratio = double(_image_width) / double(_image_height);
        const double viewport_height = 2.0 * tan(vertical_field_of_view / 2);
        const double viewport_width = aspect_ratio * viewport_height;
        const double focal_length = 1.0;

        origin = Vec3(0);
        horizon = Vec3(viewport_width, 0, 0);
        vertical = Vec3(0, viewport_height, 0);
        left_lower_corner = origin - horizon / 2 - vertical / 2 - Vec3(0, 0, focal_length);
    }

    Image get_image() const
    {
        return image;
    }

    void save_photo(const char *output_filepath) const
    {
        image.save_png(output_filepath);
    }

    Ray get_ray(const int pixel_x, const int pixel_y) const
    {
        // アンチエイリアシングを行うために、ピクセル内のランダムな地点を通るサンプルの生成
        double u = (double(pixel_x) + generate_random_in_range(0.0, 1.0)) / double(image.get_width());
        double v = 1.0 - (double(pixel_y) + generate_random_in_range(0.0, 1.0)) / double(image.get_height());
        return Ray(origin, left_lower_corner + u * horizon + v * vertical - origin);
    }
};

#endif