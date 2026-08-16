#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define int long long
int n, k;
constexpr int N = 5e5 + 10;
int a[N], b[N], c[N];
map<int, map<int, map<int, bool>>> vis;

bool cmp(int a, int b) {
	return a > b;
}

struct node {
	int x, y, z;
	int val;

	bool operator<(const node& other) const {
		return this->val < other.val;
	}
};

node make_node(int x, int y, int z) {
	return {x, y, z, a[x] * b[y] + a[x] * c[z] + b[y] * c[z]};
}

int get_val(int x, int y, int z) {
	return a[x] * b[y] + a[x] * c[z] + b[y] * c[z];
}

signed main() {
	freopen("Attribute.in", "r", stdin);
	freopen("Attribute.out", "w", stdout);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + n + 1, cmp);
	sort(c + 1, c + n + 1, cmp);
	priority_queue<node, vector<node>, less<node>> pq;
	pq.push(make_node(1, 1, 1));
	vis[1][1][1] = 1;
	for (int i = 1; i < k; i++) {
		node now = pq.top();
		pq.pop();
		int x = now.x;
		int y = now.y;
		int z = now.z;
		if (x + 1 <= n && !vis[x + 1][y][z]) {
			pq.push(make_node(x + 1, y, z));
			vis[x + 1][y][z] = 1;
		}
		if (y + 1 <= n && !vis[x][y + 1][z]) {
			pq.push(make_node(x, y + 1, z));
			vis[x][y + 1][z] = 1;
		}
		if (z + 1 <= n && !vis[x][y][z + 1]) {
			pq.push(make_node(x, y, z + 1));
			vis[x][y][z + 1] = 1;
		}
	}
	cout << pq.top().val << endl;
	return 0;
}
