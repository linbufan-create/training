#include <bits/stdc++.h>
using namespace std;
int n, m;
constexpr int N = 1e6 + 10;
pair<int, pair<pair<int, int>, int>> a[N];
int p;
int mp[N];
int s[N];
int cnt[1005];

int main() {
        freopen64("Light.in", "r", stdin);
        freopen64("Light.out", "w", stdout);
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
#define t a[i].first
                cin >> a[i].first;
                if (t == 1) {
                        cin >> a[i].second.first.first >> a[i].second.first.second;
                } else if (t == 2) {
                        cin >> a[i].second.second;
                } else {
                        p = i;
                }
        }
        for (int i = p + 1; i <= m; i++) {
                if (a[i].first == 2) {
                        int x = a[i].second.second;
                        if (x == 1) {
                                s[1] = !s[1];
                                continue;
                        }
                        if (x < sqrt(n)) {
                                cnt[x] = !cnt[x];
                                continue;
                        }
                        for (int j = x; j <= n; j += x) {
                                mp[j] = !mp[j];
                        }
                } else {
                        int l = a[i].second.first.first, r = a[i].second.first.second;
                        s[l] = 1 - s[l];
                        s[r + 1] = 1 - s[r + 1];
                }
        }
        for (int i = 1; i <= sqrt(n) + 1; i++) {
                if (cnt[i]) {
                        for (int j = i; j <= n; j += i) {
                                mp[j] = !mp[j];
                        }
                }
        }
        for (int i = 1; i <= n; i++) {
                s[i] ^= s[i - 1];
                mp[i] ^= s[i];
                if (mp[i] == 1) {
                        cout << i << " ";
                }
        }
}
