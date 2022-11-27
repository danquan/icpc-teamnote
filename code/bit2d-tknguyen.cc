struct BIT_2D
{
    vector<ll> vt;
    vector<vector<ll>> f;
    vector<vector<ll>> node;
    void init(vector<ll> vt1)
    {
        vt = vt1;
        sort(vt.begin(), vt.end());
        vt.resize(unique(vt.begin(), vt.end()) - vt.begin());
        f = vector<vector<ll>>(vt.size() + 2, vector<ll>(0));
        node = vector<vector<ll>>(vt.size() + 2, vector<ll>(0));
    }
    void rearrange()
    {
        for (int i = 1; i <= vt.size(); i++)
        {
            sort(node[i].begin(), node[i].end());
            node[i].resize(unique(node[i].begin(), node[i].end()) - node[i].begin());
            f[i] = vector<ll>(node[i].size() + 2, 0);
        }
    }
    void fake_update(ll x, ll y)
    {
        for (int i = lower_bound(vt.begin(), vt.end(), x) - vt.begin() + 1; i <= vt.size(); i += i & (-i))
        {
            node[i].pb(y);
        }
    }
    void fake_get(ll x, ll y)
    {
        for (int i = lower_bound(vt.begin(), vt.end(), x) - vt.begin() + 1; i; i -= i & (-i))
        {
            node[i].pb(y);
        }
    }
    void update(ll x, ll y, ll val)
    {
        for (int i = lower_bound(vt.begin(), vt.end(), x) - vt.begin() + 1; i <= vt.size(); i += i & (-i))
        {
            for (int j = lower_bound(node[i].begin(), node[i].end(), y) - node[i].begin() + 1; j <= node[i].size(); j += j & (-j))
            {
                f[i][j] = f[i][j] + val;
            }
        }
    }
    ll get(ll x, ll y)
    {
        ll ans = 0;
        for (int i = lower_bound(vt.begin(), vt.end(), x) - vt.begin() + 1; i; i -= i & (-i))
        {
            for (int j = lower_bound(node[i].begin(), node[i].end(), y) - node[i].begin() + 1; j; j -= j & (-j))
            {
                ans += f[i][j];
            }
        }
        return ans;
    }
};