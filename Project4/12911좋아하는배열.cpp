#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N, K;
int dp[10002],arr[10002];
string str;
inline int func(int a, int b) {
	/*int same = 1, first = arr[a];
	for (int i = a + 1; i <= b; i++) {
		if (first != arr[i])same = 0;
	}
	if (same)return 1;
	int diff = arr[a + 1] - arr[a], prog = 1;
	for (int i = a + 2; i <= b; i++) {
		if (arr[i] - arr[i - 1] != diff)prog = 0;
	}
	if (prog) {
		if (abs(diff) == 1)return 2;
		else return 5;
	}
	int alter = 1;
	for (int i = a+2; i <= b; i++) {
		if (arr[i] != arr[i -2])alter = 0;
	}
	if (alter)return 4;
	return 10;*/
	string M = str.substr(a, b - a + 1);
	if (M == string(sz(M), M[0]))return 1;
	bool progressive = true;
	for (int i = 0; i + 1 < sz(M); i++) {
		if (M[i + 1] - M[i] != M[1] - M[0])progressive = false;
	}
	if (progressive && abs(M[1] - M[0]) == 1)return 2;
	bool alternating = true;
	for (int i = 0; i < sz(M); i++) {
		if (M[i] != M[i % 2])alternating = false;
	}
	if (alternating)return 4;
	if (progressive)return 5;
	return 10;
}
int solve(int here) {
	if (here == N)return 0;
	int& ret = dp[here];
	if (ret != -1)return ret;
	ret = INF;
	for (int i = 3; i <= 5; i++) {
		if (here + i <= N)ret = min(ret, solve(here + i) + func(here, here + i - 1));
	}
	return ret;
}
int num_rows_rec_topk, num_cols_rec_topk;
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while (T--) {
		cin >> str;
		N = sz(str);
		memset(dp, -1, sizeof(dp));
		cout << solve(0) << '\n';
	}
	return 0;
}
