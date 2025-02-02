
### Google Test（gtest）の利用**
Google Testは、Googleが提供するC++テストフレームワークで、広く使われています。ここでは、Google Testを使って簡単なテストコードを実行する手順を紹介します。

#### 1. Google Testのインストール
Google TestをUbuntuにインストールする手順は以下の通りです。
```bash
sudo apt update
sudo apt install  libgtest-dev cmake
cd /usr/src/gtest
sudo cmake .
sudo make
```

#### 2. テストコードの書き方
以下の例は、`Vec3`クラスのコンストラクタをテストするコードです。

```cpp
#include <gtest/gtest.h>
#include "../header/vec3.h"

// テストケース: 引数なしコンストラクタ
TEST(Vec3Test, DefaultConstructor) {
    Vec3 v0;
    EXPECT_DOUBLE_EQ(v0.x(), 0.0);
    EXPECT_DOUBLE_EQ(v0.y(), 0.0);
    EXPECT_DOUBLE_EQ(v0.z(), 0.0);
}

// テストケース: 1引数コンストラクタ
TEST(Vec3Test, SingleArgumentConstructor) {
    Vec3 v1(5.0);
    EXPECT_DOUBLE_EQ(v1.x(), 5.0);
    EXPECT_DOUBLE_EQ(v1.y(), 5.0);
    EXPECT_DOUBLE_EQ(v1.z(), 5.0);
}

// テストケース: 3引数コンストラクタ
TEST(Vec3Test, TripleArgumentConstructor) {
    Vec3 v2(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v2.x(), 1.0);
    EXPECT_DOUBLE_EQ(v2.y(), 2.0);
    EXPECT_DOUBLE_EQ(v2.z(), 3.0);
}

// メイン関数（Google Testのエントリーポイント）
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

#### 3. テストのビルドと実行
テストコードをビルドして実行するには、以下のコマンドを使います。
- ビルド
    ```bash
    g++ test_vec3.cpp -o a.out -std=c++17 -lgtest -lgtest_main -pthread
    ```
- 実行
    ```bash
    ./a.out
    ```

#### 4. 実行結果の例
テストが成功した場合、次のような出力が得られます。
```
[==========] Running 3 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 3 tests from Vec3Test
[ RUN      ] Vec3Test.DefaultConstructor
[       OK ] Vec3Test.DefaultConstructor (0 ms)
[ RUN      ] Vec3Test.SingleArgumentConstructor
[       OK ] Vec3Test.SingleArgumentConstructor (0 ms)
[ RUN      ] Vec3Test.TripleArgumentConstructor
[       OK ] Vec3Test.TripleArgumentConstructor (0 ms)
[----------] 3 tests from Vec3Test (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 3 tests.
```

