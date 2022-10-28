using ll = long long;
using ld = long double;
namespace CRT
{
    // b must contain distinct element
    // x % b_i = a_i
    // x % m == (a1 * m2 * m3 * ... * m_k) * [(m2 * m3 * ... * mk) ^ -1 mod m_1] + (a2 * m1 * m3 * ... * m_k) / [(m1 * m3 * ... * mk) ^ -1 mod m2] + ...
    // Call CRT(a, b, phi) [Default phi is empty]
    // return {r, m} that x % m == r

    // In case of overflow, use this function
    ll Mul(ll a, ll b, const ll &mod)
    {
        ll q = (ld)a * b / mod;
        ll r = a * b - q * mod;

        return (r % mod + mod) % mod;
    }

    ll Pow(ll a, ll b, const ll &mod)
    {
        ll ans(1);
        for (; b; b >>= 1)
        {
            if (b & 1)
                ans = Mul(ans, a, mod);
            a = Mul(a, a, mod);
        }

        return ans;
    }

    ll calPhi(ll n)
    {
        ll ans = 1;

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

    pair<ll, ll> solve(const vector<ll> &a, const vector<ll> &b, vector<ll> phi = {})
    {
        assert(a.size() == b.size()); // Assume a and b have the same size
        ll m = 1;

        {
            m = 1;
            for (auto i : b)
                m *= i;
        }

        if (phi.empty())
        {
            for (auto i : b)
                phi.emplace_back(calPhi(i));
        }

        ll r = 0;

        for (int i = 0; i < (int)b.size(); ++i)
            r = (r + Mul(Mul(a[i], m / b[i], m), Pow(m / b[i], phi[i] - 1, m), m)) % m;

        return make_pair(r, m);
    }
};
