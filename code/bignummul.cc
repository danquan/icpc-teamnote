// Replace function *= in Bignum implementation with below code:
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
    {
        for (cd &x : a)
            x /= n;
    }
}
Bignum &operator*=(const Bignum &x)
{
    int m = 1;
    while (m < n + x.n)
        m <<= 1;
    vector<cd> fa(m), fb(m);
    for (int i = 0; i < m; ++i)
    {
        fa[i] = a[i];
        fb[i] = x.a[i];
    }
    fft(fa, false); /// dft
    fft(fb, false); /// dft
    for (int i = 0; i < m; i++)
        fa[i] *= fb[i];
    fft(fa, true); /// Interpolation
    n = m;
    for (int i = 0; i < n; ++i)
        a[i] = round(fa[i].real());
    fix();
    return *this;
}