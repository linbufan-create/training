#include <bits/stdc++.h>
using namespace std;
const long long N = 2e5 + 10;
unsigned long long a[N];
unsigned long long n, m;

template <typename T>
class SegmentTree {
private:
	struct {
		unsigned int ls, rs;
		T sum;
		T tag;
		unsigned int l, r;
	} tree[4 * N];

public:
#define lson (num << 1)
#define rson ((num << 1) | 1)

	void pushup(unsigned int num) {
		tree[num].sum = tree[lson].sum + tree[rson].sum;
	}

	void build(unsigned int num, unsigned int l, unsigned int r) {
		tree[num].sum = 0;
		if (l == r) {
			tree[num].sum = a[l];
			tree[num].l = l;
			tree[num].r = r;
			tree[num].tag = 0;
			return;
		}
		tree[num].ls = lson;
		tree[num].rs = rson;
		tree[num].tag = 0;
		tree[num].l = l;
		tree[num].r = r;
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(num);
	}

	void pushdown(unsigned int num) {
		T& t = tree[num].tag;
		if (tree[num].l == tree[num].r) {
			tree[num].sum += t * (tree[num].r - tree[num].l + 1);
			return;
		}
		if (!t) {
			return;
		}
		if (tree[num].l == tree[num].r) {
			return;
		}
		int len1 = tree[lson].r - tree[lson].l + 1, len2 = tree[rson].r - tree[rson].l + 1;
		tree[lson].sum += len1 * t;
		tree[lson].tag += t;
		tree[rson].sum += len2 * t;
		tree[rson].tag += t;
		t = 0;
	}

	void update(unsigned int l, unsigned int r, unsigned int num, unsigned int d) {
		if (l > tree[num].r || r < tree[num].l) {
			return;
		}
		if (tree[num].l >= l && tree[num].r <= r) {
			tree[num].tag += d;
			tree[num].sum += (T)d * (tree[num].r - tree[num].l + 1);
			return;
		}
		unsigned int mid = (tree[num].l + tree[num].r) >> 1;
		pushdown(num);
		if (l > mid) {
			update(l, r, rson, d);
		} else if (r <= mid) {
			update(l, r, lson, d);
		} else {
			update(l, r, lson, d);
			update(l, r, rson, d);
		}
		pushup(num);
	}

	T query(unsigned int l, unsigned int r, unsigned int num) {
		if (l > tree[num].r || r < tree[num].l) {
			return 0;
		}
		pushdown(num);
		if (tree[num].l >= l && tree[num].r <= r) {
			return tree[num].sum;
		}
		unsigned int mid = (tree[num].l + tree[num].r) >> 1;
		if (l > mid) {
			return query(l, r, rson);
		} else if (r <= mid) {
			return query(l, r, lson);
		} else {
			return query(l, r, lson) + query(l, r, rson);
		}
	}
};

SegmentTree<unsigned long long> st;

void init() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> m;
	for (unsigned long long i = 1; i <= n; i++) {
		cin >> a[i];
	}
	st.build(1, 1, n);
}

int main() {
	init();
	for (unsigned long long i = 1; i <= m; i++) {
		unsigned int opt;
		cin >> opt;
		if (opt == 1) {
			unsigned long long x, y, k;
			cin >> x >> y >> k;
			st.update(x, y, 1u, k);
		} else if (opt == 2) {
			unsigned long long x, y;
			cin >> x >> y;
			cout << st.query(x, y, 1) << endl;
		}
	}
}
