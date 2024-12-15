#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <climits>
#include "util.h"
#include "color.h"
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

class Image
{
private:
    int width;
    int height;
    int channels{3};
    Color **data;

public:
    // コンストラクタ
    Image() {}
    Image(int _width, int _height) : width(_width), height(_height)
    {
        data = new Color *[width];
        for (int x = 0; x < width; x++)
        {
            data[x] = new Color[height];
        }
    }

    // デストラクタ
    ~Image() {}

    // セッタ―
    void set_pixel(int x, int y, const Color &c)
    {
        data[x][y] = c;
    }

    void set_pixel(int x, int y, const double g)
    {
        data[x][y] = Color(g);
    }

    // ゲッター
    int get_width() { return width; }
    int get_height() { return height; }

    // ガンマ補正
    void gamma_correction()
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                Color c = data[x][y];
                data[x][y] = Color(
                    std::pow(c.r(), 1 / 2.2),
                    std::pow(c.g(), 1 / 2.2),
                    std::pow(c.b(), 1 / 2.2));
            }
        }
    }

    // 画像保存
    void save_png(const char *output_filepath) const
    {
        unsigned char pixels[width * height * channels];
        // [0~1] を [0~255] に変換
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                Color c = data[x][y];
                auto r = clamp(c.r(), 0.0, 1.0);
                auto g = clamp(c.g(), 0.0, 1.0);
                auto b = clamp(c.b(), 0.0, 1.0);

                unsigned char ir = static_cast<unsigned char>(UCHAR_MAX * r);
                unsigned char ig = static_cast<unsigned char>(UCHAR_MAX * g);
                unsigned char ib = static_cast<unsigned char>(UCHAR_MAX * b);

                pixels[y * (width * channels) + x * (channels) + 0] = ir;
                pixels[y * (width * channels) + x * (channels) + 1] = ig;
                pixels[y * (width * channels) + x * (channels) + 2] = ib;
            }
        }
        stbi_write_png(output_filepath, width, height, channels, pixels, width * channels);
    }
};

#endif