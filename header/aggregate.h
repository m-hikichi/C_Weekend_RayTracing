#ifndef AGGREGATE_H
#define AGGREGATE_H
#include <vector>
#include <memory>
#include "sphere.h"

class Aggregate
{
private:
    std::vector<std::shared_ptr<Sphere>> spheres;

public:
    Aggregate() {}
    Aggregate(const std::vector<std::shared_ptr<Sphere>> &_spheres) : spheres(_spheres) {}

    std::vector<std::shared_ptr<Sphere>> get_spheres()
    {
        return spheres;
    }

    void clear() {
        spheres.clear();
    }

    // 物体の追加
    void add(const std::shared_ptr<Sphere> &s)
    {
        spheres.push_back(s);
    }

    // 与えられたレイと全ての物体との間で衝突計算を行い，最も手前に存在する物体との衝突情報を返す
    std::optional<Hit> intersect(const Ray &ray) const
    {
        std::optional<Hit> closest_hit = std::nullopt;

        for (std::shared_ptr<Sphere> sphere : spheres)
        {
            // 各球体の交差を取得
            std::optional<Hit> hit_candidate = sphere->intersect(ray);

            // 交差がある場合
            if (hit_candidate)
            {
                // 最初の交差または、より近い交差が見つかれば更新
                if (!closest_hit || closest_hit->get_distance() > hit_candidate->get_distance())
                {
                    closest_hit = hit_candidate;
                }
            }
        }

        return closest_hit;
    }
};

#endif