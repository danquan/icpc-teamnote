
// Biconnected Component Tree
// 1 is the root of Tree
// n + i is the node that represent i-th bcc, its depth is even

const int N = 3e5 + 5; // Change size to n + number of bcc (For safety, set N >= 2 * n)
int n, nBicon, nTime;
int low[N], num[N];
vector<int> adj[N], nadj[N];
vector<int> s;

void dfs(int v, int p = -1)
{
    low[v] = num[v] = ++nTime;
    s.emplace_back(v);

    for (auto i : adj[v])
        if (i != p)
        {
            if (!num[i])
            {
                dfs(i, v);
                low[v] = min(low[v], low[i]);

                if (low[i] >= num[v])
                {
                    ++nBicon;
                    nadj[v].emplace_back(n + nBicon);

                    int vertex;
                    do
                    {
                        vertex = s.back();
                        s.pop_back();

                        nadj[n + nBicon].emplace_back(vertex);
                    } while (vertex != i);
                }
            }
            else
                low[v] = min(low[v], num[i]);
        }
}