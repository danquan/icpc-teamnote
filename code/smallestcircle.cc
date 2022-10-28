#include <bits/stdc++.h>
using namespace std;
using ld = double;

typedef pair<ld, ld> point;
typedef pair<point, ld> circle;
#define X first
#define Y second

// O(n)
// Remember to change size of set points
// All point must be save in array a[] below

namespace emowelzl
{
    const int N = 100005; // Size of set points
    int n;
    point a[N];

    point operator+(point a, point b)
    {
        return point(a.X + b.X, a.Y + b.Y);
    }
    point operator-(point a, point b) { return point(a.X - b.X, a.Y - b.Y); }
    point operator/(point a, ld x) { return point(a.X / x, a.Y / x); }
    ld abs(point a) { return sqrt(a.X * a.X + a.Y * a.Y); }

    point center_from(ld bx, ld by, ld cx, ld cy)
    {
        ld B = bx * bx + by * by, C = cx * cx + cy * cy, D = bx * cy - by * cx;
        return point((cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D));
    }

    circle circle_from(point A, point B, point C)
    {
        point I = center_from(B.X - A.X, B.Y - A.Y, C.X - A.X, C.Y - A.Y);
        return circle(I + A, abs(I));
    }

    circle f(int n, vector<point> T)
    {
        if (T.size() == 3 || n == 0)
        {
            if (T.size() == 0)
                return circle(point(0, 0), -1);
            if (T.size() == 1)
                return circle(T[0], 0);
            if (T.size() == 2)
                return circle((T[0] + T[1]) / 2, abs(T[0] - T[1]) / 2);
            return circle_from(T[0], T[1], T[2]);
        }
        random_shuffle(a + 1, a + n + 1);
        circle Result = f(0, T);
        for (int i = 1; i <= n; i++)
            if (abs(Result.X - a[i]) > Result.Y + 1e-9)
            {
                T.push_back(a[i]);
                Result = f(i - 1, T);
                T.pop_back();
            }
        return Result;
    }
};

int main()
{
    cin >> emowelzl::n;

    for (int i = 1; i <= emowelzl::n; ++i)
        cin >> emowelzl::a[i].X >> emowelzl::a[i].Y;

    cout << emowelzl::f(emowelzl::n, {}).Y * 2;
}