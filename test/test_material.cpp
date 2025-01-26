#include <gtest/gtest.h>
#include "../header/material.h"

/**
 * Lambertian クラス
 */
TEST(LambertianTest, SampleRay)
{
    // アルベド（反射率）を設定
    Color albedo(0.8, 0.6, 0.2);
    Lambertian lambertian(albedo);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray incident_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 6));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, true);

    for (int i = 0; i < 100; i++)
    {
        // 反射ベクトルを計算する
        Ray reflect_ray = lambertian.sample_ray(incident_ray, hit);
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

/**
 * Mirror クラス
 */
TEST(MirrorTest, SampleRay)
{
    // アルベド（反射率）を設定
    Color albedo(0.9, 0.7, 0.5);
    Mirror mirror(albedo);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray incident_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 6));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, true);

    // 反射ベクトルを計算する
    Ray reflect_ray = mirror.sample_ray(incident_ray, hit);
    // 入力レイの始点が反射レイの始点と一致するか確認
    EXPECT_EQ(reflect_ray.get_origin(), hit_position);
    // 反射ベクトルの方向が期待通りか確認
    // 反射ベクトルは入力レイの方向に180度回転したもの
    EXPECT_NEAR(reflect_ray.get_direction().x, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).x, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().y, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).y, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().z, spherical_to_cartesian(M_PI / 3, M_PI / 6 + M_PI).z, 1e-6);
}

TEST(MirrorTest, GetBRDFDirect)
{
    // アルベド（反射率）の設定
    Color albedo(0.9, 0.7, 0.5);

    // Mirrorオブジェクトを直接作成
    Mirror mirror(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = mirror.get_brdf();
    EXPECT_EQ(brdf, albedo);
}

TEST(MirrorTest, GetBRDFPointer)
{
    // アルベド（反射率）の設定
    Color albedo(0.9, 0.7, 0.5);

    // Materialポインタを使ってMirrorオブジェクトを作成
    Material *mirror = new Mirror(albedo);

    // get_brdf がアルベドを返すか確認
    Color brdf = mirror->get_brdf();
    EXPECT_EQ(brdf, albedo);

    // メモリ解放
    delete mirror;
}

/**
 * Glass クラス
 */
TEST(GlassTest, SampleRayFromOutside)
{
    // アルベド（反射率）を設定
    double refractive_index = 1.5;
    Glass glass(refractive_index);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray incident_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 2));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, true);

    // 透過ベクトルを計算する
    Ray reflect_ray = glass.sample_ray(incident_ray, hit);
    // 入力レイの始点が透過レイの始点と一致するか確認
    EXPECT_EQ(reflect_ray.get_origin(), hit_position);
    // 透過ベクトルの方向が期待通りか確認
    double eta_theta = asin(sin(M_PI / 3) * (1.0 / refractive_index));
    EXPECT_NEAR(reflect_ray.get_direction().x, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).x, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().y, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).y, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().z, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).z, 1e-6);
}

TEST(GlassTest, SampleRayFromInside)
{
    // アルベド（反射率）を設定
    double refractive_index = 1.5;
    Glass glass(refractive_index);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, -1.0, 0.0); // 下向きの法線

    // 入力レイの設定
    Ray incident_ray(hit_position, -spherical_to_cartesian(M_PI / 6, M_PI / 2));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, false);

    // 透過ベクトルを計算する
    Ray reflect_ray = glass.sample_ray(incident_ray, hit);
    // 入力レイの始点が透過レイの始点と一致するか確認
    EXPECT_EQ(reflect_ray.get_origin(), hit_position);
    // 透過ベクトルの方向が期待通りか確認
    double eta_theta = asin(sin(M_PI / 6) * (refractive_index / 1.0));
    EXPECT_NEAR(reflect_ray.get_direction().x, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).x, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().y, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).y, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().z, spherical_to_cartesian(eta_theta + M_PI, M_PI / 2).z, 1e-6);
}

TEST(GlassTest, SampleRayTotalReflection)
{
    // アルベド（反射率）を設定
    double refractive_index = 1.5;
    Glass glass(refractive_index);

    // ヒット位置と法線の設定
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 1.0, 0.0); // 上向きの法線

    // 入力レイの設定
    Ray incident_ray(hit_position, -spherical_to_cartesian(M_PI / 3, M_PI / 2));
    // ヒット情報の設定
    Hit hit(10, hit_position, hit_normal, nullptr, false);

    // 反射ベクトルを計算する
    Ray reflect_ray = glass.sample_ray(incident_ray, hit);
    // 入力レイの始点が反射レイの始点と一致するか確認
    EXPECT_EQ(reflect_ray.get_origin(), hit_position);
    // 反射ベクトルの方向が期待通りか確認
    // 反射ベクトルは入力レイの方向に180度回転したもの
    EXPECT_NEAR(reflect_ray.get_direction().x, spherical_to_cartesian(M_PI / 3, M_PI / 2 + M_PI).x, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().y, spherical_to_cartesian(M_PI / 3, M_PI / 2 + M_PI).y, 1e-6);
    EXPECT_NEAR(reflect_ray.get_direction().z, spherical_to_cartesian(M_PI / 3, M_PI / 2 + M_PI).z, 1e-6);
}

TEST(GlassTest, GetBRDFDirect)
{
    // Glassオブジェクトを直接作成
    double refractive_index = 1.5;
    Glass glass(refractive_index);

    // get_brdf がアルベドを返すか確認
    Color brdf = glass.get_brdf();
    EXPECT_EQ(brdf, Color(1.0));
}

TEST(GlassTest, GetBRDFPointer)
{
    // Materialポインタを使ってGlassオブジェクトを作成
    double refractive_index = 1.5;
    Material *glass = new Glass(refractive_index);

    // get_brdf がアルベドを返すか確認
    Color brdf = glass->get_brdf();
    EXPECT_EQ(brdf, Color(1.0));

    // メモリ解放
    delete glass;
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}