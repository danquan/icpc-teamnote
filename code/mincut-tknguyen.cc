typedef long long LL;

struct Edge
{
    int u, v;
    LL cap, flow;
    Edge() {}
    Edge(int u, int v, LL cap) : u(u), v(v), cap(cap), flow(0) {}
};

bool chk[maxn];
vector<pll> mincut;
struct Dinic
{
    int N;
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> d, pt;

    Dinic(int N) : N(N), E(0), g(N), d(N), pt(N) {}

    void AddEdge(int u, int v, LL cap)
    {
        //  cout <<u<<" "<<v<<" "<<cap<<endl;
        if (u != v)
        {
            E.emplace_back(u, v, cap);
            g[u].emplace_back(E.size() - 1);
            E.emplace_back(v, u, 0);
            g[v].emplace_back(E.size() - 1);
        }
    }

    bool BFS(int S, int T)
    {
        queue<int> q({S});
        fill(d.begin(), d.end(), N + 1);
        d[S] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == T)
                break;
            for (int k : g[u])
            {
                Edge &e = E[k];
                if (e.flow < e.cap && d[e.v] > d[e.u] + 1)
                {
                    d[e.v] = d[e.u] + 1;
                    q.emplace(e.v);
                }
            }
        }
        return d[T] != N + 1;
    }

    LL DFS(int u, int T, LL flow = -1)
    {
        if (u == T || flow == 0)
            return flow;
        for (int &i = pt[u]; i < g[u].size(); ++i)
        {
            Edge &e = E[g[u][i]];
            Edge &oe = E[g[u][i] ^ 1];
            if (d[e.v] == d[e.u] + 1)
            {
                LL amt = e.cap - e.flow;
                if (flow != -1 && amt > flow)
                    amt = flow;
                if (LL pushed = DFS(e.v, T, amt))
                {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    void dfs1(ll u)
    {
        // cout <<u<<endl;
        chk[u] = 1;
        for (int k : g[u])
        {
            Edge e = E[k];
            if (e.cap - e.flow > 0)
            {
                ll nxt = e.v;
                if (!chk[nxt])
                    dfs1(nxt);
            }
        }
    }
    void find_mincut(ll S)
    {
        dfs1(S);
        for (int i = 0; i < E.size(); i += 2)
        {
            auto p = E[i];
            if (chk[p.u] && !chk[p.v])
            {
                mincut.pb(make_pair(p.u, p.v));
            }
        }
    }

    LL MaxFlow(int S, int T)
    {
        LL total = 0;
        while (BFS(S, T))
        {
            fill(pt.begin(), pt.end(), 0);
            while (LL flow = DFS(S, T))
                total += flow;
        }
        return total;
    }
};