#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N,K;
int dp[11][100002];
const int MOD = (int)1e9 + 7;
int solve(int here, int k) {
	if (here == N)return 1;
	int& ret = dp[here][k];
	if (ret != -1)return ret;
	ret = 0;
	for (int i = 1; i <= K; i++) {
		if (here==0||(k <= i || k % i))ret = (ret + solve(here + 1, i)) % MOD;
	}
	return ret;
}
int main(void){
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	memset(dp, -1, sizeof(dp));
	cin >> N >> K;
	cout << solve(0, 0) << '\n';
	return 0;
}
