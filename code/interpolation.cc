// You can change mod into other prime number
// update k to the degree of polynomial
// Just work when we know a[1] = P(1), a[2] = P(2),..., a[k] = P(k) [The degree of P(x) is k-1]
// update() then build() then cal()

/*
 * Complexity: O(Nlog(mod), N)
 */

constexpr ll mod = 1e9 + 7; // Change mod here
constexpr ll N = 1e5 + 5;   // Change size here

struct Interpolation
{
    ll a[N], fac[N], ifac[N], prf[N], suf[N];
    int k;

    ll Pow(ll a, ll b)
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

    void upd(int u, ll v)
    {
        a[u] = v;
    }

    void build()
    {
        fac[0] = ifac[0] = 1;
        for (int i = 1; i < N; i++)
        {
            fac[i] = (long long)fac[i - 1] * i % mod;
            ifac[i] = Pow(fac[i], mod - 2);
        }
    }

    // Calculate P(x)
    ll calc(int x)
    {
        prf[0] = suf[k + 1] = 1;

        for (int i = 1; i <= k; i++)
            prf[i] = prf[i - 1] * (x - i + mod) % mod;

        for (int i = k; i >= 1; i--)
            suf[i] = suf[i + 1] * (x - i + mod) % mod;

        ll res = 0;

        for (int i = 1; i <= k; i++)
        {
            if (!((k - i) & 1))
                res = (res + prf[i - 1] * suf[i + 1] % mod * ifac[i - 1] % mod * ifac[k - i] % mod * a[i]) % mod;
            else
                res = (res - prf[i - 1] * suf[i + 1] % mod * ifac[i - 1] % mod * ifac[k - i] % mod * a[i] % mod + mod) % mod;
        }

        return res;
    }
};
