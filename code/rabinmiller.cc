// There is another version of Rabin Miller using random in the implementation of Pollard Rho

ll mul(ll a, ll b, ll mod)
{
    a %= mod;
    b %= mod;
    ll q = (ld)a * b / mod;
    ll r = a * b - q * mod;
    return (r % mod + mod) % mod;
}
ll pow(ll a, ll n, ll m)
{
    ll result = 1;
    a %= m;
    while (n > 0)
    {
        if (n & 1)
            result = mul(result, a, m);
        n >>= 1;
        a = mul(a, a, m);
    }
    return result;
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
bool test(ll s, ll d, ll n, ll witness)
{
    if (n == witness)
        return true;
    ll p = pow(witness, d, n);
    if (p == 1)
        return true;
    for (; s > 0; s--)
    {
        if (p == n - 1)
            return true;
        p = mul(p, p, n);
    }
    return false;
}
bool miller(ll n)
{
    if (n < 2)
        return false;
    if ((n & 1) == 0)
        return n == 2;
    ll s, d;
    tie(s, d) = factor(n - 1);
    return test(s, d, n, 2) && test(s, d, n, 3) && test(s, d, n, 5) &&
           test(s, d, n, 7) && test(s, d, n, 11) && test(s, d, n, 13) &&
           test(s, d, n, 17) && test(s, d, n, 19) && test(s, d, n, 23);
}