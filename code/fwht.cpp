void FST(vector<int> &a, bool inv) {
    for (int n = (int) a.size(), step = 1; step < n; step *= 2)
        for (int i = 0; i < n; i += 2 * step)
            for (int j = 0; j < step; ++j) {
                int u = a[i + j];
                int v = a[i + j + step];

                // tie(a[i + j], a[i + j + step]) = (inv ? make_pair(v, u - v) : make_pair(u + v, v)); // AND
                // tie(a[i + j], a[i + j + step]) = (inv ? make_pair(u - v, v) : make_pair(u, u + v)); // OR
                tie(a[i + j], a[i + j + step]) = make_pair(u + v, u - v); // XOR
            }
    
    if (inv) {
        for (int &x : a) x /= (int) a.size(); // XOR only
    }
}

vector<int> conv(vector<int> &a, vector<int> &b) {
    int n = 1, need = (int)a.size() + (int)b.size() - 1;
    while (n < need) n <<= 1;
    a.resize(n, 0); b.resize(n, 0);

    FST(a, 0); FST(b, 0);
    for (int i = 0; i < (int) a.size(); ++i) a[i] *= b[i];
    FST(a, 1);

    return a;
}
