#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N = 105, M = 105;
int a[N];
int b[M];
int c[M];
pair<int, int> song[M];
long long dp[M][N * M];	 // dp[i][k][s]表示前i个,选k首,Σmin(k,ai)为s
int sum[M];  // sum[k]表示Σi<=k,min(i,ai)
long long ans = 0;
int n, m;

signed main() {
	// 输入
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; ++i) {
		cin >> song[i].first >> song[i].second;
	}
	// 排序
	sort(song + 1, song + m + 1);
	reverse(song + 1, song + m + 1);
	// 预处理
	for (int i = 1; i <= m; ++i) {
		for (int ai : a) {
			sum[i] += min(ai, i);
		}
		// cout << "sum[" << i << "]:" << sum[i] << endl;
	}
	// dp
	// memset(dp, INT_MIN, sizeof(dp));
	for (int k = 0; k <= m; ++k) {
		for (int s = 0; s <= m * n; ++s) {
			dp[k][s] = (long long)-1e18;
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= m; ++i) {
		for (int k = i; k >= 0; --k) {
			for (int s = sum[k]; s >= b[i]; --s) {
				// 转移
				if (sum[k] >= s && s >= song[i].first && k > 0) {
					dp[k][s] =
						max(dp[k - 1][s - song[i].first] + song[i].second,
						    dp[k][s]);
					ans = max(ans, dp[k][s]);
				}
				// cout << "dp[" << i << "][" << k << "][" << s << "]:" <<
				// dp[i][k][s] << endl;
			}
		}
	}
	cout << ans << endl;
}  //
