/*
g is a primitive root modulo n if and only if for any integer a such that gcd(a, n) = 1, there exists an integer k such that:
g^k = a (mod n).

Primitive root modulo n exists if and only if:
    - n is 1, 2, 4
    - n is power of an odd prime number (n = p ^ k)
    - n is twice power of an odd prime number (n = 2 * p ^ k)

This theorem was proved by Gauss in 1801.
*/

using ll = int; // Change type of data here

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

ll GetPhi(ll n)
{
    ll ans(1);

    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                n /= i;
                ans *= i;
            }

            ans = ans / i * (i - 1);
        }

    if (n != 1)
        ans *= n - 1;

    return ans;
}

ll PrimitiveRoot(ll p)
{
    vector<ll> fact;
    ll phi = GetPhi(p);
    ll n = phi;

    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }

    if (n > 1)
        fact.push_back(n);

    for (ll res = 2; res <= p; ++res)
    {
        bool ok = true;

        for (int i = 0; i < fact.size() && ok; ++i)
            ok &= Pow(res, phi / fact[i], p) != 1;

        if (ok)
            return res;
    }

    return -1; // can't find
}