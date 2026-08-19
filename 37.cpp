/*
从左到右枚举右端点
r，维护一个左端点
l，以及当前区间
[l,r] 中每个质因子的次数。
每次加入
r。

如果当前区间已经能被
k 整除，就不断尝试删除左端点
l。

只要删掉
l 后仍然满足整除条件，就删掉它并令
l 右移。

这样处理后：
若当前
[l,r] 满足条件；
且删掉
l 后不满足条件；
那么所有左端点
1,2,…,l 都可以和
r 组成合法区间。

因为把左端点继续往左移，只会让区间乘积多乘上一些数，不会破坏整除性。

所以此时对答案贡献
l。

如果当前
[l,r] 不满足条件，则贡献
0。
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
vector<int> prime;

class __prime {
public:
	int prime[10];

	__prime(int x) {
		for (int i = 0; i < 10; i++) {
			prime[i]=0;
		}
		for (int i = 0; i < ::prime.size(); i++) {
			if (x % ::prime[i] == 0) {
				int cnt = 0;
				while (x % ::prime[i]==0) {
					cnt++;
					x /= ::prime[i];
				}
				prime[i + 1] = cnt;
			}
		}
	}

	bool operator<(const __prime& other) {
		for (int i = 1; i <= ::prime.size(); i++) {
			if (this->prime[i] < other.prime[i]) {
				return 1;
			}
		}
		return 0;
	}

	bool operator>=(const __prime& other) {
		return !(*this < other);
	}

	__prime operator+=(const __prime& other) {
		for (int i = 1; i <= ::prime.size(); i++) {
			this->prime[i] += other.prime[i];
		}
		return *this;
	}

	__prime operator-=(const __prime& other) {
		for (int i = 1; i <= ::prime.size(); i++) {
			this->prime[i] -= other.prime[i];
		}
		return *this;
	}

	__prime operator+(const __prime& other) {
		__prime tmp = *this;
		tmp += other;
		return tmp;
	}

	__prime operator-(const __prime& other) {
		__prime tmp = *this;
		tmp -= other;
		return tmp;
	}
};

int ans;
int k2;

signed main() {
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	cin >> n >> k;
	k2 = k;
	if (k == 1) {
		cout << n * (n + 1) / 2 << endl;
		return 0;
	}
	for (int i = 2; i * i <= k; i++) {
		if (k % i == 0) {
			prime.push_back(i);
			while (k % i == 0) {
				k /= i;
			}
		}
	}
	if (k > 1) {
		prime.push_back(k);
	}
	__prime p = __prime(k2);
	__prime sum = p;
	for (int i = 1; i <= prime.size(); i++) {
		sum.prime[i] = 0;
	}
	for (int l = 1, r = 1; r <= n; r++) {
		sum += __prime(r);
		while (l < r && sum - __prime(l) >= p) {
			sum-=__prime(l);
			l++;
		}
		if (sum >= p) {
			ans += l;
		}
	}
	cout << ans << endl;
}
