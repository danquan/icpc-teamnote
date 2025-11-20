pair<ll, ll> exteuclid(ll a, ll b){
    if(b == 0) return {1, 0};
    pair<ll, ll> q = gcd(b, a % b);
    return {q.second, q.first - q.second * (a / b)};
}

/**
 * x % m1 == x1
 * x % m2 == x2
 * => x % lcm(m1, m2) == res
 */
ll solve(ll x1, ll m1, ll x2, ll m2) {
    ll g = __gcd(m1, m2);
    if((x2 - x1) % g) return -1;// no sol
    m1 /= g; m2 /= g;
    pair<ll,ll> p = exteuclid(m1, m2);
    ll lcm = m1 * m2 * g;
    ll res = p.first * (x2 - x1) * m1 + x1;
    return (res % lcm + lcm) % lcm;
}