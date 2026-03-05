struct Point {
    int x, y;

    Point() {}
    Point(int _x, int _y) {
        x = _x; y = _y;
    }
};

struct Edge {
    int u, v, w;

    Edge() {}
    Edge(int _u, int _v, int _w) {
        u = _u; v = _v; w = _w;
    }
};

// Cấu trúc dùng nội bộ để duyệt các nửa cạnh
struct HalfEdge {
    int id;
    int to;
    double angle;
};

// Cấu trúc cạnh cho đồ thị đối ngẫu
struct DualEdge {
    int w;
    int to;
};

int num_faces;
int outer_face;
vector<vector<DualEdge>> dual_adj;

int build_dual_graph(const vector<Point> &pts, const vector<Edge> &edges) {
    int n = pts.size();
    int m = edges.size();

    vector<vector<HalfEdge>> adj(n);
    vector<int> rev_edge(2 * m);

    // 1. tạo nửa cạnh và góc
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        double angle_uv = atan2((double)pts[v].y - pts[u].y, (double)pts[v].x - pts[u].x);
        double angle_vu = atan2((double)pts[u].y - pts[v].y, (double)pts[u].x - pts[v].x);

        adj[u].push_back({2 * i, v, angle_uv});
        adj[v].push_back({2 * i + 1, u, angle_vu});

        rev_edge[2 * i] = 2 * i + 1;
        rev_edge[2 * i + 1] = 2 * i;
    }

    // 2. sort góc CCW, có tie-breaker (khoảng cách, rồi id)
    const double EPS = 1e-12;
    for (int u = 0; u < n; ++u) {
        sort(adj[u].begin(), adj[u].end(), [&](const HalfEdge &a, const HalfEdge &b){
            if (fabs(a.angle - b.angle) > EPS) return a.angle < b.angle;
            // tie-break: gần trước (squared distance)
            long long dx1 = pts[a.to].x - pts[u].x;
            long long dy1 = pts[a.to].y - pts[u].y;
            long long d1 = dx1*dx1 + dy1*dy1;
            long long dx2 = pts[b.to].x - pts[u].x;
            long long dy2 = pts[b.to].y - pts[u].y;
            long long d2 = dx2*dx2 + dy2*dy2;
            if (d1 != d2) return d1 < d2;
            return a.id < b.id;
        });
    }

    // 3. xây nxt
    vector<int> nxt(2 * m, -1);
    for (int u = 0; u < n; ++u) {
        int deg = adj[u].size();
        if (deg == 0) continue;
        for (int i = 0; i < deg; ++i) {
            int current_edge_id = adj[u][i].id;
            int reverse_edge_id = rev_edge[current_edge_id];
            int next_idx = (i + 1) % deg;
            int next_edge_id = adj[u][next_idx].id;
            nxt[reverse_edge_id] = next_edge_id;
        }
    }

    // 4. tìm mặt, lưu area2 cho mỗi mặt
    vector<int> face_id(2 * m, -1);
    vector<long long> face_area2;
    num_faces = 0;

    for (int i = 0; i < 2 * m; ++i) {
        if (face_id[i] != -1) continue;
        int curr = i;
        long long area2 = 0;
        // duyệt chu trình mặt
        vector<int> cycle;
        while (face_id[curr] == -1) {
            face_id[curr] = num_faces;
            cycle.push_back(curr);

            int edge_idx = curr / 2;
            int u = (curr % 2 == 0) ? edges[edge_idx].u : edges[edge_idx].v;
            int v = (curr % 2 == 0) ? edges[edge_idx].v : edges[edge_idx].u;

            area2 += 1LL * pts[u].x * pts[v].y - 1LL * pts[v].x * pts[u].y;

            if (nxt[curr] == -1) {
                // embedding không đầy đủ / lỗi: bỏ chu trình này
                break;
            }
            curr = nxt[curr];
            // phòng trường hợp vòng lặp vô hạn (an toàn)
            if ((int)cycle.size() > 2 * m + 5) break;
        }
        face_area2.push_back(area2);
        num_faces++;
    }

    // 4b. xác định outer_face là mặt có |area| lớn nhất
    outer_face = 0;
    long long best_abs = llabs(face_area2[0]);
    for (int f = 1; f < (int)face_area2.size(); ++f) {
        long long a = llabs(face_area2[f]);
        if (a > best_abs) { best_abs = a; outer_face = f; }
    }

    // 5. xây đồ thị đối ngẫu
    dual_adj.assign(num_faces, vector<DualEdge>());
    for (int i = 0; i < m; ++i) {
        int f1 = face_id[2 * i];
        int f2 = face_id[2 * i + 1];
        int w = edges[i].w;
        if (f1 == -1 || f2 == -1) continue; // phòng lỗi
        // TÙY: nếu muốn bỏ self-loop trong dual (vì bridge), skip khi f1==f2
        if (f1 == f2) continue;
        dual_adj[f1].push_back({w, f2});
        dual_adj[f2].push_back({w, f1});
    }

    return outer_face;
}