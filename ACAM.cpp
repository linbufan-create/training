#include <bits/stdc++.h>
using namespace std;
int n;
constexpr int N = 2e5 + 10;
string t[N];
string s;
int ed[N];

struct trie {
	int fail[N];
	int e[N][26];
	int cnt = 0;
	bool is_end[N];
	int cnt_end[N];
	int vis[N];
	vector<int> ord;
	int insert(string s) {
		int p = 0;
		for (int i = 0; i < s.size(); i++) {
			if (!e[p][s[i] - 'a']) {
				e[p][s[i] - 'a'] = ++cnt;
			}
			p = e[p][s[i] - 'a'];
		}
		cnt_end[p]++;
		is_end[p] = 1;
		return p;
	}

	bool find(string s) {
		int p = 0;
		for (int i = 0; i < s.size(); i++) {
			if (e[p][s[i] - 'a'] == 0) {
				return false;
			}
			p = e[p][s[i] - 'a'];
		}
		return is_end[p];
	}

	void bfs() {
		queue<int> q;
		for (int i = 0; i < 26; i++) {
			if (e[0][i]) {
				q.push(e[0][i]);
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			ord.push_back(u);
			for (int i = 0; i < 26; i++) {
				if (e[u][i]) {
					fail[e[u][i]] = e[fail[u]][i];
					q.push(e[u][i]);
					continue;
				}
				e[u][i] = e[fail[u]][i];
			}
		}
	}

	void query(string t) {
		int u = 0;
		for (int i = 0; i < t.size(); i++) {
			u = e[u][t[i] - 'a'];
			vis[u]++;
		}
		
		for (int i = (int)ord.size() - 1; i >= 0; i--) {
			vis[fail[ord[i]]] += vis[ord[i]];
		}
	}
} trie;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
		ed[i] = trie.insert(t[i]);
	}
	trie.bfs();
	cin >> s;
	trie.query(s);
	for (int i = 1; i <= n; i++) {
		cout << trie.vis[ed[i]] << '\n';
	}
	return 0;
}
