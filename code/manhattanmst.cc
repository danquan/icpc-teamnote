// Idea is to reduce number of edges which are candidates to be in the MST
// Then apply Kruskal algorithm to find MST

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int N = 2e5 + 2;
constexpr ll Inf = 1e17;

namespace manhattanMST
{
    /// disjoint set union
    struct dsu
    {
        int par[N];
        dsu()
        {
            memset(par, -1, sizeof par);
        }

        int findpar(int v)
        {
            return par[v] < 0 ? v : par[v] = findpar(par[v]);
        }

        bool Merge(int u, int v)
        {
            u = findpar(u);
            v = findpar(v);
            if (u == v)
                return false;

            if (par[u] < par[v])
                swap(u, v);

            par[v] += par[u];
            par[u] = v;

            return true;
        }
    };

    // Fenwick Tree Min

    struct FenwickTreeMin
    {
        pair<ll, int> a[N];
        int n;

        FenwickTreeMin(int n = 0)
        {
            Assign(n);
        }

        void Assign(int n)
        {
            this->n = n;
            fill(a, a + n + 1, make_pair(Inf, -1));
        }

        void Update(int p, pair<ll, int> v)
        {
            for (; p <= n; p += p & -p)
                a[p] = min(a[p], v);
        }

        pair<ll, int> Get(int p)
        {
            pair<ll, int> ans({Inf, -1});

            for (; p; p -= p & -p)
                ans = min(ans, a[p]);
            return ans;
        }
    };

    struct Edge
    {
        int u, v;
        ll w;
        Edge(const int &u = 0, const int &v = 0, const ll &w = 0) : u(u), v(v), w(w) {}
        bool operator<(const Edge &a) const
        {
            return w < a.w;
        }
    };

    int n;
    ll x[N], y[N];
    vector<Edge> edges;

    ll dist(int i, int j)
    {
        return abs(x[i] - x[j]) + abs(y[i] - y[j]);
    }

#define Find(x, v) (lower_bound(x.begin(), x.end(), v) - x.begin() + 1)
    void createEdge(int a1, int a2, int b1, int b2, int c1, int c2)
    {
        vector<array<ll, 4>> v;
        vector<ll> s;

        for (int i = 1; i <= n; i++)
        {
            v.push_back({a1 * x[i] + a2 * y[i],
                         b1 * x[i] + b2 * y[i],
                         c1 * x[i] + c2 * y[i],
                         i});
            s.emplace_back(b1 * x[i] + b2 * y[i]);
        }
        sort(s.begin(), s.end());
        s.resize(unique(s.begin(), s.end()) - s.begin());
        sort(v.begin(), v.end());

        FenwickTreeMin f(n);

        for (auto [num1, num2, cost, idx] : v)
        {
            num2 = Find(s, num2);

            int res = f.Get(num2).second;
            if (res != -1)
                edges.emplace_back(res, idx, dist(res, idx));

            f.Update(num2, make_pair(cost, idx));
        }
    }

    void calc()
    {
        edges.clear();

        createEdge(1, -1, -1, 0, 1, 1);  // R1
        createEdge(-1, 1, 0, -1, 1, 1);  // R2
        createEdge(-1, -1, 0, 1, 1, -1); // R3
        createEdge(1, 1, -1, 0, 1, -1);  // R4
        createEdge(-1, 1, 1, 0, -1, -1); // R5
        createEdge(1, -1, 0, 1, -1, -1); // R6
        createEdge(1, 1, 0, -1, -1, 1);  // R7
        createEdge(-1, -1, 1, 0, -1, 1); // R8

        dsu f;

        sort(edges.begin(), edges.end());
        vector<pair<int, int>> res;
        ll ans(0);

        for (auto i : edges)
            if (f.Merge(i.u, i.v))
            {
                ans += i.w;
                res.emplace_back(i.u, i.v);
            }

        cout << ans << "\n";

        for (auto i : res)
            cout << i.first << " " << i.second << "\n";
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> manhattanMST::n;

    for (int i = 1; i <= manhattanMST::n; ++i)
        cin >> manhattanMST::x[i] >> manhattanMST::y[i];

    manhattanMST::calc();
}