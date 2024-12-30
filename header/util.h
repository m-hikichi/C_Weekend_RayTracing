#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <time.h>

template <typename T> T clamp(T x, T min, T max) {
    if (x < min) return min;
    else if (max < x) return max;
    else return x;
}


template <typename T> T generate_random_in_range(T min, T max) {
    // 0.0 以上 1.0 未満のランダムな浮動小数点数を生成
    double normalized_random_value = static_cast<double>(rand()) / RAND_MAX;
    // [min,max) の実数乱数を返す
    return min + normalized_random_value * (max - min);
}

#endif