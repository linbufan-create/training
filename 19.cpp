#include <bits/stdc++.h>
using namespace std;
int n;
constexpr int N = 1e5 + 10;
int a[N];

struct cmp {
	bool operator()(const deque<int>& a, const deque<int>& b) {
		return a.size() > b.size();
	}
};

bool check(int x) {
	priority_queue<deque<int>, vector<deque<int>>, cmp> q;
	for (int i = 1; i <= n; i++) {
		if (q.empty()) {
			deque<int> tmp;
			tmp.push_back(a[i]);
			q.push(tmp);
			continue;
		}
		deque<int> tmp;
		vector<deque<int>> tmp2;
		while (!q.empty()) {
			if (q.top().back() + 1 == a[i]) {
				deque<int> tmpq = q.top();
				q.pop();
				tmpq.push_back(a[i]);
				q.push(tmpq);
				for (deque j : tmp2) {
					q.push(j);
				}
				goto ed;
			}
			if (q.top().back() == a[i]) {
				tmp2.push_back(q.top());
				q.pop();
				continue;
			}
			if (q.top().size() < x) {
				return 0;
			}
			q.pop();
		}
		for (deque j : tmp2) {
			q.push(j);
		}
		tmp.push_back(a[i]);
		q.push(tmp);
	ed:;
	}
	if (q.top().size() < x) {
		return 0;
	}
	return 1;
}

int main() {
	freopen("group.in", "r", stdin);
	freopen("group.out", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	int l = 1, r = n, mid;
	while (l < r) {
		mid = (l + r + 1) >> 1;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	cout << l << endl;
}
