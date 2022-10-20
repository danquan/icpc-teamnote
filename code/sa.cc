// string and array pos start from 0
// but array sa and lcp start from 1
constexpr char firstCharacter = 'a';
constexpr int ALPHABET_SIZE = 26;

struct SuffixArray
{
    string s;
    vector<int> sa, lcp, pos;
    int n;
#define ModSum(x, y) (((x + y) % n + n) % n)
    void Assign(const string &p)
    {
        s = p;
        s += char(firstCharacter - 1);
        n = s.size();
        sa.resize(n + 1);
        lcp.resize(n + 1);
        pos.resize(n + 1);
        vector<int> tmpsa(n + 1), in(n + 1),
            tmpin(n + 1), cnt(max(n, 256) + 1, 0);

        // ------ Counting Sort ------

        for (auto i : s)
            ++cnt[i - firstCharacter + 1];
        for (int i = 1; i <= ALPHABET_SIZE; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; ~i; --i)
            sa[--cnt[s[i] - firstCharacter + 1]] = i;

        // Break into bucket
        for (int i = 0; i < n; ++i)
            in[sa[i]] = i == 0 ? 0 : (in[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]));
        // ----- End Counting Sort ------

        for (int i = 0, maxn = in [sa[n - 1]]; (1 << i) <= n; ++i)
        {
            // Reset cnt[]
            for (int j = 0; j <= maxn; ++j)
                cnt[j] = 0;

            // ----- Counting Sort -----
            for (int j = 0; j < n; ++j)
                ++cnt[in[sa[j]]];
            for (int j = 1; j <= maxn; ++j)
                cnt[j] += cnt[j - 1];
            for (int j = n - 1; ~j; --j)
                tmpsa[--cnt[in[ModSum(sa[j], -(1 << i))]]] = ModSum(sa[j], -(1 << i));
            // break into bucket
            for (int j = 0; j < n; ++j)
            {
                sa[j] = tmpsa[j];
                tmpin[sa[j]] = j == 0 ? 0 : (tmpin[sa[j - 1]] + (make_pair(in[sa[j]], in[ModSum(sa[j], 1 << i)]) != make_pair(in[sa[j - 1]], in[ModSum(sa[j - 1], 1 << i)])));
            }
            // ----- End Counting Sort -----

            maxn = tmpin[sa[n - 1]];
            swap(in, tmpin);
        }
        s.pop_back();
        --n;
    }

    void LCP()
    {
        for (int i = 0; i < n; ++i)
            pos[sa[i + 1]] = i + 1;
        for (int i = 0, k = 0; i < n; ++i)
        {
            if (pos[i] == n)
            {
                lcp[pos[i]] = k = 0;
                continue;
            }
            while (k + i < n && sa[pos[i] + 1] + k < n &&
                   s[k + i] == s[sa[pos[i] + 1] + k])
                ++k;
            lcp[pos[i]] = k;
            k = max(k - 1, 0);
        }
    }
};