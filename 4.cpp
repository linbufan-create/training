#include <bits/stdc++.h>
using namespace std;
int n, d;
constexpr int N = 1000;
int g[N][N];
int first = 1, second = 2;
int cnt[(int)1e7 + 10];

int main() {
	freopen("speech.in", "r", stdin);
	freopen("speech.out", "w", stdout);
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> g[i][j];
		}
	}
	cnt[1] = 1;
	for (int i = 1; i <= d; i++) {
		int tmp = first;
		first = second;
		second = g[second][tmp];
		if (cnt[first]) {
			cout << cnt[d % (i - cnt[i] + 1)];
			return 0;
		}
		cnt[first] = i;
	}
	cout << first;
}
