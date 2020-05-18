#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = (int) 3e5 + 1;
const long long LINF = (long long) 1e18 + 123;

struct DSU {
    int n;
    int dsu[N];
    int leftmost[N];
    int rightmost[N];

    void init(int n_) {
        n = n_ + 1;
        for (int i = 0; i < n; i++) {
            dsu[i] = -1;
            leftmost[i] = i;
            rightmost[i] = i;
        }
    }

    int get(int v) {
        if (dsu[v] == v) {
            return v;
        }
        return (dsu[v] = get(dsu[v]));
    }

    void unite(int u, int v) {
        u = get(u);
        v = get(v);
        dsu[u] = v;
        leftmost[v] = min(leftmost[v], leftmost[u]);
        rightmost[v] = max(rightmost[v], rightmost[u]);
    }

    bool is_enabled(int v) {
        return dsu[v] != -1;
    }

    pair<int, int> get_segment(int v) {
        if (!is_enabled(v)) {
            return {-1, -1};
        }
        v = get(v);
        return {leftmost[v], rightmost[v]};
    }

    void enable(int v) {
        dsu[v] = v;
        if (v - 1 >= 0 && dsu[v - 1] != -1) {
            unite(v - 1, v);
        }
        if (v + 1 < n && dsu[v + 1] != -1) {
            unite(v, v + 1);
        }
    }
};

class MinTree {
public:
    void init(int n_) {
        n = n_ + 1;
        fill(tree, tree + 4 * n, LINF);
    }

    void update(int index, long long value) {
        update(0, 0, n, index, value);
    }

    long long get(int l, int r) {
        return get(0, 0, n, l, r + 1);
    }

private:
    int n;
    long long tree[4 * N];

    void update(int i, int tl, int tr, int index, long long value) {
        if (tl == tr - 1) {
            tree[i] = min(tree[i], value);
            return;
        }
        int tm = (tl + tr) / 2;
        if (index < tm) {
            update(2 * i + 1, tl, tm, index, value);
        } else {
            update(2 * i + 2, tm, tr, index, value);
        }
        tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }

    long long get(int i, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) {
            return LINF;
        }
        if (l <= tl && tr <= r) {
            return tree[i];
        }
        int tm = (tl + tr) / 2;
        return min(get(2 * i + 1, tl, tm, l, r), get(2 * i + 2, tm, tr, l, r));
    }
};

struct Query {
    int l, r;
    long long x;
    int id;
};

int n, m;
long long h[N];
long long pref[N];
Query queries[N];
MinTree tree;
DSU dsu;
long long ans[N];

long long get_sum(int l, int r) {
    return pref[r] - pref[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    vector<pair<long long, int>> heights(n);
    tree.init(n);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        heights[i - 1] = {h[i], i};
        pref[i] = pref[i - 1] + h[i];
        tree.update(i, -h[i]);
    }

    for (int i = 0; i < m; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].x;
        queries[i].id = i;
        ans[i] = LINF;
        int left, right;

        left = queries[i].l - 1;
        right = queries[i].r + 1;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            int length = mid - queries[i].l + 1;
            if (get_sum(queries[i].l, mid) * 2 * length >= queries[i].x) {
                right = mid;
            } else {
                left = mid;
            }
        }

        if (right != queries[i].r + 1) {
            ans[i] = min(ans[i], -tree.get(queries[i].l, right));
        }

        left = queries[i].l - 1;
        right = queries[i].r + 1;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            int length = queries[i].r - mid + 1;
            if (get_sum(mid, queries[i].r) * 2 * length >= queries[i].x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (left != queries[i].l - 1) {
            ans[i] = min(ans[i], -tree.get(left, queries[i].r));
            queries[i].r = right - 1;
        }
    }

    sort(heights.begin(), heights.end());
    dsu.init(n);
    vector<pair<long long, pair<int, long long>>> events;
    for (int i = 0; i < n; i++) {
        int pos = heights[i].second;
        dsu.enable(pos);
        auto segment = dsu.get_segment(pos);
        int left = segment.first;
        int right = segment.second;
        int length = right - left + 1;
        long long value = get_sum(left, right) * 2 * length;
        events.emplace_back(value, make_pair(left, h[pos]));
    }

    sort(events.begin(), events.end(), [&] (const auto& x, const auto& y) {
        return x.first > y.first;
    });
    sort(queries, queries + m, [&] (const auto &x, const auto &y) {
        return x.x > y.x;
    });

    tree.init(n);
    int ptr = 0;
    for (int i = 0; i < m; i++) {
        while (ptr < n && events[ptr].first >= queries[i].x) {
            tree.update(events[ptr].second.first, events[ptr].second.second);
            ptr++;
        }
        int id = queries[i].id;
        if (ans[id] == LINF) {
            continue;
        }
        ans[id] = min(ans[id], tree.get(queries[i].l, queries[i].r));
    }

    for (int i = 0; i < m; i++) {
        cout << (ans[i] == LINF ? -1 : ans[i]) << "\n";
    }

    return 0;
}
