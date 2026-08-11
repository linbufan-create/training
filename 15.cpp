#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
// template <typename T>
// class SegmentTree
// {
// private:
//         int cnt;
//         struct node{
//                 node *lson, *rson;
//                 T mx;
//                 int l, int r;
//                 T tg;
//         } tree[N];

// public:
// #define ls num*2
// #define rs (num*2+1)
//         void build(int num){
//                 int l = tree[num].l;
//                 int r = tree[num].r;
//                 int mid = (l + r) >> 1;
//                 tree[ls].l = l;
//                 tree[rs].l = mid + 1;
//                 tree[ls].r = mid;
//                 tree[rs].r = r;
//                 build(ls);
//                 build(rs);
//                 tree[num].mx = max(tree[ls].mx, tree[rs].mx);
//         }
//         void push_up(int num){
//                 tree[num].mx = max(tree[ls].mx, tree[rs].mx);
//         }

// #undef ls
// #undef rs
// };

// SegmentTree<int> st;
int n, m, k;
vector<pair<int, int>> a[N];
long long dp[N];

int main() {
        ios::sync_with_stdio(0);
        cin.tie(nullptr);
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
                int l, r, w;
                cin >> l >> r >> w;
                if (l + k - 1 <= r) {
                        a[l + k - 1].push_back({r, w});
                }
        }
        dp[0] = 0;
        typedef pair<int, int> pi;
        priority_queue<pi, vector<pi>, less<pi>> pq;
        for (int i = 1; i <= m; i++) {
                dp[i] = dp[i - 1];
                for (pi j : a[i]) {
                        pq.push({j.second, j.first});
                }
                while (!pq.empty() && pq.top().second < i) {
                        pq.pop();
                }
                if (!pq.empty()) {
                        dp[i] = max(dp[i], dp[i - k] + pq.top().first);
                }
        }
        cout << dp[m] << endl;
}
