#include <vector>
#include <stack>
#include <algorithm>

struct EulerianTrail
{
    std::vector<std::vector<std::pair<int, int>>> g;
    std::vector<std::pair<int, int>> es;
    int M;
    std::vector<int> used_vertex, used_edge, deg;

    explicit EulerianTrail(int V) : g(V), M(0), deg(V), used_vertex(V) {}

    void add_edge(int a, int b)
    {
        es.emplace_back(a, b);
        g[a].emplace_back(b, M);

        g[b].emplace_back(a, M);
        deg[a]++;
        deg[b]++;

        M++;
    }

    std::pair<int, int> get_edge(int idx) const
    {
        return es[idx];
    }

    std::vector<std::vector<int>> enumerate_eulerian_trail()
    {
        for(auto &p : deg) if(p & 1) return {};

        used_edge.assign(M, 0);
        std::vector<std::vector<int>> ret;
        for(int i = 0; i < (int) g.size(); i++)
        {
            if(g[i].empty() || used_vertex[i]) continue;
            ret.emplace_back(enumerate_eulerian_trail_in_component(i));
        }
        return ret;
    }

    std::vector<int> enumerate_eulerian_trail_in_component(int s)
    {
        std::stack<std::pair<int,int>> st;
        std::vector<int> ord;
        st.emplace(s, -1);

        while (!st.empty())
        {
            int idx = st.top().first;
            used_vertex[idx] = true;

            if (g[idx].empty())
            {
                ord.emplace_back(st.top().second);
                st.pop();
            }
            else
            {
                auto e = g[idx].back();
                g[idx].pop_back();
                if(used_edge[e.second]) continue;
                used_edge[e.second] = true;
                st.emplace(e);
            }
        }
        ord.pop_back();
        std::reverse(ord.begin(), ord.end());
        return ord;
    }

    std::vector<int> GetEuler(int start = 0) // returns sequence of vertices in the component of vertex 'start'
    {
        std::vector<int> v = enumerate_eulerian_trail()[0];

        auto build = [&](int init) -> std::vector<int>
        {
            std::vector<int> ret;
            int now = init;
            for (auto ie : v)
            {
                ret.emplace_back(now);
                if (now != es[ie].first and now != es[ie].second) return {};
                now = now ^ es[ie].first ^ es[ie].second;
            }
            return ret;
        };

        std::vector<int> ret1 = build(es[v[0]].first);
        std::vector<int> ret2 = build(es[v[0]].second);
        if (ret1.empty())
            return ret2;
        return ret1;
    }
};
