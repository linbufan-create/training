#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
int n;
string s;
int q;
constexpr int N = 5e5 + 10;
int hash_val[N];
constexpr int mod = 1e9 + 7;
constexpr int base = 131;
vector<int> prime;
bool is_prime[N];
int vis[N];

int fast_mod(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) {
			sum = sum * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return sum;
}

void get_hash() {
	int sum = 0;
	for (int i = 0; i < s.size(); i++) {
		sum = (sum * base + s[i]) % mod;
		hash_val[i] = sum;
	}
}

int get_sub_hash(int l, int r) {
	if (l > r) {
		return 0;
	}
	if (l == 0) {
		return hash_val[r];
	}
	return (hash_val[r] + mod - (hash_val[l - 1] * fast_mod(base, r - l + 1) % mod)) % mod;
}

void init() {
	for (int i = 2; i <= n; i++) {
		if (!is_prime[i]) {
			prime.push_back(i);
			vis[i]=i;
		}
		for (int j : prime) {
			if (i * j > n) {
				break;
			}
			is_prime[i * j] = 1;
			vis[i * j] = j;
			if (i % j == 0) {
				break;
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> s >> q;
	get_hash();
	init();
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		int len = r - l + 1;
		int j = len;
		int ans = len;
		while (j > 1) {
			int p = vis[j];
			while (ans
			       % p
			       == 0
			       && get_sub_hash(l, r - ans / p)
			       == get_sub_hash(l + ans / p, r))
			{
				ans /= p;
			}
			while (j % p == 0) {
				j /= p;
			}
		}
		cout << ans << '\n';
	}
}
