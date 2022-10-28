// start from 1
// O(n^2)
struct Maximum_matching
{
    int nx, ny, t;
    vector<int> Visited, match;
    vector<vector<int>> a;

    Maximum_matching(int nx = 0, int ny = 0)
    {
        Assign(nx, ny);
    }

    void Assign(int nx, int ny)
    {
        this->nx = nx;
        this->ny = ny;
        t = 0;
        Visited.assign(nx + 5, 0);
        match.assign(ny + 5, 0);
        a.resize(nx + 5, {});
    }

    void AddEdge(int x, int y)
    {
        a[x].emplace_back(y);
    }

    bool visit(int u)
    {
        if (Visited[u] != t)
            Visited[u] = t;
        else
            return false;

        for (int i = 0; i < a[u].size(); i++)
        {
            int v = a[u][i];
            if (!match[v] || visit(match[v]))
            {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int MaxMatch()
    {
        int ans(0);

        for (int i = 1; i <= nx; i++)
        {
            t++;
            ans += visit(i);
        }

        return ans;
    }
};