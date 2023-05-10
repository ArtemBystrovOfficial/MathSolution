#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

namespace knapsack {

    struct Bug {
        int weight, size = 1;
    };

    struct Object {
        int price, weight, count = 1, size = 1;
    };

    class Mode {
    public:
        Mode(std::deque <Object>&& objects, Bug bug)
            : m_objects(objects),
            bug(bug),
            dp(objects.size() + 1, std::vector<int>(bug.weight + 1)) {
            m_objects.push_front({});
        }
        virtual int exec() = 0;
    protected:
        int getMax() {
            int out = 0;
            std::for_each(std::begin(dp), std::end(dp), [&](const std::vector<int>& vec) {
                out = std::max(out, *std::max_element(std::begin(vec), std::end(vec)));
                });
            return out;
        }

        std::deque <Object> m_objects;
        std::vector<std::vector<int>> dp;
        Bug bug;
    };

    class Mode0_1 : public Mode {
    public:
        Mode0_1(std::deque <Object>&& objects, Bug bug) : Mode(std::move(objects), bug) {}
        int exec() override {
            for (int i = 1; i < dp.size(); i++)
                for (int j = 0; j < bug.weight + 1; j++)
                    if (m_objects[i].weight <= j)
                        dp[i][j] = std::max(dp[i][j],
                            dp[i - 1][j - m_objects[i].weight] + m_objects[i].price);
                    else
                        dp[i][j] = dp[i - 1][j];

            return getMax();
        }
    };

    class ModeLimited : public Mode {
    public:
        ModeLimited(std::deque <Object>&& objects, Bug bug) : Mode(std::move(objects), bug) {}
        int exec() override {
            for (int i = 1; i < dp.size(); i++)
                for (int j = 0; j < bug.weight + 1; j++)
                    for (int count = 0; count < std::min(m_objects[i].count, bug.weight / m_objects[i].weight) + 1; ++count)
                        if (m_objects[i].weight * count <= j)
                            dp[i][j] = std::max(dp[i][j],
                                dp[i - 1][j - m_objects[i].weight * count]
                                + m_objects[i].price * count);
            return getMax();
        }
    };

    class ModeUnlimited : public Mode {
    public:
        ModeUnlimited(std::deque <Object>&& objects, Bug bug) : Mode(std::move(objects), bug) {}
        int exec() override {
            for (int i = 1; i < dp.size(); i++)
                for (int j = 0; j < bug.weight + 1; j++)
                    if (m_objects[i].weight <= j)
                        dp[i][j] = std::max(dp[i][j],
                            dp[i][j - m_objects[i].weight] + m_objects[i].price);
                    else
                        dp[i][j] = dp[i - 1][j];

            return getMax();
        }
    };

    class ModeMultyArg0_1 : public Mode {
    public:
        ModeMultyArg0_1(std::deque <Object>&& objects, Bug bug) : Mode(std::move(objects), bug) {
            m_objects.pop_front();
        }
        int exec() override {
            int n = m_objects.size();
            int out = 0;
            int full_size, full_weight, full_cost;
            for (int j = 0; j < n + 1; j++) {
                std::vector<bool> v(n);
                std::fill(v.end() - j, v.end(), true);
                do {
                    full_size = 0;
                    full_weight = 0;
                    full_cost = 0;
                    for (int i = 0; i < n; ++i) {
                        if (v[i]) {
                            full_size += m_objects[i].size;
                            full_weight += m_objects[i].weight;
                            full_cost += m_objects[i].price;
                        }
                    }
                    if (full_size <= bug.size && full_weight <= bug.weight)
                        out = std::max(out, full_cost);
                } while (std::next_permutation(v.begin(), v.end()));
            }
            return out;
        }
    };

    struct Bug1 {
        int weight;
    };

    struct Bug2 {
        int weight, size;
    };

    template<class bg>
    struct Object1_0 {
        int price;
        bg bug;
    };

    template<class bg>
    struct ObjectUnlimited {
        int price;
        bg bug;
    };

    template<class bg>
    struct ObjectLimited {
        int price;
        int count;
        bg bug;
    };

    template <class Obj, class Bg>
    int makeTask(const std::deque <Obj>& objects, Bg bug) {
        std::deque<Object> out_objects(objects.size());
        Bug out_bug;
        if constexpr (std::is_same_v<Bg, Bug1>) {
            if constexpr (std::is_same_v<Obj, Object1_0<Bug1> >) {
                std::transform(objects.begin(), objects.end(), out_objects.begin(), [](const auto& obj) {
                    return Object{ obj.price, obj.bug.weight };
                    });
                out_bug.weight = bug.weight;
                Mode0_1 mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
            if constexpr (std::is_same_v<Obj, ObjectUnlimited<Bug1> >) {
                std::transform(objects.begin(), objects.end(), out_objects.begin(), [](const auto& obj) {
                    return Object{ obj.price, obj.bug.weight };
                    });
                out_bug.weight = bug.weight;
                ModeUnlimited mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
            if constexpr (std::is_same_v<Obj, ObjectLimited<Bug1> >) {
                std::transform(objects.begin(), objects.end(), out_objects.begin(), [](const auto& obj) {
                    return Object{ obj.price, obj.bug.weight, obj.count };
                    });
                out_bug.weight = bug.weight;
                ModeLimited mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
        }
        if constexpr (std::is_same_v<Bg, Bug2>) {
            if constexpr (std::is_same_v<Obj, Object1_0<Bug2> >) {
                std::transform(objects.begin(), objects.end(), out_objects.begin(), [](const auto& obj) {
                    return Object{ obj.price, obj.bug.weight, 1, obj.bug.size };
                    });
                out_bug.weight = bug.weight;
                out_bug.size = bug.size;
                ModeMultyArg0_1 mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
            if constexpr (std::is_same_v<Obj, ObjectUnlimited<Bug2> >) {
                std::for_each(objects.begin(), objects.end(), [&](const auto& obj) {
                    for (int i = 0; i < std::max(bug.weight / obj.bug.weight + 1, bug.size / obj.bug.size + 1); i++)
                        out_objects.push_back(Object{ obj.price, obj.bug.weight, 1, obj.bug.size });
                    });
                out_bug.weight = bug.weight;
                out_bug.size = bug.size;
                ModeMultyArg0_1 mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
            if constexpr (std::is_same_v<Obj, ObjectLimited<Bug2> >) {
                std::for_each(objects.begin(), objects.end(), [&](const auto& obj) {
                    for (int i = 0; i < obj.count; i++)
                        out_objects.push_back(Object{ obj.price, obj.bug.weight, 1, obj.bug.size });
                    });
                out_bug.weight = bug.weight;
                out_bug.size = bug.size;
                ModeMultyArg0_1 mode(std::move(out_objects), out_bug);
                return mode.exec();
            }
        }
    }
}
