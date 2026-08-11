/*
对于n次询问
每次统计所有gcd(x,y)=k(a<=x<=b,c<=y<=d)的二元组的个数
即为统计 (a/k)<=x <=(b/k) , (c/k) <= y <= (d/k)的 gcd(x,y)=1的二元组的数量
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int k, a, b, c, d, n, u[N], cnt_prime[N], g[N];
bool is_prime[N];

int f(int n, int m) {
        long long ans = 0;
        int l = 1, r;
        while (l <= min(n, m)) {
                r = min(n / (n / l), m / (m / l));
                r = min(r, n);
                ans += (g[r] - g[l - 1]) * (n / l) * (m / l);
                l = r + 1;
        }
        return ans;
}

int fast_mod(int a, int b) {
        int sum = 1;
        while (b) {
                if (b & 1) {
                        sum *= a;
                }
                a *= a;
                b >>= 1;
        }
        return sum;
}

void init() {
        memset(u, -1, sizeof(u));
        u[1] = 1;
        g[1] = 1;
        for (int i = 2; i < N; i++) {
                if (!is_prime[i]) {
                        u[i] = -1;
                        for (int j = 2; i * j <= N; j++) {
                                is_prime[i * j] = 1;
                                cnt_prime[i * j]++;
                                if (!(j % i)) {
                                        u[i * j] = 0;
                                }
                        }
                } else if (u[i] != 0) {
                        u[i] = fast_mod(-1, cnt_prime[i]);
                }
                g[i] = g[i - 1] + u[i];
        }
}

void solve() {
        cin >> a >> b >> c >> d >> k;
        cout
                << f(b / k, d / k)
                - f((a - 1) / k, d / k)
                - f(b / k, (c - 1) / k)
                + f((a - 1) / k, (c - 1) / k)
                << endl;
        ;
}

int main() {
        init();
        cin >> n;
        while (n--) {
                solve();
        }
}
