#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
const int MOD = (int)1e9 + 7;
const int INF = (int)987654321;
int N, boatpossible, boat;
vector<int> disjoint, notboat;
int dp[1 << 12], boatsize;
inline int bitCount(int num) {
	int ret = 0;
	while (num) {
		if (num % 2)ret += 1;
		num /= 2;
	}
	return ret;
}
inline bool checkhere(int here) {
	for (int i = 0; i < sz(disjoint); i++) {
		if (here == disjoint[i])return false;
	}
	return true;
}
inline bool checknotboat(int cand) {
	for (int i = 0; i < sz(notboat); i++) {
		if (cand == notboat[i])return false;
	}
	return true;
}
int dfs(int here, int there, int turn) {
	if (here == 0) {
		return turn ? 0 : INF;
	}
	//here와 배가 어딨는지를 기억
	int newhere = here | (turn << 10);
	int& ret = dp[newhere];
	if (ret != -1)return ret;
	//재방문 금지!
	ret = INF;
	//현재 강둑에 있으면 안되는 조건이 있다면 return INF;
	if (!checkhere(here) || !checkhere(there))return INF;
	//A turn에서 일단 배를 탈 수 있는 사람이 있어야 하며
	if (!turn && (here & boat)) {
		//부분집합을 traverse
		for (int i = here; i; i = (i - 1) & here) {
			//일단 boatsize보다는 작거나 같아야 하고
			if (bitCount(i) <= boatsize) {
				//i=cand중에 boat를 탈 수 있는 사람이 있어야 한다.
				if ((i & boat) == 0) {
					continue;
				}
				//cand중에서 boat를 같이 탈 수 없는 사람이 있다면 안되고
				if (!checknotboat(i))continue;
				
				ret = min(ret, dfs(here - i, there | i, !turn) + 1);
			}
		}
	}
	if (turn && (there & boat)) {
		for (int i = there; i; i = (i - 1) & there) {
			if (bitCount(i) <= boatsize) {
				if ((i & boat) == 0) {
					continue;
				}
				if (!checknotboat(i))continue;
				ret = min(ret, dfs(here |i, there - i, !turn) + 1);
			}
		}
	}
	return ret;
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &boatsize);
	map<string, int>mp;
	int num = 0;
	int M;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		mp[str] = num++;
	}
	scanf("%d", &boatpossible);
	for (int i = 0; i < boatpossible; i++) {
		string str;
		cin >> str;
		boat |= (1 << mp[str]);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		string str1, str2;
		int cnt, val = 0;
		scanf("%d", &cnt);
		for (int j = 0; j < cnt; j++) {
			cin >> str1;
			val |= (1 << mp[str1]);
		}
		disjoint.push_back(val);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		string str1, str2;
		int cnt, val = 0;
		scanf("%d", &cnt);
		for (int j = 0; j < cnt; j++) {
			cin >> str1;
			val |= (1 << mp[str1]);
		}
		notboat.push_back(val);
	}
	int ans = INF;
	memset(dp, -1, sizeof(dp));
	ans = dfs((1 << (N)) - 1, 0, 0);
	printf("%d", ans == INF ? -1 : ans);
	return 0;
}