#include <vector>

int l, sz;
std::vector<std::vector<int>> g;
std::vector<int> tin, tout;
int timer;
std::vector<std::vector<int>> up;

void dfs_lca (int v = 0, int p = 0)
{
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i = 1; i <= l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];

	for (size_t i = 0; i < g[v].size(); ++i)
    {
		int to = g[v][i];
		if (to != p)
			dfs_lca (to, v);
	}

	tout[v] = ++timer;
}

bool upper (int v1, int v2)
{
	return tin[v1] <= tin[v2] && tout[v1] >= tout[v2];
}

int lca (int v1, int v2)
{
	if (upper (v1, v2))  return v1;
	if (upper (v2, v1))  return v2;
	for (int i = l; i >= 0; --i)
		if (!upper (up[v1][i], v2))
			v1 = up[v1][i];
	return up[v1][0];
}

int bit_up (int v, int dist)
{
	for (int i = 0; dist > 0; ++i, dist >>= 1)
        if (dist & 1)
            v = up[v][i];

	return v;
}

void SetupLCA()
{
    sz = g.size();
    tin.resize(sz);
    tout.resize(sz);
    up.resize(sz);
	l = 1;
	timer = 0;
	while ((1<<l) <= sz)
        ++l;
	for (int i = 0; i < sz; ++i)
        up[i].resize(l+1);
	dfs_lca(0);
}
