// string and array pos start from 0
// but array sa and lcp start from 1

constexpr int N = 3e5 + 5; // change size to size of string;
 
struct SuffixArray
{
    string s;
    int n, c[N], p[N], rp[N], lcp[N];
 
    //p[] : suffix array
    // lcp[]: lcp array

    void Assign(const string &x)
    {
        s = x;
        s.push_back('$'); // Change character here due to range of charater in string
        n = s.size();
        Build();
        s.pop_back();
        n = s.size();
    }
 
    void Build()
    {
        vector<int> pn(N), cn(N), cnt(N);
 
        for (int i = 0; i < n; ++i)
            ++cnt[s[i]];
        for (int i = 1; i <= 256; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i)
            p[--cnt[s[i]]] = i;
 
        for (int i = 1; i < n; ++i)
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
 
        int maxn = c[p[n - 1]];
 
        for (int i = 0; (1 << i) < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                p[j] = ((p[j] - (1 << i)) % n + n) % n;
            for (int j = 0; j <= maxn; ++j)
                cnt[j] = 0;
 
            for (int j = 0; j < n; ++j)
                ++cnt[c[p[j]]];
 
            for (int j = 1; j <= maxn; ++j)
                cnt[j] += cnt[j - 1];
 
            for (int j = n - 1; ~j; --j)
                pn[--cnt[c[p[j]]]] = p[j];
 
            for (int j = 1; j < n; ++j)
                cn[pn[j]] = cn[pn[j - 1]] + (c[pn[j]] != c[pn[j - 1]] || c[(pn[j] + (1 << i)) % n] != c[(pn[j - 1] + (1 << i)) % n]);
 
            maxn = cn[pn[n - 1]];
 
            for (int j = 0; j < n; ++j)
            {
                p[j] = pn[j];
                c[j] = cn[j];
            }
        }
    }
 
    void BuildLCP()
    {
        for (int i = 1; i <= n; ++i)
            rp[p[i]] = i;
        for (int i = 0; i < n; ++i)
        {
            if (i)
                lcp[i] = max(lcp[i - 1] - 1, 0);
            if (rp[i] == n)
                continue;
 
            while (lcp[i] < n - i && lcp[i] < n - p[rp[i] + 1] && s[i + lcp[i]] == s[p[rp[i] + 1] + lcp[i]])
                ++lcp[i];
        }
    }
} g;