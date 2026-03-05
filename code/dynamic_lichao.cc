struct Line {
    ll a, b;

    Line() {
        a = 0; b = 1e18;
    }

    Line(ll _a, ll _b) {
        a = _a; b = _b;
    }

    ll calc(ll x) {
        return a * x + b;
    }
};

struct Node {
    Line line;
    int lc, rc;
    Node() : lc(-1), rc(-1) {}
};

struct DynamicLichao {
    vector<Node> tr;
    int root;

    DynamicLichao() {
        root = -1;
    }

    int addLine(Line f, int k, ll l, ll r) {
        if (k == -1) {
            int new_idx = tr.size();
            tr.push_back(Node());
            tr[new_idx].line = f;
            return new_idx;
        }

        ll mid = l + (r - l) / 2;
        bool left_better = f.calc(l) < tr[k].line.calc(l);
        bool mid_better = f.calc(mid) < tr[k].line.calc(mid);

        if (mid_better) {
            swap(tr[k].line, f);
        }

        if (l == r) return k;

        if (left_better != mid_better) {
            int nxt = addLine(f, tr[k].lc, l, mid);
            tr[k].lc = nxt;
        } else {
            int nxt = addLine(f, tr[k].rc, mid + 1, r);
            tr[k].rc = nxt;
        }
        return k;
    }

    int update(ll a, ll b, Line f, int k, ll l, ll r) {
        if (b < l || r < a) return k;

        if (k == -1) {
            int new_idx = tr.size();
            tr.push_back(Node());
            k = new_idx;
        }

        if (a <= l && r <= b) {
            return addLine(f, k, l, r);
        }

        ll mid = l + (r - l) / 2;
        int nxt_lc = update(a, b, f, tr[k].lc, l, mid);
        tr[k].lc = nxt_lc;
        int nxt_rc = update(a, b, f, tr[k].rc, mid + 1, r);
        tr[k].rc = nxt_rc;
        
        return k;
    }

    ll query(ll pos, int k, ll l, ll r) {
        if (k == -1) return 2e18;
        
        ll cur = tr[k].line.calc(pos);
        if (l == r) return cur;
        
        ll mid = l + (r - l) / 2;
        if (pos <= mid)
            return min(cur, query(pos, tr[k].lc, l, mid));
        else 
            return min(cur, query(pos, tr[k].rc, mid + 1, r));
    }
};