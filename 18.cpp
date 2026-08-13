#include <bits/stdc++.h>
using namespace std;
int n, x, k;
constexpr int N = 1e6 + 10;
int a[N];
int b[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> x >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = (a[i] != x);
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		b[i] = (b[i] != x);
	}
	int be = 0;
	int heada = 1, headb = 1, cnt = 0;
	while (heada <= n || headb <= n) {
		if (be) {
			cnt++;
		}
		while (heada <= n && a[heada] == be) {
			heada++;
		}
		while (headb <= n && b[headb] == be) {
			headb++;
		}
		be = !be;
	}
	if (!cnt) {
		cout << 0 << endl;
	} else if (cnt - k >= 1) {
		cout << cnt - k << endl;
	} else {
		cout << 1 << endl;
	}
	return 0;
}
