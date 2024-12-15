#include <gtest/gtest.h>
#include "../header/color.h"

// テストケース: 引数なしコンストラクタ
TEST(ColorTest, DefaultConstructor)
{
    Color c;
    EXPECT_DOUBLE_EQ(c.r(), 0.0);
    EXPECT_DOUBLE_EQ(c.g(), 0.0);
    EXPECT_DOUBLE_EQ(c.b(), 0.0);
}

// テストケース: 1引数コンストラクタ
TEST(ColorTest, SingleArgumentConstructor)
{
    Color c(0.5);
    EXPECT_DOUBLE_EQ(c.r(), 0.5);
    EXPECT_DOUBLE_EQ(c.g(), 0.5);
    EXPECT_DOUBLE_EQ(c.b(), 0.5);
}

// テストケース: 3引数コンストラクタ
TEST(ColorTest, TripleArgumentConstructor)
{
    Color c(0.1, 0.2, 0.3);
    EXPECT_DOUBLE_EQ(c.r(), 0.1);
    EXPECT_DOUBLE_EQ(c.g(), 0.2);
    EXPECT_DOUBLE_EQ(c.b(), 0.3);
}

// Colorクラスのイコール演算子（==）のテスト
TEST(ColorTest, EqualityOperator)
{
    Color c(0.1, 0.2, 0.3);

    // 正しい値の場合
    EXPECT_TRUE(c == Color(0.1, 0.2, 0.3)) << "c should be equal to Color(0.1, 0.2, 0.3)";

    // rが異なる場合
    EXPECT_FALSE(c == Color(0.2, 0.2, 0.3)) << "c should not be equal to Color(0.2, 0.2, 0.3)";

    // gが異なる場合
    EXPECT_FALSE(c == Color(0.1, 0.1, 0.3)) << "c should not be equal to Color(0.1, 0.1, 0.3)";

    // bが異なる場合
    EXPECT_FALSE(c == Color(0.1, 0.2, 0.4)) << "c should not be equal to Color(0.1, 0.2, 0.4)";

    // 全ての値が異なる場合
    EXPECT_FALSE(c == Color(0.3, 0.1, 0.2)) << "c should not be equal to Color(0.3, 0.1, 0.2)";
}

// Colorクラスのベクトル演算のテスト
TEST(ColorTest, ColorAddition)
{
    Color c1(0.5, 0.5, 0.5), c2(0.1, 0.2, 0.3), result;

    // 加算演算子のテスト
    result = c1 + c2;
    // result = Vec3(6,7,8);
    EXPECT_EQ(result.r(), 0.5 + 0.1) << "r of c1 + c2 should be 0.5 + 0.1";
    EXPECT_EQ(result.g(), 0.5 + 0.2) << "g of c1 + c2 should be 0.5 + 0.2";
    EXPECT_EQ(result.b(), 0.5 + 0.3) << "b of c1 + c2 should be 0.5 + 0.3";

    // 加算代入演算子のテスト
    result += c2;
    EXPECT_EQ(result.r(), 0.5 + 0.1 + 0.1) << "r of result += c2 should be 0.5 + 0.1 + 0.1";
    EXPECT_EQ(result.g(), 0.5 + 0.2 + 0.2) << "g of result += c2 should be 0.5 + 0.2 + 0.2";
    EXPECT_EQ(result.b(), 0.5 + 0.3 + 0.3) << "b of result += c2 should be 0.5 + 0.3 + 0.3";
}

TEST(ColorTest, ColorSubtraction)
{
    Color c1(0.5, 0.5, 0.5), c2(0.1, 0.2, 0.3), result;

    // 減算演算子のテスト
    result = c1 - c2;
    EXPECT_EQ(result.r(), 0.5 - 0.1) << "r of c1 - c2 should be 0.5 - 0.1";
    EXPECT_EQ(result.g(), 0.5 - 0.2) << "g of c1 - c2 should be 0.5 - 0.2";
    EXPECT_EQ(result.b(), 0.5 - 0.3) << "b of c1 - c2 should be 0.5 - 0.3";

    // 減算代入演算子のテスト
    result -= c2;
    EXPECT_EQ(result.r(), 0.5 - 0.1 - 0.1) << "r of result -= c2 should be 0.5 - 0.1 - 0.1";
    EXPECT_EQ(result.g(), 0.5 - 0.2 - 0.2) << "g of result -= c2 should be 0.5 - 0.2 - 0.2";
    EXPECT_EQ(result.b(), 0.5 - 0.3 - 0.3) << "b of result -= c2 should be 0.5 - 0.3 - 0.3";
}

TEST(ColorTest, ColorMultiplication)
{
    Color c1(0.5, 0.5, 0.5), c2(0.1, 0.2, 0.3), result;

    // 乗算演算子のテスト
    result = c1 * c2;
    EXPECT_EQ(result.r(), 0.5 * 0.1) << "r of c1 * c2 should be 0.5 * 0.1";
    EXPECT_EQ(result.g(), 0.5 * 0.2) << "g of c1 * c2 should be 0.5 * 0.2";
    EXPECT_EQ(result.b(), 0.5 * 0.3) << "b of c1 * c2 should be 0.5 * 0.3";

    // 乗算代入演算子のテスト
    result *= c2;
    EXPECT_EQ(result.r(), 0.5 * 0.1 * 0.1) << "r of result *= c2 should be 0.5 * 0.1 * 0.1";
    EXPECT_EQ(result.g(), 0.5 * 0.2 * 0.2) << "g of result *= c2 should be 0.5 * 0.2 * 0.2";
    EXPECT_EQ(result.b(), 0.5 * 0.3 * 0.3) << "b of result *= c2 should be 0.5 * 0.3 * 0.3";
}

TEST(ColorTest, ColorDivision)
{
    Color c1(0.5, 0.5, 0.5), c2(0.1, 0.2, 0.3), result;

    // 除算演算子のテスト
    result = c1 / c2;
    EXPECT_EQ(result.r(), 0.5 / 0.1) << "r of c1 / c2 should be 0.5 / 0.1";
    EXPECT_EQ(result.g(), 0.5 / 0.2) << "g of c1 / c2 should be 0.5 / 0.2";
    EXPECT_EQ(result.b(), 0.5 / 0.3) << "b of c1 / c2 should be 0.5 / 0.3";

    // 除算代入演算子のテスト
    result /= c2;
    EXPECT_EQ(result.r(), 0.5 / 0.1 / 0.1) << "r of result /= c2 should be 0.5 / 0.1 / 0.1";
    EXPECT_EQ(result.g(), 0.5 / 0.2 / 0.2) << "g of result /= c2 should be 0.5 / 0.2 / 0.2";
    EXPECT_EQ(result.b(), 0.5 / 0.3 / 0.3) << "b of result /= c2 should be 0.5 / 0.3 / 0.3";
}

// ベクトルとスカラーの加算
TEST(ColorTest, ColorScalarAddition)
{
    Color c(0.1, 0.2, 0.3), result;
    result = c + 0.1;
    EXPECT_EQ(result.r(), 0.1 + 0.1);
    EXPECT_EQ(result.g(), 0.2 + 0.1);
    EXPECT_EQ(result.b(), 0.3 + 0.1);

    result = 0.1 + c;
    EXPECT_EQ(result.r(), 0.1 + 0.1);
    EXPECT_EQ(result.g(), 0.1 + 0.2);
    EXPECT_EQ(result.b(), 0.1 + 0.3);

    result += 0.1;
    EXPECT_EQ(result.r(), 0.1 + 0.1 + 0.1);
    EXPECT_EQ(result.g(), 0.1 + 0.2 + 0.1);
    EXPECT_EQ(result.b(), 0.1 + 0.3 + 0.1);
}

// ベクトルとスカラーの減算
TEST(ColorTest, ColorScalarSubtraction)
{
    Color c(0.1, 0.2, 0.3), result;
    result = c - 0.1;
    EXPECT_EQ(result.r(), 0.1 - 0.1);
    EXPECT_EQ(result.g(), 0.2 - 0.1);
    EXPECT_EQ(result.b(), 0.3 - 0.1);

    result = 0.1 - c;
    EXPECT_EQ(result.r(), 0.1 - 0.1);
    EXPECT_EQ(result.g(), 0.1 - 0.2);
    EXPECT_EQ(result.b(), 0.1 - 0.3);

    result -= 0.1;
    EXPECT_EQ(result.r(), 0.1 - 0.1 - 0.1);
    EXPECT_EQ(result.g(), 0.1 - 0.2 - 0.1);
    EXPECT_EQ(result.b(), 0.1 - 0.3 - 0.1);
}

// ベクトルとスカラーの乗算
TEST(ColorTest, ColorScalarMultiplication)
{
    Color c(0.1, 0.2, 0.3), result;
    result = c * 5;
    EXPECT_EQ(result.r(), 0.1 * 5);
    EXPECT_EQ(result.g(), 0.2 * 5);
    EXPECT_EQ(result.b(), 0.3 * 5);

    result = 5 * c;
    EXPECT_EQ(result.r(), 5 * 0.1);
    EXPECT_EQ(result.g(), 5 * 0.2);
    EXPECT_EQ(result.b(), 5 * 0.3);

    result *= 5;
    EXPECT_EQ(result.r(), 5 * 0.1 * 5);
    EXPECT_EQ(result.g(), 5 * 0.2 * 5);
    EXPECT_EQ(result.b(), 5 * 0.3 * 5);
}

// ベクトルとスカラーの除算
TEST(ColorTest, ColorScalarDivision)
{
    Color c(0.1, 0.2, 0.3), result;
    result = c / 5;
    EXPECT_DOUBLE_EQ(result.r(), 0.1 / 5);
    EXPECT_DOUBLE_EQ(result.g(), 0.2 / 5);
    EXPECT_DOUBLE_EQ(result.b(), 0.3 / 5);

    result = 5 / c;
    EXPECT_DOUBLE_EQ(result.r(), 5 / 0.1);
    EXPECT_DOUBLE_EQ(result.g(), 5 / 0.2);
    EXPECT_DOUBLE_EQ(result.b(), 5 / 0.3);

    result /= 2;
    EXPECT_DOUBLE_EQ(result.r(), 5 / 0.1 / 2);
    EXPECT_DOUBLE_EQ(result.g(), 5 / 0.2 / 2);
    EXPECT_DOUBLE_EQ(result.b(), 5 / 0.3 / 2);
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}