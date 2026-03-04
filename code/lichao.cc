// Lichao
struct Line {
    ld a, b;

    Line() {
        a = 0;
        b = 1e18;
    }

    Line(ld _a, ld _b) {
        a = _a;
        b = _b;
    }

    ld calc (int x) { return a * x + b; }

    ld slope() { return a; }
};

struct LiChao {
    vector<Line> tr;

    LiChao() {}
    LiChao (int sz) : tr(4 * sz, Line(0, LLONG_MAX)) {}

    void addLine (Line f, int k, int l, int r) {
        /*
            f: đường thẳng cần cập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (l == r) {
            tr[k] = (f.calc(l) < tr[k].calc(l) ? f : tr[k]);
            return;
        }
        int mid = (l + r) >> 1;
        if (f.calc(mid) < tr[k].calc(mid)) swap(tr[k], f);
        if (f.slope() > tr[k].slope())
            addLine(f, 2 * k, l, mid); // trường hợp 1.1
        if (f.slope() < tr[k].slope())
            addLine(f, 2 * k + 1, mid + 1, r); // trường hợp 1.2
    }

    void update (int a, int b, Line f, int k, int l, int r) {
        /*
            a..b: khoảng cần cập nhật
            f: đường thẳng cần nhập nhật
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        if (b < l || r < a) return;

        // thực hiện thao tác cập nhật của Li-chao tree cơ bản
        // khi khoảng mà nút quản lý nằm gọn trong khoảng cần cập nhật
        if (a <= l && r <= b) {
            return addLine(f, k, l, r), void();
        }

        // chia để trị tương tự Segment tree
        int mid = (l + r) >> 1;
        update(a, b, f, 2 * k, l, mid);
        update(a, b, f, 2 * k + 1, mid + 1, r);
    }

    ld query (int pos, int k, int l, int r) {
        /*
            pos: vị trí được truy vấn
            k: nút hiện tại
            l..r: khoảng mà nút quản lý
        */
        ld cur = tr[k].calc(pos);
        int mid = (l + r) >> 1;
        if (l == r) return cur;
        if (pos <= mid)
            return min(cur, query(pos, 2 * k, l, mid));
        else return min(cur, query(pos, 2 * k + 1, mid + 1, r));
    }
};