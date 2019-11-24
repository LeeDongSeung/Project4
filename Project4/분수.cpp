#include <bits/stdc++.h>
using namespace std;

#define sz(v) (int)((v).size())
using lint = unsigned long long;
using ii = pair<int, int>;
const int INF = (int)2e9 + 1;
int A, B;
//(A*n)%B
lint addmod(lint A,lint n, lint B) {
	lint ret = 0;
	while (n) {
		if (n % 2)ret = (ret + A) % B;
		A = (A + A) % B;
		n /= 2;
	}
	return ret;
}
//(A^n)%B
lint powmod(lint A, lint n, lint B) {
	lint ret = 1;
	while (n) {
		if (n % 2)ret = addmod(ret, A, B);
		A = addmod(A, A, B);
		n /= 2;
	}
	return ret;
}
lint solve(lint A, lint B, lint k) {
	//10^k
	lint ret = powmod(10, k, B);
	//ret*A
	ret =addmod(ret, A, B);
	//ret*10
	return ret*10 / B;
}
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while (T--) {
		cin >> A >> B;
		int I, N;
		cin >> I >> N;
		I--;
		for (int i = 0; i < N; i++) {
			cout << solve(A, B, I + i);
		}
		cout << '\n';
	}
	return 0;
}