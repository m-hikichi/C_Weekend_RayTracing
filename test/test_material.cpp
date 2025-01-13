#include <gtest/gtest.h>
#include "../header/material.h"

// Lambertian クラスのテスト
TEST(LambertianTest, SampleRay)
{
    // アルベド（反射率）を設定
    Color albedo(0.8, 0.6, 0.2);
    Lambertian lambertian(albedo);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray injection_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 6));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, true);

    for (int i = 0; i < 100; i++)
    {
        // 反射ベクトルを計算する
        Ray reflect_ray = lambertian.sample_ray(injection_ray, hit);
        // 入力レイの始点が反射レイの始点と一致するか確認
        EXPECT_EQ(reflect_ray.get_origin(), hit_position);
        // 反射ベクトルの方向が期待通りか確認
        // 反射ベクトルは入力レイの方向に180度回転したもの
        EXPECT_LE(acos(reflect_ray.get_direction().y), M_PI / 2);
    }
}

TEST(LambertianTest, GetBRDFDirect)
{
    // アルベド（反射率）の設定
    Color albedo(0.8, 0.6, 0.2);

    // Lambertianオブジェクトを直接作成
    Lambertian lambertian(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = lambertian.get_brdf();
    EXPECT_EQ(brdf, albedo);
}

TEST(LambertianTest, GetBRDFPointer)
{
    // アルベド（反射率）の設定
    Color albedo(0.8, 0.6, 0.2);

    // Materialポインタを使ってLambertianオブジェクトを作成
    Material *lambertian = new Lambertian(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = lambertian->get_brdf();
    EXPECT_EQ(brdf, albedo);

    // メモリ解放
    delete lambertian;
}

// Metal クラスのテスト
TEST(MetalTest, SampleRay)
{
    // アルベド（反射率）を設定
    Color albedo(0.9, 0.7, 0.5);
    Metal metal(albedo);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray injection_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 6));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, true);

    // 反射ベクトルを計算する
    Ray reflect_ray = metal.sample_ray(injection_ray, hit);
    // 入力レイの始点が反射レイの始点と一致するか確認
    EXPECT_EQ(reflect_ray.get_origin(), hit_position);
    // 反射ベクトルの方向が期待通りか確認
    // 反射ベクトルは入力レイの方向に180度回転したもの
    EXPECT_NEAR(reflect_ray.get_direction().x, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).x, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().y, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).y, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().z, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).z, 1e-6);
}

TEST(MetalTest, GetBRDFDirect)
{
    // アルベド（反射率）の設定
    Color albedo(0.9, 0.7, 0.5);

    // Metalオブジェクトを直接作成
    Metal metal(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = metal.get_brdf();
    EXPECT_EQ(brdf, albedo);
}

TEST(MetalTest, GetBRDFPointer)
{
    // アルベド（反射率）の設定
    Color albedo(0.9, 0.7, 0.5);

    // Materialポインタを使ってMetalオブジェクトを作成
    Material *metal = new Metal(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = metal->get_brdf();
    EXPECT_EQ(brdf, albedo);

    // メモリ解放
    delete metal;
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}