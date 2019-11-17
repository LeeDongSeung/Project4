#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
const int INF =(int)1e9+1;
const int MAX_V = 252;
int N, dp[MAX_V][MAX_V*MAX_V];
int arr[MAX_V][2];
int solve(int here, int capa) {
	if (here == N)return 0;
	int& ret = dp[here][capa];
	if (ret != -1)return ret;
	ret = INF;
	if (capa >= arr[here][0]) {
		ret = min(ret, solve(here + 1, capa - arr[here][0]));
	}
	return ret = min(ret, solve(here + 1, capa)+arr[here][1]);
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		arr[i][0] = a, arr[i][1] = b;
	}
	memset(dp, -1, sizeof(dp));
	int ans = INF;
	for (int i = 0; i < MAX_V * MAX_V; i++) {
		ans = min(ans, max(i, solve(0, i)));
	}
	printf("%d\n", ans);
}