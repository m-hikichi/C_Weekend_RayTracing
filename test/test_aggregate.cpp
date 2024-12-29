#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "../header/ray.h"
#include "../header/sphere.h"
#include "../header/hit.h"
#include "../header/aggregate.h"

TEST(AggregateTest, InitialState)
{
    Aggregate aggregate;
    EXPECT_TRUE(aggregate.get_spheres().empty());
}

TEST(AggregateTest, Add)
{
    Aggregate aggregate;
    auto s1 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 1);
    aggregate.add(s1);
    EXPECT_EQ(aggregate.get_spheres().size(), 1);

    auto s2 = std::make_shared<Sphere>(Vec3(1.0, 2.0, 3.0), 2);
    aggregate.add(s2);
    EXPECT_EQ(aggregate.get_spheres().size(), 2);
}

TEST(AggregateTest, Clear)
{
    Aggregate aggregate;
    auto s1 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 1);
    auto s2 = std::make_shared<Sphere>(Vec3(1.0, 2.0, 3.0), 2);
    aggregate.add(s1);
    aggregate.add(s2);
    EXPECT_EQ(aggregate.get_spheres().size(), 2);

    aggregate.clear();
    EXPECT_EQ(aggregate.get_spheres().size(), 0);
}

TEST(AggregateTest, IntersectRay)
{
    Vec3 ray_origin(0, 0, -5);
    Vec3 ray_direction(0, 0, 1);
    Ray ray(ray_origin, ray_direction);

    Aggregate aggregate;
    auto s1 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 2);
    auto s2 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 6.0), 3);
    aggregate.add(s1);
    aggregate.add(s2);

    std::optional<Hit> result = aggregate.intersect(ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";
    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 3);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, 0, -2));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0, 0, -1));
    ASSERT_TRUE(hit.check_ray_outside_sphere());
}

TEST(AggregateTest, IntersectRayOnlyHitsOneSphere)
{
    Vec3 ray_origin(0, -5, 0);
    Vec3 ray_direction(0, 1, 0);
    Ray ray(ray_origin, ray_direction);

    Aggregate aggregate;
    auto s1 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 2);
    auto s2 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 6.0), 3);
    aggregate.add(s1);
    aggregate.add(s2);

    std::optional<Hit> result = aggregate.intersect(ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";
    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 3);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, -2, 0));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0, -1, 0));
    ASSERT_TRUE(hit.check_ray_outside_sphere());
}

TEST(AggregateTest, RayMissesSpheres)
{
    Vec3 ray_origin(0, 0, -5);
    Vec3 ray_direction(0, 1, 0);
    Ray ray(ray_origin, ray_direction);

    Aggregate aggregate;
    auto s1 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 2);
    auto s2 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 6.0), 3);
    aggregate.add(s1);
    aggregate.add(s2);

    std::optional<Hit> result = aggregate.intersect(ray);
    ASSERT_FALSE(result.has_value()) << "Intersection test failed: Expected nullopt, but got a valid Hit.";
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}