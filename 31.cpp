#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node {
	int x, y;
	int con;
	int step;

	bool operator<(const node other) {
		return (this->x + this->y) < (other.x + other.y);
	}
};

int h, w, d, r;
const int N = 2e3 + 10;
char mp[N][N];
int vis[N][N][2];

bool check(int x, int y, int con) {
	if (x > h || y > w) {
		return 0;
	}
	if (x < 1 || y < 1) {
		return 0;
	}
	if (con == 1 && mp[x][y] == '~') {
		return 0;
	}
	if (mp[x][y] == '#') {
		return 0;
	}
	if (vis[x][y][con]) {
		return 0;
	}
	return 1;
}

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void bfs() {
	deque<node> q;
	q.push_back({1, 1, 0, 0});
	while (!q.empty()) {
		node now = q.front();
		q.pop_front();
		int x = now.x;
		int y = now.y;
		int con = now.con;
		int step = now.step;
		if (x == h && y == w) {
			cout << step << endl;
			return;
		}
		if (con == 0 && check(x + d, y + r, 1)) {
			q.push_back({x + d, y + r, 1, step + 1});
		}
	nxt:
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (check(nx, ny, con)) {
				if (mp[nx][ny] == '~') {
					q.push_front({nx, ny, con, step});
				} else {
					q.push_back({nx, ny, con, step + 1});
				}
				vis[nx][ny][con] = 1;
			}
		}
	}
	cout << -1 << endl;
	return;
}

signed main() {
	freopen("big.in", "r", stdin);
	freopen("big.out", "w", stdout);
	cin >> h >> w >> d >> r;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> mp[i][j];
		}
	}
	// cout<<-1<<endl;
	// return 0;
	bfs();
}
