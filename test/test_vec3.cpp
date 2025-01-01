#include <gtest/gtest.h>
#include "../header/vec3.h"

// テストケース: 引数なしコンストラクタ
TEST(Vec3Test, DefaultConstructor)
{
    Vec3 v;
    EXPECT_DOUBLE_EQ(v.x, 0.0);
    EXPECT_DOUBLE_EQ(v.y, 0.0);
    EXPECT_DOUBLE_EQ(v.z, 0.0);
}

// テストケース: 1引数コンストラクタ
TEST(Vec3Test, SingleArgumentConstructor)
{
    Vec3 v(5.0);
    EXPECT_DOUBLE_EQ(v.x, 5.0);
    EXPECT_DOUBLE_EQ(v.y, 5.0);
    EXPECT_DOUBLE_EQ(v.z, 5.0);
}

// テストケース: 3引数コンストラクタ
TEST(Vec3Test, TripleArgumentConstructor)
{
    Vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

// Vec3クラスのイコール演算子（==）のテスト
TEST(Vec3Test, EqualityOperator)
{
    Vec3 v(1, 2, 3);

    // 正しい値の場合
    EXPECT_TRUE(v == Vec3(1, 2, 3)) << "v should be equal to Vec3(1, 2, 3)";

    // xが異なる場合
    EXPECT_FALSE(v == Vec3(2, 2, 3)) << "v should not be equal to Vec3(2, 2, 3)";

    // yが異なる場合
    EXPECT_FALSE(v == Vec3(1, 1, 3)) << "v should not be equal to Vec3(1, 1, 3)";

    // zが異なる場合
    EXPECT_FALSE(v == Vec3(1, 2, 4)) << "v should not be equal to Vec3(1, 2, 4)";

    // 全ての値が異なる場合
    EXPECT_FALSE(v == Vec3(3, 1, 2)) << "v should not be equal to Vec3(3, 1, 2)";
}

// Vec3クラスのベクトル演算のテスト
TEST(Vec3Test, VectorAddition)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3), result;

    // 加算演算子のテスト
    result = v1 + v2;
    // result = Vec3(6,7,8);
    EXPECT_EQ(result.x, 6) << "x of v1 + v2 should be 6";
    EXPECT_EQ(result.y, 7) << "y of v1 + v2 should be 7";
    EXPECT_EQ(result.z, 8) << "z of v1 + v2 should be 8";

    // 加算代入演算子のテスト
    result += v2;
    EXPECT_EQ(result.x, 7) << "x of result += v2 should be 7";
    EXPECT_EQ(result.y, 9) << "y of result += v2 should be 9";
    EXPECT_EQ(result.z, 11) << "z of result += v2 should be 11";
}

TEST(Vec3Test, VectorSubtraction)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3), result;

    // 減算演算子のテスト
    result = v1 - v2;
    EXPECT_EQ(result.x, 4) << "x of v1 - v2 should be 4";
    EXPECT_EQ(result.y, 3) << "y of v1 - v2 should be 3";
    EXPECT_EQ(result.z, 2) << "z of v1 - v2 should be 2";

    // 減算代入演算子のテスト
    result -= v2;
    EXPECT_EQ(result.x, 3) << "x of result -= v2 should be 3";
    EXPECT_EQ(result.y, 1) << "y of result -= v2 should be 1";
    EXPECT_EQ(result.z, -1) << "z of result -= v2 should be -1";
}

TEST(Vec3Test, VectorMultiplication)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3), result;

    // 乗算演算子のテスト
    result = v1 * v2;
    EXPECT_EQ(result.x, 5) << "x of v1 * v2 should be 5";
    EXPECT_EQ(result.y, 10) << "y of v1 * v2 should be 10";
    EXPECT_EQ(result.z, 15) << "z of v1 * v2 should be 15";

    // 乗算代入演算子のテスト
    result *= v2;
    EXPECT_EQ(result.x, 5) << "x of result *= v2 should be 5";
    EXPECT_EQ(result.y, 20) << "y of result *= v2 should be 20";
    EXPECT_EQ(result.z, 45) << "z of result *= v2 should be 45";
}

TEST(Vec3Test, VectorDivision)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3), result;

    // 除算演算子のテスト
    result = v1 / v2;
    EXPECT_NEAR(result.x, 5.0, 1e-6) << "x of v1 / v2 should be 5.0";
    EXPECT_NEAR(result.y, 2.5, 1e-6) << "y of v1 / v2 should be 2.5";
    EXPECT_NEAR(result.z, 5.0 / 3, 1e-6) << "z of v1 / v2 should be 5.0 / 3";

    // 除算代入演算子のテスト
    result /= v2;
    EXPECT_NEAR(result.x, 5.0, 1e-6) << "x of result /= v2 should be 5.0";
    EXPECT_NEAR(result.y, 1.25, 1e-6) << "y of result /= v2 should be 1.25";
    EXPECT_NEAR(result.z, 5.0 / 9, 1e-6) << "z of result /= v2 should be 5.0 / 9";
}

// ベクトルとスカラーの加算
TEST(Vec3Test, VectorScalarAddition)
{
    Vec3 v(1, 2, 3), result;
    result = v + 1;
    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);

    result = 1 + v;
    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 3);
    EXPECT_EQ(result.z, 4);

    result += 1;
    EXPECT_EQ(result.x, 3);
    EXPECT_EQ(result.y, 4);
    EXPECT_EQ(result.z, 5);
}

// ベクトルとスカラーの減算
TEST(Vec3Test, VectorScalarSubtraction)
{
    Vec3 v(1, 2, 3), result;
    result = v - 1;
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 1);
    EXPECT_EQ(result.z, 2);

    result = 1 - v;
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.z, -2);

    result -= 1;
    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, -2);
    EXPECT_EQ(result.z, -3);
}

// ベクトルとスカラーの乗算
TEST(Vec3Test, VectorScalarMultiplication)
{
    Vec3 v(1, 2, 3), result;
    result = v * 5;
    EXPECT_EQ(result.x, 5);
    EXPECT_EQ(result.y, 10);
    EXPECT_EQ(result.z, 15);

    result = 5 * v;
    EXPECT_EQ(result.x, 5);
    EXPECT_EQ(result.y, 10);
    EXPECT_EQ(result.z, 15);

    result *= 5;
    EXPECT_EQ(result.x, 25);
    EXPECT_EQ(result.y, 50);
    EXPECT_EQ(result.z, 75);
}

// ベクトルとスカラーの除算
TEST(Vec3Test, VectorScalarDivision)
{
    Vec3 v(1, 2, 3), result;
    result = v / 5;
    EXPECT_DOUBLE_EQ(result.x, 0.2);
    EXPECT_DOUBLE_EQ(result.y, 0.4);
    EXPECT_DOUBLE_EQ(result.z, 0.6);

    result = 5 / v;
    EXPECT_DOUBLE_EQ(result.x, 5);
    EXPECT_DOUBLE_EQ(result.y, 2.5);
    EXPECT_DOUBLE_EQ(result.z, 5.0 / 3);

    result /= 2;
    EXPECT_DOUBLE_EQ(result.x, 2.5);
    EXPECT_DOUBLE_EQ(result.y, 1.25);
    EXPECT_DOUBLE_EQ(result.z, 5.0 / 6);
}

// Vec3クラスのマイナス演算子（-）のテスト
TEST(Vec3Test, NegationOperator)
{
    // 入力ベクトル
    Vec3 v = -Vec3(1, 2, 3);

    // 各成分が正しく負になっているかを検証
    EXPECT_EQ(v.x, -1) << "Negated x of Vec3(1, 2, 3) should be -1";
    EXPECT_EQ(v.y, -2) << "Negated y of Vec3(1, 2, 3) should be -2";
    EXPECT_EQ(v.z, -3) << "Negated z of Vec3(1, 2, 3) should be -3";
}

// Vec3クラスのノルム計算（norm()）のテスト
TEST(Vec3Test, NormCalculation)
{
    // ケース1: 小さな値
    Vec3 v1(0.1, 0, 0);
    EXPECT_DOUBLE_EQ(v1.norm(), 0.1) << "Norm of Vec3(0.1, 0, 0) should be 0.1";

    // ケース2: ピタゴラスの定理に基づく値
    Vec3 v2(3, 4, 0);
    EXPECT_DOUBLE_EQ(v2.norm(), 5.0) << "Norm of Vec3(3, 4, 0) should be 5.0";
}

// Vec3クラスの正規化（normalize()）のテスト
TEST(Vec3Test, Normalization)
{
    Vec3 normalized;
    // ケース1: ノルムが1以下の場合
    Vec3 v1(0.1, 0, 0);
    normalized = v1.normalize();
    EXPECT_NEAR(normalized.x, 1.0, 1e-6) << "Normalized x of Vec3(0.1, 0, 0) should be 1.0";
    EXPECT_NEAR(normalized.y, 0.0, 1e-6) << "Normalized y of Vec3(0.1, 0, 0) should be 0.0";
    EXPECT_NEAR(normalized.z, 0.0, 1e-6) << "Normalized z of Vec3(0.1, 0, 0) should be 0.0";

    // ケース2: ノルムが1以上の場合
    Vec3 v2(3, 4, 0);
    normalized = v2.normalize();
    EXPECT_NEAR(normalized.x, 0.6, 1e-6) << "Normalized x of Vec3(3, 4, 0) should be 0.6";
    EXPECT_NEAR(normalized.y, 0.8, 1e-6) << "Normalized y of Vec3(3, 4, 0) should be 0.8";
    EXPECT_NEAR(normalized.z, 0.0, 1e-6) << "Normalized z of Vec3(3, 4, 0) should be 0.0";
}

// 内積のテスト
TEST(Vec3Test, DotProduct)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3);
    int dot_val = dot(v1, v2);
    EXPECT_EQ(dot_val, 30) << "The dot product of v1 and v2 should be 30";
}

// 外積のテスト
TEST(Vec3Test, CrossProduct)
{
    Vec3 v1(5, 5, 5), v2(1, 2, 3), result;
    result = cross(v1, v2);
    EXPECT_EQ(result.x, 5.0) << "x component of cross product should be 5.0";
    EXPECT_EQ(result.y, -10.0) << "y component of cross product should be -10.0";
    EXPECT_EQ(result.z, 5.0) << "z component of cross product should be 5.0";
}

// spherical_to_cartesianメソッドのテスト
TEST(Vec3Test, SphericalToCartesianTest)
{
    // θ = 0, φ = 0 の場合
    Vec3 result = spherical_to_cartesian(0, 0);
    EXPECT_NEAR(result.x, 0, 1e-6);
    EXPECT_NEAR(result.y, 1, 1e-6);
    EXPECT_NEAR(result.z, 0, 1e-6);

    // θ = π/2, φ = 0 の場合
    result = spherical_to_cartesian(M_PI / 2, 0);
    EXPECT_NEAR(result.x, 0, 1e-6);
    EXPECT_NEAR(result.y, 0, 1e-6);
    EXPECT_NEAR(result.z, 1, 1e-6);

    // θ = π/2, φ = π/2 の場合
    result = spherical_to_cartesian(M_PI / 2, M_PI / 2);
    EXPECT_NEAR(result.x, 1, 1e-6);
    EXPECT_NEAR(result.y, 0, 1e-6);
    EXPECT_NEAR(result.z, 0, 1e-6);
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}