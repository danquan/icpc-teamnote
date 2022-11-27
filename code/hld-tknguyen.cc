ll st[4 * maxn];
ll la[4 * maxn];
void dosth(ll id, ll left, ll right)
{
    if (left == right)
        return;
    st[id * 2] = min(st[id * 2], la[id]);
    st[id * 2 + 1] = min(st[id * 2 + 1], la[id]);
    la[id * 2] = min(la[id * 2], la[id]);
    la[id * 2 + 1] = min(la[id * 2 + 1], la[id]);
    la[id] = base;
}
void update(ll id, ll left, ll right, ll x, ll y, ll w)
{
    if (x > right || y < left)
        return;
    if (x <= left && y >= right)
    {
        st[id] = min(st[id], w);
        la[id] = min(la[id], w);
        return;
    }
    dosth(id, left, right);
    ll mid = (left + right) / 2;
    update(id * 2, left, mid, x, y, w);
    update(id * 2 + 1, mid + 1, right, x, y, w);
}
ll get(ll id, ll left, ll right, ll x)
{
    if (x > right || x < left)
        return base;
    if (left == right)
        return st[id];
    dosth(id, left, right);
    ll mid = (left + right) / 2;
    return min(get(id * 2, left, mid, x), get(id * 2 + 1, mid + 1, right, x));
}
ll cntnw = 0;
ll nchain = 1;
ll chainhead[maxn];
ll chainid[maxn];
ll id[maxn];
vector<pll> adj[maxn];
ll par1[maxn];
ll siz[maxn];
void hld(ll u, ll par)
{
    if (!chainhead[nchain])
        chainhead[nchain] = u;
    cntnw++;
    chainid[u] = nchain;
    id[u] = cntnw;
    ll nxt = -1;
    for (auto p : adj[u])
    {
        ll to = p.ff;
        if (to == par)
            continue;
        if (nxt == -1 || siz[nxt] < siz[to])
        {
            nxt = to;
        }
    }
    if (nxt != -1)
    {
        hld(nxt, u);
    }
    for (auto p : adj[u])
    {
        ll to = p.ff;
        if (to == par || to == nxt)
            continue;
        nchain++;
        hld(to, u);
    }
}
void update1(ll u, ll a, ll w)
{
    ll p = chainid[u];
    ll chk = chainid[a];
    while (1)
    {
        if (p == chk)
        {
            update(1, 1, cntnw, id[a], id[u], w);
            break;
        }
        update(1, 1, cntnw, id[chainhead[p]], id[u], w);
        u = par1[chainhead[p]];
        p = chainid[u];
    }
}