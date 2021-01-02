// Created by BlurringShadow at 2021-01-01-下午 6:40

#pragma once
#include "../algorithm_utility/utils.h"

#include <list>

/*
 * Monocarp was fascinated by BFS so much that, in the end, he lost his tree.
 * Fortunately, he still has a sequence of vertices,
 * in which order vertices were visited by the BFS algorithm (the array a from the pseudocode).
 * Monocarp knows that each vertex was visited exactly once
 * (since they were put and taken from the queue exactly once).
 * Also, he knows that all children of each vertex were viewed in ascending order.
 * Monocarp knows that there are many trees (in the general case) with the same visiting order a,
 * so he doesn't hope to restore his tree.
 * Monocarp is okay with any tree that has minimum height.
 * The height of a tree is the maximum depth of the tree's vertices,
 * and the depth of a vertex is the number of edges in the path from the root to it.
 * For example, the depth of vertex 1 is 0, since it's the root, and the depth of all root's children are 1.
 * Help Monocarp to find any tree with given visiting order a and minimum height.
 */
class minimal_height_tree final
{
    using value_t = uint32_t;

    vector<value_t> vertices_;

    [[nodiscard]] auto solve() const
    {
        using namespace std;
        const auto vertices_size = vertices_.size();
        value_t height = 0;

        const auto end = vertices_.end();
        list<value_t> available_leaf_count{1};

        for(auto it = vertices_.begin() + 1; it != end;)
        {
            const auto next = is_sorted_until(it, end);
            const auto diff = static_cast<value_t>(next - it);

            auto&& leaf_it = available_leaf_count.begin();
            if(--*leaf_it++ == 0) available_leaf_count.pop_front();

            if(leaf_it == available_leaf_count.cend())
            {
                ++height;
                available_leaf_count.emplace_back(diff);
            }
            else *leaf_it += diff;

            it = next;
        }

        return height;
    }

public:
    friend std::ostream& operator<<(std::ostream& os, minimal_height_tree& s) { return os << s.solve() << '\n'; }

    friend std::istream& operator>>(std::istream& is, minimal_height_tree& v)
    {
        v.vertices_.resize(get_from_stream(is));
        for(auto& vertex : v.vertices_) is >> vertex;
        return is;
    }

    minimal_height_tree() noexcept {}
};
