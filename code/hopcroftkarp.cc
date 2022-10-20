// Trace to find vertex cover and independence set
/*
	Y* = Set of vertices y such that exist an argument path from y to a vertex x which isn't matched
	X* = Set of matched vertices x that x isn't matched with a vertex in Y*

	(X* v Y*) is vertex cover 
*/

struct HopCroft_Karp
{
    const int NoMatch = -1;
    vector<int> h, S, match;
    vector<vector<int>> adj;
    int nx, ny;
    bool found;
    HopCroft_Karp(int nx = 0, int ny = 0)
    {
        this->nx = nx;
        this->ny = ny;
        S.reserve(nx);
        h.resize(ny + 5);
        adj.resize(nx + 5);
        match.resize(ny + 5, NoMatch);
    }
    void Clear()
    {
        for (int i = 1; i <= nx; ++i)
            adj[i].clear();
        S.clear();
        fill(match.begin(), match.end(), NoMatch);
    }
    void AddEdge(int x, int y)
    {
        adj[x].emplace_back(y);
    }
    bool BFS()
    {
        fill(h.begin(), h.end(), 0);
        queue<int> q;
        for (auto x : S)
            for (auto i : adj[x])
                if (h[i] == 0)
                {
                    q.emplace(i);
                    h[i] = 1;
                }
        while (q.size())
        {
            int x, ypop = q.front();
            q.pop();
            if ((x = match[ypop]) == NoMatch)
                return true;
            for (auto i : adj[x])
                if (h[i] == 0)
                {
                    h[i] = h[ypop] + 1;
                    q.emplace(i);
                }
        }
        return false;
    }
    void dfs(int v, int lv)
    {
        for (auto i : adj[v])
            if (h[i] == lv + 1)
            {
                if (match[i] == NoMatch)
                    found = 1;
                else
                    dfs(match[i], lv + 1);
                if (found)
                {
                    match[i] = v;
                    return;
                }
            }
    }
    int MaxMatch()
    {
        int ans(0);
        for (int i = 1; i <= nx; ++i)
            S.emplace_back(i);
        while (BFS())
        {
            for (int i = S.size() - 1; ~i; --i)
            {
                found = 0;
                dfs(S[i], 0);
                if (found)
                {
                    ++ans;
                    S[i] = S.back();
                    S.pop_back();
                }
            }
        }
        return ans;
    }
 
};
