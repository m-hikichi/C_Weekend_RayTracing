#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <ctime>
#include <random>
#include <type_traits>

template <typename T> T clamp(T x, T min, T max) {
    if (x < min) return min;
    else if (max < x) return max;
    else return x;
}


template <typename T> T rnd(T min, T max) {
    // C++11以上のランダムエンジンを使用
    static std::mt19937 mt(std::random_device{}());

    if constexpr (std::is_integral<T>::value) {
        // 整数型の場合、std::uniform_int_distributionを使用
        std::uniform_int_distribution<T> dist(min, max);
        return dist(mt);
    } else if constexpr (std::is_floating_point<T>::value) {
        // 浮動小数点型の場合、std::uniform_real_distributionを使用
        std::uniform_real_distribution<T> dist(min, max);
        return dist(mt);
    } else {
        // その他の型はサポート外
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
        return T();
    }
}

#endif