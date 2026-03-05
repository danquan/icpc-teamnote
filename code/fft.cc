using cd = complex<double>;
const double PI = acos(-1);
// invert == true means Interpolation
// invert == false means dft
void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
            j ^= bit;
            if (i < j)
            swap(a[i], a[j]);
        }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j],
                v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd &x : a)
        x /= n;
    }
}

vector<long long> multiply(vector<long long>& A, vector<long long>& B) {
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());

    int n1 = (int)A.size(), n2 = (int)B.size();
    int n = 1;
    while (n < n1 + n2 - 1) n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> res(n1 + n2 - 1);
    for (int i = 0; i < (int)res.size(); i++) {
        res[i] = (long long) llround(fa[i].real()); // round to nearest integer
    }
    return res;
}