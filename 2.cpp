#include <bits/stdc++.h>
using namespace std;
unsigned long long n, m, q;
constexpr unsigned long long N = 3e2 + 10, M = 3e2 + 10,
			     Q = 3e4 + 10;  // 4e4的数据会MLE,主动放弃
unsigned long long a[N], p[M], len[M], d[M], x[M], k[Q];
unsigned long long del1[M][N], del2[M][N], dell1[M][N], dell2[M][N], del[N][M],
	cnt[N];	 // 正向一阶/二阶差分,反向一阶/二阶差分,

int main() {
#define int unsigned long long
	freopen("202506E.in", "r", stdin);
	freopen("202506E.out", "w", stdout);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++) {
		if (!m) {
			break;
		}
		cin >> p[i] >> len[i] >> d[i] >> x[i];
		del1[i][p[i] + 1] += x[i];
		del2[i][p[i]] += x[i];
		dell1[i][p[i] - 1] -= d[i];
		dell2[i][p[i] + 1] -= d[i];
		dell2[i][p[i] + len[i]] += len[i] * d[i];
		dell2[i][p[i] - len[i]] += len[i] * d[i];
	}
	for (int i = 1; i <= m; i++) {
		if (!m) {
			break;
		}
		for (int j = n - 1; j >= 1; j--) {
			dell2[i][j] += dell2[i][j + 1];
		}
		for (int j = 2; j <= n; j++) {
			dell1[i][j] += dell2[i][j - 1];
		}
		for (int j = n; j >= 1; j--) {
			del2[i][j] += dell2[i][j];
			del[j][i] = del[j][i - 1] + del2[i][j];
		}
		for (int j = 1; j <= n; j++) {
			del1[i][j] += dell1[i][j];
			del[j][i] += del1[i][j];
		}
	}
	for (int i = 1; i <= q; i++) {
		cin >> k[i];
	}
	if (!m) {
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= q; i++) {
			int pos = upper_bound(a + 1, a + n + 1, k[i]) - a;
			cout << pos << endl;
		}
		return 0;
	}
	for (int i = 1; i <= q; i++) {
		for (int j = 1; j <= n; j++) {
			int l = 1, r = m, mid;
			while (l < r) {
				mid = (l + r) >> 1;
				if (a[j] + del[j][mid] <= k[i]) {
					l = mid;
				} else {
					r = mid - 1;
				}
			}
			if (a[j] + del[j][mid] <= k[i]) {
				cnt[i] = mid;
			} else {
				cnt[i] = 0;
			}
		}
		sort(cnt + 1, cnt + n + 1);
		unsigned long long ans = 0;
		cnt[0] = 0;
		for (int j = 1; j <= n; j++) {
			if (!cnt[j] || cnt[j] == cnt[j - 1]) {
				continue;
			}
			ans += (cnt[j] - cnt[j - 1])
				* (n - j + 1)
				% (unsigned long long)(1e9 + 7)
				* (n - j)
				% (unsigned long long)(1e9 + 7)
				* (unsigned long long)(5e8 + 4)
				% (unsigned long long)(1e9 + 7);
			ans %= (unsigned long long)(1e9 + 7);
		}
		cout << ans << '\n';
	}
}
