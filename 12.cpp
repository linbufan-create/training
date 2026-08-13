#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353, N = 2e5 + 10;
int a[N], fact[N], vis[N], cnt[N], use[2], bad[2], tot[2], dup_, n, q;
#define PUT 1
#define DEL -1

void add_bad(int p, int x, int v) {
	if (x == 0) {
		return;
	}
	for (int t = 0; t < 2; t++) {
		int need = (p & 1) ^ t;
		if (cnt[x] != need) {
			bad[t] += v;
		}
	}
}

void init() {
	fact[0] = 1;
	for (int i = 1; i <= n; i++) {
		fact[i] = (fact[i - 1] * i) % mod;
		cnt[i] = __builtin_popcountll((unsigned long long)i) & 1;
	}
}

void solve() {
	if ((tot[0] != n / 2) || (tot[1] != n / 2) || (n & 1) || dup_) {
		cout << 0 << endl;
		return;
	}
	int base = fact[tot[0] - use[0]] * fact[tot[1] - use[1]] % mod;
	int ans = 0;
	if (!bad[0]) {
		ans += base;
		ans %= mod;
	}
	if (!bad[1]) {
		ans += base;
		ans %= mod;
	}
	cout << ans << endl;
	return;
}

signed main() {
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
	cin >> n >> q;
	init();
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		tot[cnt[i]]++;
		if (a[i] > 0) {
			vis[a[i]]++;
			if (vis[a[i]] == 2) {
				dup_++;
			} else {
				use[cnt[a[i]]]++;
			}

			add_bad(i, a[i], PUT);
		}
	}
	if (n & 1) {
		for (int i = 0; i <= q; i++) {
			cout << 0 << endl;
		}
		return 0;
	}
	solve();
	for (int i = 1; i <= q; i++) {
		int p, x;
		cin >> p >> x;
		if (a[p] != 0) {
			if (vis[a[p]] == 2) {
				dup_--;
			} else if (vis[a[p]] == 1) {
				use[cnt[a[p]]]--;
			}
			add_bad(p, a[p], DEL);
			vis[a[p]]--;
		}
		if (x != 0) {
			if (vis[x] == 1) {
				dup_++;
			} else if (vis[x] == 0) {
				use[cnt[x]]++;
			}
			vis[x]++;
			add_bad(p, x, PUT);
		}
		a[p] = x;
		solve();
	}
}
