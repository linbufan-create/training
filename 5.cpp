#include <bits/stdc++.h>
using namespace std;
int n, m;
constexpr int M = 1e5 + 10;
int a[M];
int ans = 0;
int chs[M];

void dfs(int step) {
	if (step > n) {
		vector<int> cnt(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (i == 1) {
				cnt[i] = 1;
				continue;
			}
			if (chs[i] == chs[i - 1]) {
				cnt[i] = cnt[i - 1] + 1;
				if (cnt[i] > a[chs[i]]) {
					return;
				}
			} else {
				cnt[i] = 1;
			}
		}
		ans++;
		return;
	}
	for (int i = 1; i <= m; i++) {
		chs[step] = i;
		dfs(step + 1);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dfs(1);
	cout << ans;
}
