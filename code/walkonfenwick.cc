// This is equivalent to calculating lower_bound on prefix sums array
// LOGN = log2(N)

struct FenwickTree
{
    int n, LOGN;
    ll a[N]; // BIT array

    FenwickTree()
    {
        memset(a, 0, sizeof a);
    }

    void Update(int p, ll v)
    {
        for (; p <= n; p += p & -p)
            a[p] += v;
    }

    ll Get(int p)
    {
        ll ans(0);

        for (; p; p -= p & -p)
            ans += a[p];

        return ans;
    }

    int search(ll v)
    {
        ll sum = 0;
        int pos = 0;
        for (int i = LOGN; i >= 0; i--)
        {
            if (pos + (1 << i) <= n && sum + a[pos + (1 << i)] < v)
            {
                sum += a[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
        //+1 because pos will be position of largest value less than v
    }
};