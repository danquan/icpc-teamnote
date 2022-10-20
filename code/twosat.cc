// start from 0
// pos(V) is the vertex that represent V in graph
// neg(V) is the vertex that represent !V
// pos(V) ^ neg(V) = 1, use two functions below
// (U v V) <=> (!U -> V) <=> (!V -> U)
// You need do addEge(represent(U), represent(V))
// solve() == false mean no answer
// Want to get the answer ?
// color[pos(U)] = 1 means we choose U
// otherwise, we don't
constexpr int N = 1e5 + 5; // Keep N double of n
inline int pos(int u) { return u << 1; }
inline int neg(int u) { return u << 1 | 1; }
struct TwoSAT
{
    int n, numComp, cntTarjan;
    vector<int> adj[N], stTarjan;
    int low[N], num[N], root[N], color[N];
    TwoSAT(int n) : n(n * 2)
    {
        memset(root, -1, sizeof root);
        memset(low, -1, sizeof low);
        memset(num, -1, sizeof num);
        memset(color, -1, sizeof color);
        cntTarjan = 0;
        stTarjan.clear();
    }
    void addEdge(int u, int v)
    {
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
    }
    void tarjan(int u)
    {
        stTarjan.push_back(u);
        num[u] = low[u] = cntTarjan++;
        for (int v : adj[u])
        {
            if (root[v] != -1)
                continue;
            if (low[v] == -1)
                tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u])
        {
            while (1)
            {
                int v = stTarjan.back();
                stTarjan.pop_back();
                root[v] = numComp;
                if (u == v)
                    break;
            }
            numComp++;
        }
    }
    bool solve()
    {
        for (int i = 0; i < n; i++)
            if (root[i] == -1)
                tarjan(i);
        for (int i = 0; i < n; i += 2)
        {
            if (root[i] == root[i ^ 1])
                return 0;
            color[i] = (root[i] < root[i ^ 1]);
        }
        return 1;
    }
};