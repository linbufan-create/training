#include <bits/stdc++.h>
using namespace std;
unordered_map<string, int> f;
int m;
constexpr int M = 1e6 + 10;
string s[M];
int ans = 0;

int main() {
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> s[i];
		string_view s2 = s[i];
		f[s[i]] = 1;
		unordered_map<string, bool> vis;
		f[s[i]] += f[string(s2.substr(1, s2.size() - 1))];
		vis[string(s2.substr(1, s2.size() - 1))] = 1;
		f[s[i]] += f[string(s2.substr(0, s[i].size() - 1))]
			* (!vis[string(s2.substr(1, s2.size() - 1))]);
		for (int j = 1; j < s[i].size() - 1; j++) {
			f[s[i]] += f[string(s2.substr(0, j - 1))
				     + string(s2.substr(j + 1, s[i].size() - j - 1))]
				* (int)(!vis[string(s2.substr(1, s2.size() - 1))]);
			if (!vis[string(s2.substr(1, s2.size() - 1))]) {
				vis[string(s2.substr(1, s2.size() - 1))] = 1;
			}
		}
		ans = max(ans, f[s[i]]);
		vis.clear();
	}
	cout << ans << endl;
}
