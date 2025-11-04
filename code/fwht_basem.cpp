// m | MOD - 1 is required
int primitive_mth_root(int m, int mod) {
    int g = PrimitiveRoot(mod);
    return Pow(g, (mod - 1) / m, mod);
}

void fwht_m(vector<ll>& a, int m, int omega, bool inverse) {
    const int SZ = (int)a.size();
    ll w = inverse ? Pow(omega, m-1, mod) : omega;

    vector<ll> wp(m, 1);
    for (int t = 1; t < m; ++t) wp[t] = wp[t-1] * w % mod;

    vector<ll> Mmt(m * m);
    for (int k = 0; k < m; ++k)
        for (int t = 0; t < m; ++t)
            Mmt[k * m + t] = wp[(k * t) % m];

    int stages = 0;
    for (int len=1; len<SZ; len *= m) {
        ++stages;
        for (int base = 0; base < SZ; base += m * len){
            for (int j = 0; j < len; ++j){
                static vector<ll> x, y;
                x.assign(m, 0); y.assign(m, 0);
                for (int t=0; t<m; ++t) x[t] = a[base + j + t * len];

                for (int k = 0; k < m; ++k){
                    ll s = 0;
                    const ll* row = &Mmt[k*m];
                    for(int t = 0; t < m; ++t) {
                        s += x[t] * row[t];
                        s %= mod;
                    }
                    y[k] = s;
                }
                for (int k = 0; k < m; ++k) a[base + j + k * len] = y[k];
            }
        }
    }

    if(inverse){
        ll invm = mod_inv(m); ll scale = 1;
        for (int s = 0; s < stages; ++s) scale = scale * invm % mod;
        for (ll &v : a) v = v * scale % mod;
    }
}
