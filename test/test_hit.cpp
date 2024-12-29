#include <gtest/gtest.h>
#include "../header/vec3.h"
#include "../header/sphere.h"
#include "../header/hit.h"

// コンストラクタのテスト
TEST(HitTest, ConstructorTest) {
    double distance = 10.0;
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 3.0, 0.0);
    Sphere sphere(Vec3(0), 1);
    bool is_ray_outside_sphere = true;

    Hit hit(distance, hit_position, hit_normal, &sphere, is_ray_outside_sphere);

    EXPECT_DOUBLE_EQ(hit.get_distance(), distance);
    EXPECT_EQ(hit.get_hit_position(), Vec3(1.0, 2.0, 3.0));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0.0, 1.0, 0.0));
    EXPECT_EQ(hit.get_sphere(), &sphere);
    EXPECT_TRUE(hit.check_ray_outside_sphere());
}

// MAX_DISTANCE と MIN_DISTANCE のテスト
TEST(HitTest, MaxMinDistanceTest) {
    EXPECT_DOUBLE_EQ(Hit::MAX_DISTANCE, 10000.0);
    EXPECT_DOUBLE_EQ(Hit::MIN_DISTANCE, 0.0);
}

// `operator=` のテスト
TEST(HitTest, AssignmentOperatorTest) {
    double distance = 15.0;
    Vec3 hit_position(1.0, 2.0, 3.0);
    Vec3 hit_normal(0.0, 3.0, 0.0);
    Sphere sphere(Vec3(0), 1);
    bool is_ray_outside_sphere = false;

    Hit h1(distance, hit_position, hit_normal, &sphere, is_ray_outside_sphere);
    Hit h2(0.0, Vec3(0), Vec3(0), nullptr, true);

    h2 = h1;
    EXPECT_DOUBLE_EQ(h2.get_distance(), distance);
    EXPECT_EQ(h2.get_hit_position(), Vec3(1.0, 2.0, 3.0));
    EXPECT_EQ(h2.get_hit_normal(), Vec3(0.0, 1.0, 0.0));
    EXPECT_EQ(h2.get_sphere(), &sphere);
    EXPECT_FALSE(h2.check_ray_outside_sphere());
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
