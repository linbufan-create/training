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
#define  int long long
using namespace std;
int n, k;

class __prime {
public:
	vector<pair<int, int>> prime;

	__prime(vector<pair<int, int>> dat) {
		prime = dat;
	}

	__prime(int x) {
		vector<pair<int, int>> data;
		for (int i = 2; i * i <= x; i++) {
			if (x % i == 0) {
				int cnt = 0;
				while (x % i == 0) {
					cnt++;
					x /= i;
				}
				data.push_back({i, cnt});
			}
		}
		if (x > 1) {
			data.push_back({x, 1});
		}
		prime = data;
	}

	__prime operator-(const __prime& other) const {
		vector<pair<int, int>> th = this->prime, oth = other.prime;
		for (auto& p1 : th) {
			for (auto p2 : oth) {
				if (p1.first == p2.first) {
					p1.second -= p2.second;
				}
			}
		}
		return th;
	}

	__prime operator+(const __prime& other) {
		vector<pair<int, int>> th = this->prime, oth = other.prime;
		for (auto& p1 : th) {
			for (auto p2 : oth) {
				if (p1.first == p2.first) {
					p1.second += p2.second;
				}
			}
		}
		return th;
	}

	bool operator<(const __prime& other) const {
		bool big = 0;
		for (auto p : other.prime) {
			bool can = 0;
			for (auto p2 : this->prime) {
				if (p.first == p2.first) {
					can = 1;
					if (p.second > p2.second) {
						big = 1;
					}
				}
			}
			if (!can) {
				return 0;
			}
		}
		return big;
	}

	bool operator>=(const __prime& other) const {
		bool big = 0;
		for (auto p : other.prime) {
			bool can = 0;
			for (auto p2 : this->prime) {
				if (p.first == p2.first) {
					can = 1;
					if (p.second > p2.second) {
						big = 1;
					}
				}
			}
			if (!can) {
				return 1;
			}
		}
		return !big;
	}

	void operator+=(const __prime& other) {
		*this = *this + other;
	}

	void operator-=(const __prime& other) {
		*this = *this - other;
	}
};

int ans;

signed main() {
	freopen("num.in", "r", stdin);
	freopen("num.out","w",stdout);
	cin >> n >> k;
	if (k == 1) {
		cout << n * (n + 1) / 2 << endl;
		return 0;
	}
	__prime p = __prime(k);
	__prime sum = (k);
	for (auto& p : sum.prime) {
		p.second = 0;
	}
	for (int l = 1, r = 1; r <= n; r++) {
		sum += __prime(r);
		while (sum - __prime(l) >= p) {
			sum -= __prime(l);
			l++;
		}
		if (sum >= p) {
			ans += l;
		}
	}
	cout << ans << endl;
}
