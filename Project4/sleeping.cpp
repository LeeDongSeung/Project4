#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
const int MAX_V = 100000;
const int INF = 987654321;
int N, L, rf, rb;
int arr[100002];
int solve() {
	if (arr[N - 1] - arr[1] == N - 2 && arr[1] - arr[0] > 2)return 2;
	if (arr[N - 2] - arr[0] == N - 2 && arr[N - 1] - arr[N - 2] > 2)return 2;
	int window = 0;
	for (int i = 0, j = 0; i < N; i++) {
		while (j +1< N && arr[j + 1] - arr[i] <= N - 1)j++;
		window = max(window, j - i + 1);
	}
	return N - window;
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)scanf("%d", &arr[i]);
	sort(arr, arr + N);
	int max_n = max(arr[N - 2] - arr[0], arr[N - 1] - arr[1]) - (N - 2);
	
	printf("%d\n%d\n", solve(), max_n);
	return 0;
}