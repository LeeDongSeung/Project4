#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N, K;
int sum[11], dp[11][100002];
const int MOD = (int)1e9 + 7;

int main(void) {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	for (int k = 1; k <= K; k++) {
		dp[1][k] = 1;
		sum[1] += 1;
	}
	for (int i = 2; i <= N; i++) {
		for (int k = 1; k <= K; k++) {
			dp[i][k] = sum[i - 1];
			for (int j = k * 2; j <= K; j += k) {
				dp[i][k] = (dp[i][k] - dp[i - 1][j] + MOD) % MOD;
			}
			sum[i] = (sum[i] + dp[i][k]) % MOD;
		}
	}
	cout << sum[N] << '\n';
	return 0;
}
