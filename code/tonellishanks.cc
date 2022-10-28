using ll = int;

ll pow_mod(ll x, ll n, ll p)
{
    if (n == 0)
        return 1;
    if (n & 1)
        return (pow_mod(x, n - 1, p) * x) % p;
    x = pow_mod(x, n / 2, p);
    return (x * x) % p;
}

/*
Takes as input an odd prime p and n < p and returns r such that r * r = n [mod p].
There's exist r if and only if n ^ [(p-1) / 2] = 1 (mod p)
*/

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
        ll r = pow_mod(n, (p + 1) / 4, p);
        if ((r * r) % p == n)
            return r;
        return 0;
    }
    // Find the first quadratic non-residue z by brute-force search
    ll z = 1;
    while (pow_mod(++z, (p - 1) / 2, p) != p - 1)
        ;
    ll c = pow_mod(z, q, p);
    ll r = pow_mod(n, (q + 1) / 2, p);
    ll t = pow_mod(n, q, p);
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
        ll b = pow_mod(c, pow_mod(2, m - i - 1, p - 1), p);
        ll b2 = (b * b) % p;
        r = (r * b) % p;
        t = (t * b2) % p;
        c = b2;
        m = i;
    }
    if ((r * r) % p == n)
        return r;
    return 0;
}