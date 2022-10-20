struct tk
{
    map<ll, ll> nxt;
    ll par, f, len;
    ll link;
    tk(ll par = -1, ll f = 0, ll len = 0) : par(par), f(f), len(len)
    {
        nxt.clear();
        link = -1;
    }
};

struct Suffix_Tree
{
    vector<tk> st;
    ll node;
    ll dis;
    s
        ll n;
    vector<ll> s;
    void init()
    {
        st.clear();
        node = 0;
        dis = 0;
        st.emplace_back(-1, 0, base);
        n = 0;
    }

    void go_edge()
    {
        while (dis > st[st[node].nxt[s[n - dis]]].len)
        {
            node = st[node].nxt[s[n - dis]];
            dis -= st[node].len;
        }
    }

    void add_char(ll c)
    {
        ll last = 0;
        s.pb(c);
        n = s.size();
        dis++;
        while (dis > 0)
        {
            go_edge();
            ll edge = s[n - dis];
            ll &v = st[node].nxt[edge];
            ll t = s[st[v].f + dis - 1];
            if (v == 0)
            {
                v = st.size();
                st.emplace_back(node, n - dis, base);
                st[last].link = node;
                last = 0;
            }
            else if (c == t)
            {
                st[last].link = node;
                return;
            }
            else
            {
                ll u = st.size();
                st.emplace_back(node, st[v].f, dis - 1);
                st[u].nxt[c] = st.size();
                st.emplace_back(u, n - 1, base);
                st[u].nxt[t] = v;
                st[v].f += (dis - 1);
                st[v].len -= (dis - 1);
                v = u;
                st[last].link = u;
                last = u;
            }
            if (node == 0)
                dis--;
            else
                node = st[node].link;
        }
    }
};
