#include <gtest/gtest.h>
#include "../header/util.h"

// clamp関数のテスト
TEST(UtilTest, ClampFunction)
{
    // 整数型のテスト
    EXPECT_EQ(clamp(5, 1, 10), 5);  // 範囲内
    EXPECT_EQ(clamp(-5, 0, 10), 0); // 範囲外（下限）
    EXPECT_EQ(clamp(15, 0, 10), 10); // 範囲外（上限）

    // 浮動小数点型のテスト
    EXPECT_DOUBLE_EQ(clamp(5.5, 1.0, 10.0), 5.5);  // 範囲内
    EXPECT_DOUBLE_EQ(clamp(-5.5, 0.0, 10.0), 0.0); // 範囲外（下限）
    EXPECT_DOUBLE_EQ(clamp(15.5, 0.0, 10.0), 10.0); // 範囲外（上限）
}

// rnd関数のテスト（整数型）
TEST(UtilTest, RandomInteger) {
    constexpr int min = 1;
    constexpr int max = 10;
    constexpr int test_iterations = 1000;

    for (int i = 0; i < test_iterations; ++i) {
        int value = rnd(min, max);
        EXPECT_GE(value, min) << "Generated value is less than min";
        EXPECT_LE(value, max) << "Generated value is greater than max";
    }
}

// rnd関数のテスト（浮動小数点型）
TEST(UtilTest, RandomFloatingPoint) {
    constexpr double min = 1.0;
    constexpr double max = 10.0;
    constexpr int test_iterations = 1000;

    for (int i = 0; i < test_iterations; ++i) {
        double value = rnd(min, max);
        EXPECT_GE(value, min) << "Generated value is less than min";
        EXPECT_LE(value, max) << "Generated value is greater than max";
    }
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
