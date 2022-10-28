
// Returns minimum x for which a ^ x % m = b % m.
// Returns -1 if x isn't exist

using ll = int;
ll solve(ll a, ll b, ll m)
{
    a %= m, b %= m;
    ll k = 1, add = 0, g;
    while ((g = __gcd(a, m)) > 1)
    {
        if (b == k)
            return add;
        if (b % g)
            return -1;
        b /= g, m /= g, ++add;
        k = (k * 1ll * a / g) % m;
    }

    ll n = sqrt((ld)m) + 1;
    ll an = 1;
    for (ll i = 0; i < n; ++i)
        an = (an * 1ll * a) % m;

    unordered_map<ll, ll> vals;
    for (ll q = 0, cur = b; q <= n; ++q)
    {
        vals[cur] = q;
        cur = (cur * 1ll * a) % m;
    }

    for (ll p = 1, cur = k; p <= n; ++p)
    {
        cur = (cur * 1ll * an) % m;
        if (vals.count(cur))
        {
            ll ans = n * p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}