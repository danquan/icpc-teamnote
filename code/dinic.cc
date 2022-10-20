// In case we need to find Maximum flow of network with both minimum capacity and maximum capacity, let s* and t* be virtual source and virtual sink.

/*
Then, each edge (u->v) with lower cap l and upper cap r will be changed in to 3 edge:

- u->v whit capacity r-l
- u->t* with capacity l
- s*->v with capacity l
*/

// We need add one other edge t->s with capacity Inf
// Maximum Flow on original graph is the Maximum Flow on new graph: s*->t*

struct Edge
{
    int u, v;
    ll c;
    Edge() {}
    Edge(int u, int v, ll c)
    {
        this->u = u;
        this->v = v;
        this->c = c;
    }
};
struct Dinic
{
    const ll Inf = 1e17;
    vector<vector<int>> adj;
    vector<vector<int>::iterator> cur;
    vector<Edge> s;
    vector<int> h;
    int sink, t;
    int n;
    Dinic(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        h.resize(n + 1);
        cur.resize(n + 1);
        s.reserve(n);
    }
    void AddEdge(int u, int v, ll c)
    {
        s.emplace_back(u, v, c);
        adj[u].push_back(s.size() - 1);
        s.emplace_back(v, u, 0);
        adj[v].push_back(s.size() - 1);
    }
    bool BFS()
    {
        fill(h.begin(), h.end(), n + 2);
        queue<int> pq;
        h[t] = 0;
        pq.emplace(t);
        while (pq.size())
        {
            int c = pq.front();
            pq.pop();
            for (auto i : adj[c])
                if (h[s[i ^ 1].u] == n + 2 && s[i ^ 1].c != 0)
                {
                    h[s[i ^ 1].u] = h[c] + 1;
                    if (s[i ^ 1].u == sink)
                        return true;
                    pq.emplace(s[i ^ 1].u);
                }
        }
        return false;
    }
    ll DFS(int v, ll flowin)
    {
        if (v == t)
            return flowin;
        ll flowout = 0;
        for (; cur[v] != adj[v].end(); ++cur[v])
        {
            int i = *cur[v];
            if (h[s[i].v] + 1 != h[v] || s[i].c == 0)
                continue;
            ll q = DFS(s[i].v, min(flowin, s[i].c));
            flowout += q;
            if (flowin != Inf)
                flowin -= q;
            s[i].c -= q;
            s[i ^ 1].c += q;
            if (flowin == 0)
                break;
        }
        return flowout;
    }
    void BlockFlow(ll &flow)
    {
        for (int i = 1; i <= n; ++i)
            cur[i] = adj[i].begin();
        flow += DFS(sink, Inf);
    }
    ll MaxFlow(int s, int t)
    {
        this->sink = s;
        this->t = t;
        ll flow = 0;
        while (BFS())
            BlockFlow(flow);
        return flow;
    }
};

