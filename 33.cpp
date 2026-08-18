#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Vector {
	int x;
	int y;

	int operator*(const Vector& other) const {
		return (this->x * other.y) - (this->y * other.x);
	}

	Vector operator-(const Vector& other) {
		return {this->x - other.x, this->y - other.y};
	}
};

struct dot {
	int x;
	int y;

	bool operator==(const dot& other) const {
		return (this->x == other.x) && (this->y == other.y);
	}
};

Vector make_Vector(int x, int y) {
	return {x, y};
}

Vector make_vector(dot d) {
	return make_Vector(d.x, d.y);
}

const int N = 5e5 + 10;
dot mp[N];
int n;

signed main() {
	cin >> n;
	srand(time(0));
	for (int i = 1; i <= n; i++) {
		cin >> mp[i].x >> mp[i].y;
	}
	for (int i = 1; i <= 60; i++) {
		dot d1 = mp[(rand()) % n + 1];
		dot d2 = mp[(rand()) % n + 1];
		while (d1 == d2) {
			d2 = mp[(rand()) % n + 1];
		}
#define i j
		int cnt = 2;
		for (int i = 1; i <= n; i++) {
			if (mp[i] == d1 || mp[i] == d2) {
				continue;
			}
			if ((make_vector(d1) - make_vector(mp[i]))
			    * (make_vector(d2) - make_vector(mp[i]))
			    == 0)
			{
				cnt++;
			}
		}
		if (cnt >= (n + 1) / 2) {
			cout << "Yes\n";
			cout << d1.y - d2.y << " ";
			cout << d2.x - d1.x << " ";
			cout << d1.x * d2.y - d1.y * d2.x;
			return 0;
		}
	}
	cout << "No\n";
}
