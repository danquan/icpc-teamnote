// NTT (FFT mod 998244353) + convolution
static const int MOD = 998244353;
static const int G   = 3;

long long modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// invert=false: forward NTT, invert=true: inverse NTT
void fft_mod(vector<int> &a, bool invert) {
    int n = (int)a.size();
    static vector<int> rev;
    static vector<int> roots{0, 1};

    // bit-reversal permutation
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++) {
            rev[i] = 0;
            for (int j = 0; j < k; j++)
                if (i & (1 << j)) rev[i] |= 1 << (k - 1 - j);
        }
    }

    // roots of unity
    if ((int)roots.size() < n) {
        int k = __builtin_ctz((int)roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            long long e = modpow(G, (MOD - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = (long long)roots[i] * e % MOD;
            }
            k++;
        }
    }

    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = a[i + j];
                int v = (long long)a[i + j + len] * roots[len + j] % MOD;
                int x = u + v;
                if (x >= MOD) x -= MOD;
                a[i + j] = x;
                x = u - v;
                if (x < 0) x += MOD;
                a[i + j + len] = x;
            }
        }
    }

    if (invert) {
        // inverse via reversing (valid for this root table construction)
        reverse(a.begin() + 1, a.end());
        long long inv_n = modpow(n, MOD - 2);
        for (int &x : a) x = (long long)x * inv_n % MOD;
    }
}

vector<long long> multiply(const vector<long long>& A, const vector<long long>& B) {
    if (A.empty() || B.empty()) return {};
    int n1 = (int)A.size(), n2 = (int)B.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;

    vector<int> fa(n, 0), fb(n, 0);
    for (int i = 0; i < n1; i++) fa[i] = (int)(A[i] % MOD);
    for (int i = 0; i < n2; i++) fb[i] = (int)(B[i] % MOD);

    fft_mod(fa, false);
    fft_mod(fb, false);
    for (int i = 0; i < n; i++) fa[i] = (long long)fa[i] * fb[i] % MOD;
    fft_mod(fa, true);

    vector<long long> res(n1 + n2 - 1);
    for (int i = 0; i < (int)res.size(); i++) res[i] = fa[i];
    return res;
}