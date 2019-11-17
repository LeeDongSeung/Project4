#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N, K;
int sum[50002], dp[2][50002];
const int MOD = (int)1e9 + 7;

int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	for (int k = 1; k <= K; k++) {
		dp[1][k] = 1;
		sum[1] += 1;
	}
	for (int i = 2; i <= N; i++) {
		sum[i % 2] = 0;
		for (int k = 1; k <= K; k++) {
			dp[i%2][k] = sum[(i - 1)%2];
			for (int j = k * 2; j <= K; j += k) {
				dp[i%2][k] = (dp[i%2][k] - dp[(i - 1)%2][j] + MOD) % MOD;
			}
			sum[i%2] = (sum[i%2] + dp[i%2][k]) % MOD;
		}
	}
	cout << sum[N%2] << '\n';
	return 0;
}
