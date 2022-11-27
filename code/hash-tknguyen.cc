struct Hashing
{
    vector<vector<vector<ll>>> f;
    vector<ll> mod;
    vector<vector<ll>> mu;
    vector<ll> chr;
    ll num;
    ll base;
    void init()
    {
        num = 2;
        f.clear();
        mod.clear();
        mu.clear();
        chr.clear();
        vector<ll> vt = {999244369, 999254351, 999154309, 989154311, 989254411, 997254397, 991294387, 991814399, 994114351, 994914359, 994024333};
        random_shuffle(vt.begin(), vt.end());
        base = 317;
        for (int i = 1; i <= 26; i++)
            chr.pb(abs((ll)(rnd())));
        for (int i = 0; i < num; i++)
        {
            f.emplace_back();
            mod.pb(vt[i]);
            vector<ll> pt;
            pt.pb(1);
            for (int j = 1; j < maxn; j++)
            {
                pt.pb((pt.back() * base) % mod[i]);
            }
            mu.pb(pt);
        }
    }
    ll add(string s)
    {
        ll n = s.length();
        ll id = f[0].size();
        for (int j = 0; j < num; j++)
        {
            vector<ll> vt1;
            vt1.pb(0);
            for (int i = 1; i <= n; i++)
            {
                vt1.pb((vt1.back() * base + chr[s[i - 1] - 'a']) % mod[j]);
            }
            f[j].pb(vt1);
        }
        return id;
    }
    pll get_hash(ll id, ll l, ll r)
    {
        return make_pair(((f[0][id][r] - f[0][id][l - 1] * mu[0][r - l + 1]) % mod[0] + mod[0]) % mod[0], ((f[1][id][r] - f[1][id][l - 1] * mu[1][r - l + 1]) % mod[1] + mod[1]) % mod[1]);
    }
};