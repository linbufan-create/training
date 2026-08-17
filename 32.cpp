#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int cnt0[20], cnt1[20];
int a;
int ans;
int pre;

signed main() {
	cin >> n;
	for (int i = 0; i <= 16; i++) {
		cnt0[i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a;
		pre ^= a;
		for (int i = 0; i <= 16; i++) {
			if (pre & (1 << i)) {
				ans += (1 << i) * cnt0[i];
				cnt1[i]++;
			} else {
				ans += (1 << i) * cnt1[i];
				cnt0[i]++;
			}
		}
	}
	cout << ans << endl;
}
