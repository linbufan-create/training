#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 10;
int n;
int p[N], tmp[N];
unordered_map<int, int> mp;
int sz[N];
vector<int> dfn;
vector<int> e[N];
int pos[N];

void dfs(int x) {
	dfn.push_back(x);
	if (e[x].empty()) {
		sz[x] = 1;
		return;
	}
	for (int v : e[x]) {
		dfs(v);
		sz[x] += sz[v];
	}
	sz[x]++;
}

template <typename T>
class SegmentTree {
private:
	struct node {
		int l, r;
		int ls, rs;
		T sum;
	} tree[N << 5];

	int cnt = 0;

public:
	vector<int> rt;

	SegmentTree() {
		rt.assign(1, 0);
	}

	int build(int l, int r) {
		int p = cnt++;
		tree[p] = {l, r, 0, 0, 0};
		if (l == r) {
			return p;
		}
		int mid = (l + r) >> 1;
		tree[p].ls = build(l, mid);
		tree[p].rs = build(mid + 1, r);
		return p;
	}

	int update(int pre, int l, int r, int val) {
		int p = ++cnt;
		tree[p] = tree[pre];
		tree[p].sum++;
		if (l == r) {
			return p;
		}
		int mid = (l + r) >> 1;
		if (val <= mid) {
			tree[p].ls = update(tree[p].ls, l, mid, val);
		} else {
			tree[p].rs = update(tree[p].rs, mid + 1, r, val);
		}
		return p;
	}

	int query(int u, int v, int l, int r, int ql, int qr) {
		if (ql > r || qr < l) {
			return 0;
		}
		if (l >= ql && r <= qr) {
			return tree[v].sum - tree[u].sum;
		}
		int mid = (l + r) >> 1;
		return query(tree[u].ls, tree[v].ls, l, mid, ql, qr)
			+ query(tree[u].rs, tree[v].rs, mid + 1, r, ql, qr);
	}
};

SegmentTree<int> st;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		tmp[i] = p[i];
	}
	sort(tmp + 1, tmp + n + 1);
	for (int i = 1; i <= n; i++) {
		mp[p[i]] = lower_bound(tmp + 1, tmp + n + 1, p[i]) - tmp;
		p[i] = mp[p[i]];
	}
	for (int i = 2; i <= n; i++) {
		int fa;
		cin >> fa;
		e[fa].push_back(i);
	}
	dfn.assign(1, 0);
	dfs(1);
	for (int i = 1; i <= n; i++) {
		pos[dfn[i]] = i;
	}
	st.rt[0] = st.build(1, n);
	for (int i = 1; i <= n; i++) {
		st.rt.push_back(st.update(st.rt[i - 1], 1, n, p[dfn[i]]));
	}
	for (int v = 1; v <= n; v++) {
		int i = pos[v];
		cout
			<< st.query(st.rt[i], st.rt[i + sz[dfn[i]] - 1], 1, n, p[dfn[i]] + 1, n)
			<< endl;
	}
}
