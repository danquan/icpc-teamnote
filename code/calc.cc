// Calculate n/1 + n/2 + ... + n/n

#define Cal(a, b) ((b) - (a) + 1)

ll calc(ll n)
{
    ll ans = 0;

    for (ll i = 1; i <= n / i; ++i)
        ans += Cal(n / (i + 1) + 1, n / i) * i;

    for (ll i = 1; i < n / i; ++i)
        ans += n / i;

    return ans;
}