// To initialize, call init_count_primes() first.
// Function count_primes(n) will compute the number of
// prime numbers lower than or equal to n.
//
// Time complexity: Around O(n ^ 0.75)

constexpr int N = 1e5 + 5; // keep N larger than max(sqrt(n) + 2)
bool prime[N];
int prec[N];
vector<int> P;

ll rec(ll n, int k)
{
    if (n <= 1 || k < 0)
        return 0;
    if (n <= P[k])
        return n - 1;

    if (n < N && ll(P[k]) * P[k] > n)
        return n - 1 - prec[n] + prec[P[k]];

    const int LIM = 250;
    static int memo[LIM * LIM][LIM];
    bool ok = n < LIM * LIM;
    if (ok && memo[n][k])
        return memo[n][k];

    ll ret = n / P[k] - rec(n / P[k], k - 1) + rec(n, k - 1);

    if (ok)
        memo[n][k] = ret;
    return ret;
}
void init_count_primes()
{
    prime[2] = true;
    for (int i = 3; i < N; i += 2)
        prime[i] = true;
    for (int i = 3, j; i * i < N; i += 2)
        if (prime[i])
            for (j = i * i; j < N; j += i + i)
                prime[j] = false;

    for (int i = 1; i < N; ++i)
        if (prime[i])
            P.push_back(i);

    for (int i = 1; i < N; ++i)
        prec[i] = prec[i - 1] + prime[i];
}

ll count_primes(ll n)
{
    if (n < N)
        return prec[n];
    int k = prec[(int)sqrt(n) + 1];
    return n - 1 - rec(n, k) + prec[P[k]];
}
