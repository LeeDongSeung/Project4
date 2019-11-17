#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
const int MAX_V = 300005;
const int INF = 987654321;
#define sz(v) (int)((v).size())
int N, M, Q, K;

struct segTree {
	int N, Nidx;
	vector<int>tree, lazy;
	segTree(int N) :N(N) {
		int ret = 1;
		while (ret < N)ret *= 2;
		Nidx = ret - 1;
		tree.resize(ret * 2 + 1, 0);
		lazy.resize(ret * 2 + 1, 0);
	}
	void makelazy(int node, int start, int end) {
		if (lazy[node]) {
			if (start != end) {
				lazy[2 * node] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
				tree[2 * node] += lazy[node];
				tree[2 * node + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
		return;
	}
	void update(int s, int e, int val) {
		update(1, 0, Nidx, s, e, val);
		return;
	}
	void update(int node, int start, int end, int l, int r, int val) {
		if (r < start || end < l)return;
		if (l <= start && end <= r) {
			//���� ���ϴ� ������ [l,r]�� ���� �ٶ󺸰� �ִ� ��尡 ������ ���� ��쿡��
			//lazy�� �ɾ��ش�, �׶� ��� ������ ���ؼ� -1�� �ϴ� �翬�� ���� �ִ밪�� tree[node]���� -1�Ѵ�.
			lazy[node] += val;
			tree[node] += val;
			makelazy(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		//�׸��� ������ ��帶�� lazy�� �ɷ� �ִٸ� �̸� �����Ѵ�.
		makelazy(node, start, end);
		update(node * 2, start, mid, l, r, val);
		update(node * 2 + 1, mid + 1, end, l, r, val);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		return;
	}

	void construct(void) {
		for (int i = Nidx; i; i--) {
			tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
		}
	}
	int query(int s, int e) {
		return query(1, 0, Nidx, s, e);
	}
	int query(int node, int start, int end, int l, int r) {
		//lazy�� �����ϰ�!
		makelazy(node, start, end);
		if (r < start || end < l)return 0;
		if (l <= start && end <= r)return tree[node];
		int mid = (start + end) / 2;
		return max(query(node * 2, start, mid, l, r), query(node * 2 + 1, mid + 1, end, l, r));
	}
};
int dx[200002];
vector<int>adj[200002];
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	vector<ii>vec;
	set<int>S;
	map<int, int>mp;
	int num = 0;
	for (int i = 0; i < N; i++) {
		int x0, y0, x1, y1;
		scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
		vec.push_back(ii(y1, y0));
		S.insert(y1), S.insert(y0);
	}
	for (auto it : S)mp[it] = num++;
	segTree seg(num);
	vector<int>first;
	for (int i = 0; i < N; i++) {
		dx[mp[vec[i].first]]++, dx[mp[vec[i].second] + 1]--;
		adj[mp[vec[i].first]].push_back(mp[vec[i].second]);
		first.push_back(mp[vec[i].first]);
	}
	for (int i = 1; i < num; i++)dx[i] += dx[i - 1];
	for (int i = 0; i < num; i++) {
		seg.tree[seg.Nidx + i + 1] = dx[i];
	}
	seg.construct();
	int ans = 0;
	sort(first.begin(), first.end());
	first.erase(unique(first.begin(), first.end()), first.end());
	for (int i :first) {
		for (int j : adj[i]) {
			seg.update(i, j, -1);
		}
		ans = max(ans, dx[i] + seg.query(i+1,num-1));
	}
	printf("%d\n", ans);
	return 0;
}

