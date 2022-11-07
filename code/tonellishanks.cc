/*
Takes as input an odd prime p and n < p and returns r such that r * r = n [mod p].
There's exist r if and only if n ^ [(p-1) / 2] = 1 (mod p)
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

ll tonelli_shanks(ll n, ll p)
{
    ll s = 0;
    ll q = p - 1;
    while ((q & 1) == 0)
    {
        q /= 2;
        ++s;
    }
    if (s == 1)
    {
        ll r = Pow(n, (p + 1) / 4, p);
        if ((r * r) % p == n)
            return r;
        return 0;
    }
    // Find the first quadratic non-residue z by brute-force search
    ll z = 1;
    while (Pow(++z, (p - 1) / 2, p) != p - 1)
        ;
    ll c = Pow(z, q, p);
    ll r = Pow(n, (q + 1) / 2, p);
    ll t = Pow(n, q, p);
    ll m = s;
    while (t != 1)
    {
        ll tt = t;
        ll i = 0;
        while (tt != 1)
        {
            tt = (tt * tt) % p;
            ++i;
            if (i == m)
                return 0;
        }
        ll b = Pow(c, Pow(2, m - i - 1, p - 1), p);
        ll b2 = (b * b) % p;
        r = (r * b) % p;
        t = (t * b2) % p;
        c = b2;
        m = i;
    }
    if ((r * r) % p == n)
        return r;
    return -1; // Can't find
}