constexpr int N = 1e5 + 5; // keep N double of n+m

// Call init() before call mul()

constexpr ll mod = 998244353;

ll Pow(ll a, ll b, ll mod)
{
    ll ans(1);
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}

namespace ntt
{
    const int N = ::N;
    const long long mod = ::mod, rt = 3;
    ll G[55], iG[55], itwo[55];
    void add(int &a, int b)
    {
        a += b;
        if (a >= mod)
            a -= mod;
    }
    void init()
    {
        int now = (mod - 1) / 2, len = 1, irt = Pow(rt, mod - 2, mod);
        while (now % 2 == 0)
        {
            G[len] = Pow(rt, now, mod);
            iG[len] = Pow(irt, now, mod);
            itwo[len] = Pow(1 << len, mod - 2, mod);
            now >>= 1;
            len++;
        }
    }
    void dft(ll *x, int n, int fg = 1) // fg=1 for dft, fg=-1 for inverse dft
    {
        for (int i = (n >> 1), j = 1, k; j < n; ++j)
        {
            if (i < j)
                swap(x[i], x[j]);
            for (k = (n >> 1); k & i; i ^= k, k >>= 1)
                ;
            i ^= k;
        }
        for (int m = 2, now = 1; m <= n; m <<= 1, now++)
        {
            ll r = fg > 0 ? G[now] : iG[now];
            for (int i = 0, j; i < n; i += m)
            {
                ll tr = 1, u, v;
                for (j = i; j < i + (m >> 1); ++j)
                {
                    u = x[j];
                    v = x[j + (m >> 1)] * tr % mod;
                    x[j] = (u + v) % mod;
                    x[j + (m >> 1)] = (u + mod - v) %
                                      mod;
                    tr = tr * r % mod;
                }
            }
        }
    }

    // Take two sequence a, b;
    // return answer in sequence a

    void mul(ll *a, ll *b, int n, int m)
    {
        // a: 0,1,2,...,n-1; b: 0,1,2,...,m-1

        int nn = n + m - 1;
        if (n == 0 || m == 0)
        {
            memset(a, 0, nn * sizeof(a[0]));
            return;
        }
        int L, len;
        for (L = 1, len = 0; L < nn; ++len, L <<= 1)
            ;
        if (n < L)
            memset(a + n, 0, (L - n) * sizeof(a[0]));
        if (m < L)
            memset(b + m, 0, (L - m) * sizeof(b[0]));
        dft(a, L, 1); // dft(a)
        dft(b, L, 1); // dft(b)
        // Merge
        for (int i = 0; i < L; ++i)
            a[i] = a[i] * b[i] % mod;
        // Interpolation
        dft(a, L, -1);
        for (int i = 0; i < L; ++i)
            a[i] = a[i] * itwo[len] % mod;
    }
};
