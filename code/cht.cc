// If you want to get maximum, sort coef (A) not decreasing and change B[line.back()] > B[i] into B[line.back()] < B[i] 

struct ConvexHullTrick
{
    vector<ll> A, B;
    vector<int> line;
    vector<ld> point;
    ConvexHullTrick(int n = 0)
    {
        A.resize(n + 2, 0);
        B.resize(n + 2, 0);
        point.emplace_back(-Inf);
    }
 
    ld ff(int x, int y)
    {
        return (ld)1.0 * (B[y] - B[x]) / (A[x] - A[y]);
    }
 
    void Add(int i)
    {
        while ((int)line.size() > 1 || ((int)line.size() == 1 && A[line.back()] == A[i]))
        {
            if (A[line.back()] == A[i])
            {
                if (B[line.back()] > B[i])
                {
                    line.pop_back();
                    if (!line.empty())
                        point.pop_back();
                }
                else
                    break;
            }
            else
            {
                if (ff(i, line.back()) <= ff(i, line[line.size() - 2]))
                {
                    line.pop_back();
                    if (!line.empty())
                        point.pop_back();
                }
                else
                    break;
            }
        }
 
        if (line.empty() || A[line.back()] != A[i])
        {
            if (!line.empty())
                point.emplace_back(ff(line.back(), i));
            line.emplace_back(i);
        }
    } 
    ll Get(int x)
    {
        int j = lower_bound(point.begin(), point.end(), x) - point.begin();
        return A[line[j - 1]] * x + B[line[j - 1]];
    }
};

