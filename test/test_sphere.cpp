#include <gtest/gtest.h>
#include "../header/vec3.h"
#include "../header/ray.h"
#include "../header/sphere.h"
#include "../header/hit.h"

/**
 * Sphere クラスのテスト
 */
// コンストラクタの動作確認
TEST(SphereTest, Constructor)
{
    Sphere sphere(Vec3(0), 1.0);
    EXPECT_EQ(sphere.get_center(), Vec3(0));
    EXPECT_DOUBLE_EQ(sphere.get_radius(), 1.0);
}

// 無効な半径で例外スローを確認
TEST(SphereTest, InvalidRadiusThrowsException)
{
    EXPECT_THROW(Sphere invalid_sphere(Vec3(0), 0.0), Sphere::radius_exception);
    EXPECT_THROW(Sphere invalid_sphere(Vec3(0), -1.0), Sphere::radius_exception);
}

// RayとSphereの交差テスト
TEST(SphereTest, IntersectRay)
{
    Vec3 ray_origin(0, 0, -5);
    Vec3 ray_direction(0, 0, 1);
    Ray ray(ray_origin, ray_direction);
    Sphere sphere(Vec3(0), 2);

    std::optional<Hit> result = sphere.intersect(ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";

    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 3);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, 0, -2));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0, 0, -1));
    ASSERT_TRUE(hit.check_ray_outside_sphere());
}

// Sphere内部から始まるレイ
TEST(SphereTest, RayInsideSphere)
{
    Vec3 ray_origin(0, 0, 0.5);
    Vec3 ray_direction(0, 0, 1);
    Ray inside_ray(ray_origin, ray_direction);
    Sphere sphere(Vec3(0), 1.0);

    std::optional<Hit> result = sphere.intersect(inside_ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";

    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 0.5);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, 0, 1));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0, 0, 1));
    ASSERT_FALSE(hit.check_ray_outside_sphere());
}

// RayがSphereを交差しない場合
TEST(SphereTest, RayMissesSphere)
{
    Vec3 ray_origin(0, 0, -3);
    Vec3 ray_direction(0, 1, 0);
    Ray miss_ray(ray_origin, ray_direction);
    Sphere sphere(Vec3(0), 1.0);

    std::optional<Hit> result = sphere.intersect(miss_ray);
    ASSERT_FALSE(result.has_value()) << "Intersection test failed: Expected nullopt, but got a valid Hit.";
}

// レイがスフィアに接する場合
TEST(SphereTest, RayTangentToSphere)
{
    Vec3 ray_origin(0, 0, -4);
    Vec3 ray_direction(0, 0, 1);
    Ray tangent_ray(ray_origin, ray_direction);
    Sphere sphere(Vec3(1, 0, 0), 1.0);

    std::optional<Hit> result = sphere.intersect(tangent_ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";

    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 4.0);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, 0, 0));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(-1, 0, 0));
}

/**
 * MaterializedSphere クラスのテスト
 */
// コンストラクタの動作確認
TEST(MaterializedSphereTest, LambertianConstructor)
{
    Color albedo(0.8, 0.6, 0.2);
    std::shared_ptr<Material> lambertian = std::make_shared<Lambertian>(albedo);

    MaterializedSphere materialized_sphere(Vec3(0), 1.0, lambertian);
    Material *material = materialized_sphere.get_material();

    EXPECT_EQ(materialized_sphere.get_center(), Vec3(0));
    EXPECT_DOUBLE_EQ(materialized_sphere.get_radius(), 1.0);
    EXPECT_EQ(material->get_brdf(), albedo);
}

TEST(MaterializedSphereTest, MirrorConstructor)
{
    Color albedo(0.9, 0.7, 0.5);
    std::shared_ptr<Material> mirror = std::make_shared<Mirror>(albedo);

    MaterializedSphere materialized_sphere(Vec3(0), 1.0, mirror);
    Material *material = materialized_sphere.get_material();

    EXPECT_EQ(materialized_sphere.get_center(), Vec3(0));
    EXPECT_DOUBLE_EQ(materialized_sphere.get_radius(), 1.0);
    EXPECT_EQ(material->get_brdf(), albedo);
}

// 無効な半径で例外スローを確認
TEST(MaterializedSphereTest, InvalidRadiusThrowsException)
{
    Color albedo(0.8, 0.6, 0.2);
    std::shared_ptr<Material> lambertian = std::make_shared<Lambertian>(albedo);

    EXPECT_THROW(MaterializedSphere invalid_sphere(Vec3(0), 0.0, lambertian), Sphere::radius_exception);
    EXPECT_THROW(MaterializedSphere invalid_sphere(Vec3(0), -1.0, lambertian), Sphere::radius_exception);
}

// RayとSphereの交差テスト
TEST(MaterializedSphereTest, IntersectRay)
{
    Vec3 ray_origin(0, 0, -5);
    Vec3 ray_direction(0, 0, 1);
    Ray ray(ray_origin, ray_direction);

    Color albedo(0.8, 0.6, 0.2);
    std::shared_ptr<Material> lambertian = std::make_shared<Lambertian>(albedo);
    MaterializedSphere materialized_sphere(Vec3(0), 2, lambertian);

    std::optional<Hit> result = materialized_sphere.intersect(ray);
    ASSERT_TRUE(result) << "Intersection test failed: Expected a valid Hit, but got nullopt.";

    Hit hit = *result;
    EXPECT_EQ(hit.get_distance(), 3);
    EXPECT_EQ(hit.get_hit_position(), Vec3(0, 0, -2));
    EXPECT_EQ(hit.get_hit_normal(), Vec3(0, 0, -1));
    ASSERT_TRUE(hit.check_ray_outside_sphere());

    const Sphere *hit_sphere = hit.get_sphere();
    Material *material = hit_sphere->get_material();
    EXPECT_EQ(material->get_brdf(), albedo);
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
