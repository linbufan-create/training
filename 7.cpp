/*
T3
dp[i][j][k]= 以节点 i 为根的子树中，进行 j 次数据流测试，且未被覆盖的节点到 i
的最大深度为 k 时的最小代价
设节点 i 的子孙节点中 C 的最小值为 Ci∗​。并设节点 i
的子节点为 v1​,v2​,…,vm​。此时 dp[i][j][k]
可以通过以下状态转移方程求得：
dp[i][j][k+1]=j1​+j2​+⋯+jm​=jmax(k1​,k2​,…,km​)≤k​min​(t=1∑m​dp[vt​][jt​][kt​])
dp[i][j][0]=min⁡j′(dp[i][j′][j]+C∗×max⁡(0,j−j′))
dp[i][j][0]=j′min​(dp[i][j′][j]+C∗×max(0,j−j′))
状态转移使用前缀最小值
设节点 i 的子树中最远节点到 i 的深度为 hi
dp 数组中需要计算的仅有 j≤hi 且 k≤hi​ 的部分
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3fll
constexpr int N = 700;  // n 的最大值为 700
int p[N];  // pi 表示 i 号节点的父节点
int c[N];  // i 号节点的花费
int ci[N];  // ci[i]表示 i 的 子孙节点的最小值
int hi[N];  // hi[i]表示以 i 为根的子树中最远节点到 i 的距离
int sz[N];  // 以 i 为根的子树的大小
int n;  // 节点数
int sum_sz;  // 已经合并的节点数
vector<vector<int>> dp[N];  // dp数组
vector<int> e[N];  // 邻接表

void dfs(int x)  // 使用dfs进行树形dp
{
        for (int i : e[x]) {
                dfs(i);
                sz[x] += sz[i];
                hi[x] = max(hi[i] + 1, hi[x]);  // 统计离i最远的点
                ci[x] = min(ci[x], ci[i]);
        }
        if (e[x].empty()) {
                dp[x][0][0] = 0;
                dp[x][0][1] = 0;
                dp[x][1][0] = c[x];
                ci[x] = c[x];
                hi[x] = 1;
                sz[x] = 1;
                return;
        }
        dp[x].assign(hi[x] + 1, vector<int>(hi[x] + 1, inf));  // 给dp[x]分配空间
        vector<vector<int>> f(sz[x] + 1,
                              vector<int>(sz[x] + 1, inf));  // f[j][k] = 已经合并了\
        前几个子节点后，从这些子树中分配了 j 次测试，且最深未覆盖点到子节点的距离为 k 的最小代价
        vector<vector<int>> g(
                sz[x] + 1,
                vector<int>(sz[x] + 1, inf));  //g[j][k]用于和新子节点合并时\
        暂存结果。
        f[0][0] = 0;
        int hi_max = 0;
        for (int v : e[x]) {
                for (int i = 1; i <= sum_sz; ++i) {
                        f[i] = min(f[i], f[i - 1]);
                }
                for (int i = 0; i <= sz[v]; ++i) {
                        for (int j = 1; j <= hi[v]; ++j) {
                                dp[v][i][j] = min(dp[v][i][j], dp[v][i][j - 1]);
                        }
                }
                for (int i = 0; i <= sum_sz; ++i) {
                        for (int j = 0; j <= sz[v]; ++j) {
                                for (int k = 0; k <= max(hi_max, hi[v]); ++k) {
                                        g[i + j][k] = min(g[i + j][k], f[i][k] + dp[v][j][k]);
                                }
                        }
                }
                sum_sz += sz[v];
                hi_max = max(hi_max, hi[v]);
                f.swap(g);
                g.assign(sum_sz + sz[v] + 1, vector<int>(hi_max + 1, inf));
        }
}

signed main() {
        // 初始化
        memset(ci, 0xc0, sizeof(ci));  // ci初始化为-inf
        // 输入
        cin >> n;
        for (int i = 2; i <= n; i++)  // 父节点为1,故1不需要输入
        {
                cin >> p[i];
                e[p[i]].push_back(i);  // 建树
        }
        for (int i = 1; i <= n; i++) {
                cin >> c[i];
        }
        dfs(1);
}
