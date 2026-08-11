#include <bits/stdc++.h>
using namespace std;
int a, b, k;

void solve() {
        cin >> a >> b >> k;
        if (a == b) {
                cout << "Yes\n0";
        }
        if (!(b - a % 9)) {
                cout << "Yes\n1 ";
                cout << (b - a) / 9 << '\n';
                return;
        }
}

int main() {
        freopen("ruka.in", "r", stdin);
        freopen("ruka.out", "w", stdout);
        int n;
        cin >> n;
        while (n--) {
                solve();
        }
}
