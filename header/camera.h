#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"
#include "image.h"
#include "util.h"

class Camera
{
protected:
    const Image image;
    const Ray view_direction;
    const double vertical_field_of_view; // 垂直方向の視野角（弧度法）
    Vec3 u, v, w; // カメラの向きを表す正規直交規定(u, v, w)
    Vec3 horizon;
    Vec3 vertical;
    Vec3 left_lower_corner;

public:
    Camera(
        const int _image_width,
        const int _image_height,
        const Ray _view_direction,
        const double _vertical_fov)
        : image(Image(_image_width, _image_height)),
          view_direction(_view_direction),
          vertical_field_of_view(_vertical_fov) {}

    Image get_image() const
    {
        return image;
    }

    void save_photo(const char *output_filepath) const
    {
        image.save_png(output_filepath);
    }

    virtual Ray get_ray(const int pixel_x, const int pixel_y) const = 0;
};

class PinholeCamera : public Camera
{
public:
    PinholeCamera(
        const int _image_width,
        const int _image_height,
        const Ray _view_direction = Ray(Vec3(0), Vec3(0, 0, -1)),
        const double _vertical_fov = M_PI / 2)
        : Camera(_image_width, _image_height, _view_direction, _vertical_fov)
    {
        const double aspect_ratio = double(_image_width) / double(_image_height);
        const double viewport_height = 2.0 * tan(vertical_field_of_view / 2);
        const double viewport_width = aspect_ratio * viewport_height;

        // カメラの向きを表す正規直交規定(u, v, w)の算出
        const Vec3 view_up = Vec3(0, 1, 0);
        w = -view_direction.get_direction();
        u = cross(view_up, w).normalize();
        v = cross(w, u).normalize();

        horizon = viewport_width * u;
        vertical = viewport_height * v;
        left_lower_corner = view_direction.get_origin() - horizon / 2 - vertical / 2 - w;
    }

    Ray get_ray(const int pixel_x, const int pixel_y) const override
    {
        // アンチエイリアシングを行うために、ピクセル内のランダムな地点を通るサンプルの生成
        double s = (double(pixel_x) + generate_random_in_range(.0, 1.0)) / double(image.get_width());
        double t = 1.0 - (double(pixel_y) + generate_random_in_range(.0, 1.0)) / double(image.get_height());
        return Ray(view_direction.get_origin(), left_lower_corner + s * horizon + t * vertical - view_direction.get_origin());
    }
};


class ThinLensCamera : public Camera
{
private:
    const double lens_radius; // レンズの絞り（値が小さいほどピントの合う範囲が広くなり、値が大きいほどピントの合う範囲が狭くなりボケが発生する）

public:
    ThinLensCamera(
        const int _image_width,
        const int _image_height,
        const Ray _view_direction,
        const double _aperture,
        const double _focus_distance,
        const double _vertical_fov = M_PI / 2)
        : Camera(_image_width, _image_height, _view_direction, _vertical_fov),
          lens_radius(_aperture / 2)
    {
        const double aspect_ratio = double(_image_width) / double(_image_height);
        const double viewport_height = 2.0 * tan(vertical_field_of_view / 2);
        const double viewport_width = aspect_ratio * viewport_height;

        // カメラの向きを表す正規直交規定(u, v, w)の定義
        const Vec3 view_up = Vec3(0, 1, 0);
        w = -view_direction.get_direction();
        u = cross(view_up, w).normalize();
        v = cross(w, u).normalize();

        horizon = _focus_distance * viewport_width * u;
        vertical = _focus_distance * viewport_height * v;
        left_lower_corner = view_direction.get_origin() - horizon / 2 - vertical / 2 - _focus_distance * w;
    }

    Ray get_ray(const int pixel_x, const int pixel_y) const override
    {
        // レンズから放たれるレイ
        double theta = generate_random_in_range(.0, 2 * M_PI);
        Vec3 lens_sample = generate_random_in_range(.0, lens_radius) * Vec3(cos(theta), sin(theta), 0);
        Vec3 offset = lens_sample.x * u + lens_sample.y * v;

        // アンチエイリアシングを行うために、ピクセル内のランダムな地点を通るサンプルの生成
        double s = (double(pixel_x) + generate_random_in_range(.0, 1.0)) / double(image.get_width());
        double t = 1.0 - (double(pixel_y) + generate_random_in_range(.0, 1.0)) / double(image.get_height());
        return Ray(
            view_direction.get_origin() + offset,
            left_lower_corner + s * horizon + t * vertical - view_direction.get_origin() - offset);
    }
};

#endif