// Find pair of points that have closest distance

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

using ll = long long;
using ld = long double;

const int N = 5e4 + 2;
const ll Inf = 1e17;
#define sq(x) ((x) * (x))

struct Point
{
    ll x, y;
    int id;

    Point(const ll &x = 0, const ll &y = 0) : x(x), y(y) {}

    Point operator-(const Point &a) const
    {
        return Point(x - a.x, y - a.y);
    }
    ll len()
    {
        return x * x + y * y;
    }
};

namespace ClosestPoint
{
    int n, xa, ya;
    ll ans;
    Point a[N];

    ll Bruteforce(int l, int r)
    {
        for (; l < r; ++l)
            for (int i = l + 1; i <= r; ++i)
                if (ans > (a[l] - a[i]).len())
                {
                    ans = (a[l] - a[i]).len();
                    xa = a[l].id;
                    ya = a[i].id;
                }
        return ans;
    }

    void Brute(vector<int> &s)
    {
        sort(s.begin(), s.end(), [&](const int &x, const int &y)
             { return a[x].y < a[y].y; });
        for (int i = 0; i < s.size(); ++i)
            for (int j = i + 1; j < s.size() && sq(abs(a[s[i]].y - a[s[j]].y)) <= ans; ++j)
                if (ans > (a[s[i]] - a[s[j]]).len())
                {
                    ans = (a[s[i]] - a[s[j]]).len();
                    xa = a[s[i]].id;
                    ya = a[s[j]].id;
                }
    }

    void DAC(int l, int r)
    {
        if (r - l <= 3)
        {
            Bruteforce(l, r);
            return;
        }
        int mid = (l + r) / 2;

        DAC(l, mid);
        DAC(mid + 1, r);

        vector<int> s;
        for (int i = l; i <= r; ++i)
            if (sq(a[i].x - a[mid].x) <= ans)
                s.push_back(i);

        Brute(s);
    }

    void calc()
    {
        sort(a + 1, a + n + 1, [&](const Point &a, const Point &b)
             { return a.x < b.x || (a.x == b.x && a.y < b.y); });
        ans = Inf;

        DAC(1, n);

        if (xa > ya)
            swap(xa, ya);

        cout << xa << " " << ya << "\n";
        cout << fixed << setprecision(6) << sqrt((ld)ans);
    }
};

Point a[N];
int n;

void Read()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
    }
}

void Solve()
{
    ClosestPoint::n = n;
    for (int i = 1; i <= n; ++i)
        ClosestPoint::a[i] = a[i];

    ClosestPoint::calc();
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    Read();
    Solve();
}