/*
calc(n,k)n表示n完全拆分成0/1后前k个数的和
*/
// 模考1-T1
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, l, r;

int getlen(int x) {
	if (x <= 1) {
		return 1;
	}
	return getlen(x >> 1) * 2 + 1;
}

int calc(int x, int k) {
	if (k <= 0) {
		return 0;
	}
	if (x <= 1) {
		return x;
	}
	int len = getlen(x >> 1);
	if (k <= len) {
		return calc(x >> 1, k);
	}
	if (k == len + 1) {
		return (x >> 1) + (x & 1);
	}
	return (x >> 1) + (x & 1) + calc(x >> 1, k - len - 1);
}

signed main() {
	freopen("crystal.in", "r", stdin);
	freopen("crystal.out", "w", stdout);
	cin >> n >> l >> r;
	cout << calc(n, r) - calc(n, l - 1);
}
