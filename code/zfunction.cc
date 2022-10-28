// string start from 1
// f[i] = longest prefix match with s[i...i + f[i] - 1]

constexpr int N = 2e5 + 5;

void Build(string &s, int n, int f[N]) // n = size of string, f = z array
{
    int l(1), r(1);

    f[1] = n;

    for (int i = 2; i <= n; ++i)
        if (r < i)
        {
            l = r = i;
            while (r <= n && s[r - i + 1] == s[r])
                ++r;
            f[i] = r - i;
            --r;
        }
        else if (f[i - l + 1] < r - i + 1)
            f[i] = f[i - l + 1];
        else
        {
            l = i;
            while (r <= n && s[r - i + 1] == s[r])
                ++r;
            f[i] = r - i;
            --r;
        }
}
