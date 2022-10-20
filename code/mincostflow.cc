struct Edge
{
    int u, v;
    ll c, w;
    Edge(const int &u, const int &v, const ll &c, const ll &w) : u(u), v(v), c(c), w(w) {}
};
struct MaxFlowMinCost
{
    const ll Inf = 1e17;
    int n, source, sink;
    vector<ll> d;
    vector<int> par;
    vector<bool> inqueue;
    vector<Edge> s;
    vector<vector<int>> adj;
    MaxFlowMinCost(int n)
    {
        this->n = n;
        s.reserve(n * 2);
        d.resize(n + 5);
        inqueue.resize(n + 5);
        par.resize(n + 5);
        adj.resize(n + 5);
    }
    void AddEdge(int u, int v, ll c, ll w)
    {
        s.emplace_back(u, v, c, w);
        adj[u].emplace_back(s.size() - 1);
        s.emplace_back(v, u, 0, -w);
        adj[v].emplace_back(s.size() - 1);
    }
    bool SPFA()
    {
        fill(d.begin(), d.end(), Inf);
        fill(par.begin(), par.end(), s.size());
        fill(inqueue.begin(), inqueue.end(), 0);
        d[sink] = 0;
        queue<int> q;
        q.emplace(sink);
        inqueue[sink] = 1;
        while (q.size())
        {
            int c = q.front();
            inqueue[c] = 0;
            q.pop();
            for (auto i : adj[c])
                if (s[i ^ 1].c > 0 && d[s[i].v] > d[c] + s[i ^ 1].w)
                {
                    par[s[i].v] = i ^ 1;
                    d[s[i].v] = d[c] + s[i ^ 1].w;
                    if (!inqueue[s[i].v])
                    {
                        q.emplace(s[i].v);
                        inqueue[s[i].v] = 1;
                    }
                }
        }
        return (d[source] < Inf);
    }
    pair<ll, ll> MaxFlow(int so, int t, ll k)
    {
        source = so;
        sink = t;
        ll Flow(0), cost(0);
        while (k && SPFA())
        {
            ll q(Inf);
            int v = source;
            while (v != sink)
            {
                q = min(q, s[par[v]].c);
                v = s[par[v]].v;
            }

            q = min(q, k);

            cost += d[source] * q;
            Flow += q;
            k -= q;

            v = source;
            while (v != sink)
            {
                s[par[v]].c -= q;
                s[par[v] ^ 1].c += q;
                v = s[par[v]].v;
            }
        }
        return {Flow, cost};
    }
};
