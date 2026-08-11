#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
vector<int> e[N];
int n, m, s;
int st[N][710];
vector<int> dfn;
int lg[N];
int p[N];
void dfs(int x, int fa)
{
	dfn.push_back(x);
	for (int v : e[x])
	{
		if (v == fa)
		{
			continue;
		}
		dfs(v, x);
		dfn.push_back(x);
	}
}
int main()
{
	cin >> n >> m >> s;
	lg[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		lg[i] = lg[i / 2] + 1;
	}
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(s, -1);
	memset(st, 0x3f, sizeof(st));
	for (int i = 1; i < n; i++)
	{
		st[i][0] = min(dfn[i + 1], dfn[i]);
	}
	for (int len = 1; len <= lg[n]; len++)
	{
		for (int i = 1; i <= n - (1 << len); i++)
		{
			st[i][len] = min(st[st[i][len - 1]][len - 1], st[i][len - 1]);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		
	}
}