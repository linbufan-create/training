#include <bits/stdc++.h>
using namespace std;
constexpr int N = (int)(2e5 + 10);
int n, m;
pair<int, int> a[N];

struct cmp {
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second;
        }
};

int ans;
int cnt = 1;
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

int main() {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
                cin >> a[i].first >> a[i].second;
        }
        sort(a + 1, a + m + 1);
        for (int i = 1; i <= n; i++) {
                while (cnt <= m && a[cnt].first <= i) {
                        pq.push(a[cnt]);
                        cnt++;
                }
                while (!pq.empty() && pq.top().second < i) {
                        pq.pop();
                }
                if (pq.empty()) {
                        cout << ans << endl;
                        continue;
                }
                ++ans;
                cout << ans << endl;
                pq.pop();
        }
}
