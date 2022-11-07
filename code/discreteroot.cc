/*
Given a prime n and two integers a and k, find all x for which:\
    - x ^ k = a (mod n)

Notice:
    - In case k = 2, let's use Tonelli - Shanks
    - You must insert my implementation of Discrete Logarithm and Primitive Root to run algorithm
*/

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

ll DiscreteRoot(ll a, ll k, ll n)
{
    ll g = PrimitiveRoot(n);
    ll v = Pow(g, k, n);
    ll ans = DiscreteLogarithm(v, a, n);

    if (ans == -1)
        return -1; // Can't find

    return Pow(g, ans, n);
}