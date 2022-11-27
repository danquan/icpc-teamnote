namespace ufs
{
    struct node
    {
        int fa, val, size;
    } t[30];
    struct info
    {
        int x, y;
        node a, b;
    } st[30];
    inline void pre()
    {
        for (int i = 1; i <= n; i++)
            t[i] = (node){i, 0, 1};
    }
    inline int find(int x)
    {
        while (t[x].fa != x)
            x = t[x].fa;
        return x;
    }
    inline int dis(int x)
    {
        int ans = 0;
        while (t[x].fa != x)
            ans ^= t[x].val, x = t[x].fa;
        return ans;
    }
    inline void link(int x, int y)
    {
        int val = dis(x) ^ dis(y) ^ 1;
        x = find(x);
        y = find(y);
        if (t[x].size > t[y].size)
            swap(x, y);
        t[x].fa = y;
        t[x].val = val;
        t[y].size += t[x].size;
    }

}
using namespace ufs;