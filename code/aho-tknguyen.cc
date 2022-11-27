struct aho_corasick
{
    struct tk
    {
        ll link;
        ll nxt[27];
        ll par;
        char ch;
        ll go[27];
        ll val;
        ll leaf;
        tk(ll par = -1, char ch = 'a') : par(par), ch(ch)
        {
            memset(nxt, -1, sizeof(nxt));
            memset(go, -1, sizeof(go));
            val = -1;
            link = -1;
            leaf = 0;
        }
    };
    vector<tk> vt;
    void init()
    {
        vt.clear();
        vt.pb({-1, 'a'});
    }
    ll add(string s, ll val)
    {
        ll nw = 0;
        for (auto to : s)
        {
            if (vt[nw].nxt[to - 'a' + 1] == -1)
            {
                vt[nw].nxt[to - 'a' + 1] = vt.size();
                vt.pb({nw, to});
            }
            nw = vt[nw].nxt[to - 'a' + 1];
        }
        vt[nw].leaf = val;
        return nw;
    }
    ll get_val(ll u)
    {
        if (u == 0)
            return 0;
        if (vt[u].val == -1)
        {
            vt[u].val = vt[u].leaf + get_val(get_link(u));
        }
        return vt[u].val;
    }
    ll go(ll v, ll t)
    {
        if (vt[v].go[t] == -1)
        {
            if (vt[v].nxt[t] != -1)
            {
                vt[v].go[t] = vt[v].nxt[t];
            }
            else
            {
                if (v == 0)
                    vt[v].go[t] = 0;
                else
                    vt[v].go[t] = go(get_link(v), t);
            }
        }
        return vt[v].go[t];
    }
    ll get_link(ll v)
    {
        if (vt[v].link == -1)
        {
            if (vt[v].par == 0 || v == 0)
                vt[v].link = 0;
            else
                vt[v].link = go(get_link(vt[v].par), vt[v].ch - 'a' + 1);
        }
        return vt[v].link;
    }
    ll get(string s)
    {
        ll nw = 0;
        ll ans = 0;
        for (auto to : s)
        {
            nw = go(nw, to - 'a' + 1);
            ans += get_val(nw);
        }
        return ans;
    }
};