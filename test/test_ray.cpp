#include <gtest/gtest.h>
#include "../header/ray.h"

// Rayクラスのテスト
TEST(RayTest, ConstructorAndGetter) {
    Vec3 origin(1.0, 2.0, 3.0);
    Vec3 direction(4.0, 5.0, 6.0);

    // Rayのインスタンス作成
    Ray ray(origin, direction);

    // originとdirectionのゲッターが正しいか
    EXPECT_EQ(ray.get_origin(), origin) << "Ray origin is not correctly initialized.";
    EXPECT_EQ(ray.get_direction().x, 4.0 / sqrt(77.0)) << "Ray direction x-component is incorrect.";
    EXPECT_EQ(ray.get_direction().y, 5.0 / sqrt(77.0)) << "Ray direction y-component is incorrect.";
    EXPECT_EQ(ray.get_direction().z, 6.0 / sqrt(77.0)) << "Ray direction z-component is incorrect.";
}

TEST(RayTest, RayEvaluation) {
    Vec3 origin(1.0, 2.0, 3.0);
    Vec3 direction(3.0, 4.0, 0.0);
    Ray ray(origin, direction);
    Vec3 result;

    // r = o + t * d をテスト
    // t = 0 の場合（レイの始点）
    result = ray(0.0);
    EXPECT_EQ(result.x, 1.0);
    EXPECT_EQ(result.y, 2.0);
    EXPECT_EQ(result.z, 3.0);

    // t = 2 の場合
    result = ray(2.0);
    EXPECT_NEAR(result.x, 2.2, 1e-6);
    EXPECT_NEAR(result.y, 3.6, 1e-6);
    EXPECT_NEAR(result.z, 3.0, 1e-6);

    // t = -2 の場合
    result = ray(-2.0);
    EXPECT_NEAR(result.x, -0.2, 1e-6);
    EXPECT_NEAR(result.y, 0.4, 1e-6);
    EXPECT_NEAR(result.z, 3.0, 1e-6);
}
