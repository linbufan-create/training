#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x & (-x))
#define fmax f_max
#define fmin f_min
int t;
const int N = 2e5 + 10;
int a[N], fmax[N], l2[N], n, fmin[N];
int vis_max[64], vis_min[64], vis_and[64][64];

void solve() {
	cin >> n;
	memset(vis_max, 0, sizeof(vis_max));
	memset(vis_min, 0, sizeof(vis_min));
	memset(vis_and, 0, sizeof(vis_and));
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		l2[i] = log2l(a[i]);
		fmax[i] = 1 << (l2[i] - 1);
		fmin[i] = log2l(lowbit(a[i]));
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i > 1) {
			ans += (i - 1)
				- vis_max[l2[i]]
				- vis_min[fmin[i]]
				+ vis_and[l2[i]][fmin[i]];
		}
		vis_max[l2[i]]++;
		vis_min[f_min[i]]++;
		vis_and[l2[i]][fmin[i]]++;
	}
	cout << ans << endl;
}

signed main() {
	freopen("bipolar.in", "r", stdin);
	freopen("bipolar.out", "w", stdout);
	cin >> t;
	while (t--) {
		solve();
	}
}
