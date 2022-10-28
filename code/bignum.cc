/// M is the number of digits in the answer
/// In case that we don't use multiplication, let BASE be 1e17 or 1e18
/// a = Bignum("5")
/// The operator / is only for integer, the result is integer too

using cd = complex<long double>;
const long double PI = acos(-1);
const int M = 2000;
const ll BASE = 1e8;
const int gd = log10(BASE);
const int maxn = M / gd + 1;
struct Bignum
{
    int n;
    ll a[maxn];
    Bignum(ll x = 0)
    {
        memset(a, 0, sizeof a);
        n = 0;
        do
        {
            a[n++] = x % BASE;
            x /= BASE;
        } while (x);
    }
    Bignum(const string &s)
    {
        Convert(s);
    }
    ll stoll(const string &s)
    {
        ll ans(0);
        for (auto i : s)
            ans = ans * 10 + i - '0';
        return ans;
    }
    void Convert(const string &s)
    {
        memset(a, 0, sizeof a);
        n = 0;
        for (int i = s.size() - 1; ~i; --i)
        {
            int j = max(0, i - gd + 1);
            a[n++] = stoll(s.substr(j, i - j + 1));
            i = j;
        }
        fix();
    }
    void fix()
    {
        ++n;
        for (int i = 0; i < n - 1; ++i)
        {
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
            if (a[i] < 0)
            {
                a[i] += BASE;
                --a[i + 1];
            }
        }
        while (n > 1 && a[n - 1] == 0)
            --n;
    }
    Bignum &operator+=(const Bignum &x)
    {
        n = max(n, x.n);
        for (int i = 0; i < n; ++i)
            a[i] += x.a[i];
        fix();
        return *this;
    }
    Bignum &operator-=(const Bignum &x)
    {
        for (int i = 0; i < x.n; ++i)
            a[i] -= x.a[i];
        fix();
        return *this;
    }
    Bignum &operator*=(const Bignum &x)
    {
        vector<ll> c(x.n + n, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < x.n; ++j)
                c[i + j] += a[i] * x.a[j];
        n += x.n;
        for (int i = 0; i < n; ++i)
            a[i] = c[i];
        fix();
        return *this;
    }
    Bignum &operator/=(const ll &x)
    {
        ll r = 0ll;
        for (int i = n - 1; i > -1; --i)
        {
            r = r * BASE + a[i];
            a[i] = r / x;
            r %= x;
        }
        fix();
        return *this;
    }
    Bignum operator+(const Bignum &s)
    {
        Bignum c;
        copy(a, a + n, c.a);
        c.n = n;
        c += s;
        return c;
    }
    Bignum operator-(const Bignum &s)
    {
        Bignum c;
        copy(a, a + n, c.a);
        c.n = n;
        c -= s;
        return c;
    }
    Bignum operator*(const Bignum &s)
    {
        Bignum c;
        copy(a, a + n, c.a);
        c.n = n;
        c *= s;
        return c;
    }
    Bignum operator/(const ll &x)
    {
        Bignum c;
        copy(a, a + n, c.a);
        c.n = n;
        c /= x;
        return c;
    }
    ll operator%(const ll &x)
    {
        ll ans(0);
        for (int i = n - 1; ~i; --i)
            ans = (ans * BASE + a[i]) % x;
        return ans;
    }
    int com(const Bignum &s) const
    {
        if (n < s.n)
            return 1;
        if (n > s.n)
            return 2;
        for (int i = n - 1; i > -1; --i)
            if (a[i] > s.a[i])
                return 2;
            else if (a[i] < s.a[i])
                return 1;
        return 3;
    }
    bool operator<(const Bignum &s) const
    {
        return com(s) == 1;
    }
    bool operator>(const Bignum &s) const
    {
        return com(s) == 2;
    }
    bool operator==(const Bignum &s) const
    {
        return com(s) == 3;
    }
    bool operator<=(const Bignum &s) const
    {
        return com(s) != 2;
    }
    bool operator>=(const Bignum &s) const
    {
        return com(s) != 1;
    }
    void read()
    {
        string s;
        cin >> s;
        Convert(s);
    }
    void print()
    {
        int i = n;
        while (i > 0 && a[i] == 0)
            --i;
        cout << a[i];
        for (--i; ~i; --i)
            cout << setw(gd) << setfill('0')
                 << a[i];
    }
};
