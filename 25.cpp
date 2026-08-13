#include <bits/stdc++.h>
using namespace std;
int t;
constexpr int N = 3010;
int dp[N][N][4];

int n, m, k, x;
vector<int> e[N];

void solve() {
	memset(e,0, sizeof(e));
	cin >> n >> m >> k >> x;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
}

int main() {
#ifdef ONLINE_jUDGE
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "r", stdout);
#endif
	cin >> t;
	while (t--) {
		solve();
	}
}
