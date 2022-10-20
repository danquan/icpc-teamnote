// You can change code Rabin-Miller (preposition)
struct PollardRho
{
    ll n;
    map<ll, int> ans;
    PollardRho(ll n) : n(n) {}
    ll random(ll u)
    {
        return abs(rand()) % u;
    }
    ll mul(ll a, ll b, ll mod)
    {
        a %= mod;
        b %= mod;
        ll q = (ld)a * b / mod;
        ll r = a * b - q * mod;
        return (r % mod + mod) % mod;
    }

    ll pow(ll a, ll b, ll m)
    {
        ll ans = 1;
        a %= m;
        for (; b; b >>= 1)
        {
            if (b & 1)
                ans = mul(ans, a, m);
            a = mul(a, a, m);
        }
        return ans;
    }

    pair<ll, ll> factor(ll n)
    {
        ll s = 0;
        while ((n & 1) == 0)
        {
            s++;
            n >>= 1;
        }
        return {s, n};
    }
    // Rabin - Miller
    bool miller(ll n)
    {
        if (n < 2)
            return 0;
        if (n == 2)
            return 1;
        ll s = 0, m = n - 1;
        while (m % 2 == 0)
        {
            s++;
            m >>= 1;
        }
        // 1 - 0.9 ^ 40
        for (int it = 1; it <= 40; it++)
        {
            ll u = random(n - 2) + 2;
            ll f = pow(u, m, n);
            if (f == 1 || f == n - 1)
                continue;
            for (int i = 1; i < s; i++)
            {
                f = mul(f, f, n);
                if (f == 1)
                    return 0;
                if (f == n - 1)
                    break;
            }
            if (f != n - 1)
                return 0;
        }
        return 1;
    }

    ll f(ll x, ll n)
    {
        return (mul(x, x, n) + 1) % n;
    }
    // Find a factor
    ll findfactor(ll n)
    {
        ll x = random(n - 1) + 2;
        ll y = x;
        ll p = 1;
        while (p == 1)
        {
            x = f(x, n);
            y = f(f(y, n), n);
            p = __gcd(abs(x - y), n);
        }
        return p;
    }
    // prime factorization
    void pollard_rho(ll n)
    {
        if (n <= 1000000)
        {
            for (int i = 2; i * i <= n; i++)
            {
                while (n % i == 0)
                {
                    ans[i]++;
                    n /= i;
                }
            }
            if (n > 1)
                ans[n]++;
            return;
        }

        if (miller(n))
        {
            ans[n]++;
            return;
        }
        ll p = 0;

        while (p == 0 || p == n)
            p = findfactor(n);

        pollard_rho(n / p);
        pollard_rho(p);
    }
};
