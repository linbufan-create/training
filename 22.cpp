#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, t;
constexpr int N = 2e5 + 10;
int a[N];
unordered_map<int, int> mp;
long long sum[N], tmp[N];
int n2;
int ans;

class SegmentTree {
private:
	struct node {
		int l, r;
		int sum;
	} tree[4 * N];

public:
#define ls (num << 1)
#define rs ((num << 1) | 1)

	void build(int num, int l, int r) {
		tree[num].l = l;
		tree[num].r = r;
		tree[num].sum = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}

	void pushup(int num) {
		tree[num].sum = tree[ls].sum + tree[rs].sum;
	}

	void update(int num, int pos, int d) {
		if (tree[num].l == tree[num].r) {
			tree[num].sum += d;
			return;
		}
		int mid = (tree[num].l + tree[num].r) >> 1;
		if (pos <= mid) {
			update(ls, pos, d);
		} else {
			update(rs, pos, d);
		}
		pushup(num);
	}

	int query(int num, int l, int r) {
		if (tree[num].l > r || tree[num].r < l) {
			return 0l;
		}
		if (tree[num].l >= l && tree[num].r <= r) {
			return tree[num].sum;
		}
		int mid = (tree[num].l + tree[num].r) >> 1;
		if (l > mid) {
			return query(rs, l, r);
		} else if (r <= mid) {
			return query(ls, l, r);
		} else {
			return query(ls, l, r) + query(rs, l, r);
		}
	}
} st;

void build() {
	st.build(1, 1, n2);
}

void update(int pos, int d) {
	st.update(1, pos, d);
}

int query(int l, int r) {
	return st.query(1, l, r);
}

signed main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	cin >> n >> t;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
		tmp[i] = sum[i];
	}
	sort(tmp, tmp + n + 1);
	n2 = unique(tmp, tmp + n + 1) - tmp;
	for (int i = 0; i <= n; i++) {
		mp[sum[i]] = lower_bound(tmp, tmp + n2, sum[i]) - tmp + 1;
	}
	build();
	update(mp[0], 1);
	for (int i = 1; i <= n; i++) {
		int wt = sum[i] - t;
		int rt = upper_bound(tmp, tmp + n2, wt) - tmp;
		ans += query(rt + 1, n2);
		update(mp[sum[i]], 1);
	}
	cout << ans << endl;
}
