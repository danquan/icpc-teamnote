struct bipartite_graph
{
    int nx, ny;
    vector<vector<int>> gr;
    vector<int> match, x_not_matched;

    vector<int> level;

    bool found;

    void init(int _nx, int _ny)
    {
        nx = _nx;
        ny = _ny;
        gr.assign(nx, vector<int>());
        x_not_matched.resize(nx);
        for (int i = 0; i < nx; ++i)
            x_not_matched[i] = i;
        match.assign(ny, -1);
        level.resize(ny);
    }

    void add_edge(int x, int y)
    {
        gr[x].push_back(y);
    }

    bool bfs()
    {
        fill(level.begin(), level.end(), 0);
        queue<int> q;
        for (auto &x : x_not_matched)
            for (auto &y : gr[x])
                if (level[y] == 0)
                {
                    level[y] = 1;
                    q.push(y);
                }
        while (!q.empty())
        {
            int ypop = q.front();
            q.pop();
            int x = match[ypop];
            if (x == -1)
                return true;
            for (auto &y : gr[x])
                if (level[y] == 0)
                {
                    level[y] = level[ypop] + 1;
                    q.push(y);
                }
        }
        return false;
    }

    void dfs(int x, int lv)
    {
        for (auto &y : gr[x])
            if (level[y] == lv + 1)
            {
                level[y] = 0;
                if (match[y] == -1)
                    found = true;
                else
                    dfs(match[y], lv + 1);
                if (found)
                {
                    match[y] = x;
                    return;
                }
            }
    }

    int max_matching()
    {
        int res = 0;
        while (bfs())
        {
            for (int i = sz(x_not_matched) - 1; i >= 0; --i)
            {
                found = false;
                dfs(x_not_matched[i], 0);
                if (found)
                {
                    ++res;
                    x_not_matched[i] = x_not_matched.back();
                    x_not_matched.pop_back();
                }
            }
        }
        return res;
    }
} man;
