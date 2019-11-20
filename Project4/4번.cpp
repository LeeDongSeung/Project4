#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N, K;
const int MOD = (int)1e9 + 7;
struct segTree {
	int N, Nidx;
	vector<int>tree;
	segTree(int N) :N(N){
		int ret = 1;
		while (ret < N)ret *= 2;
		Nidx = ret - 1;
		tree.resize(ret * 2 + 1, INF);
	}
	void construct() {
		for (int i = 0; i < N; i++)tree[Nidx + i + 1] = i;
		for (int i = Nidx; i; i--) {
			tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
		}
	}
	void update(int pos, int val) {
		pos += Nidx + 1;
		tree[pos] = val;
		pos /= 2;
		while (pos) {
			tree[pos] = min(tree[pos * 2], tree[pos * 2 + 1]);
			pos /= 2;
		}
	}
	int query(int start, int end) {
		start += Nidx + 1, end += Nidx + 1;
		int ret = INF;
		while (start <= end) {
			if (start % 2)ret = min(ret, tree[start]);
			if (end % 2 == 0)ret = min(ret, tree[end]);
			start = (start + 1) / 2, end = (end - 1) / 2;
		}
		return ret;
	}
};
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	map<lint, int>mp;
	vector<lint>vec;
	for (int i = 0; i < N; i++) {
		lint a;
		cin >> a;
		vec.push_back(a);
		mp[a] += 1;
	}
	vector<lint>arr;
	lint last = (*mp.begin()).first;
	for (auto it = mp.begin(); it != mp.end(); it++) {
		auto jt = it;
		jt++;
		int cnt = it->second;
		for (int i = 0; i < cnt; i++) {
			arr.push_back(last + i);
		}
		if (jt == mp.end()) {
			break;
		}
		if (last + it->second - 1 < jt->first)last = jt->first;
		else last += it->second;
	}
	//for (lint a : arr)cout << a << '\n';
	segTree seg(N + 2);
	seg.construct();
	for (int i = 0; i < sz(vec); i++) {
		int idx = lower_bound(arr.begin(), arr.end(), vec[i]) - arr.begin();
		if (seg.tree[seg.Nidx + 1 + idx] == INF) {
			int ret = seg.query(idx + 1, N + 2);
			cout << arr[ret] << " ";
			seg.update(ret, INF);
		}
		else {
			cout << arr[idx] << " ";
			seg.update(idx, INF);
		}
	}
	return 0;
}