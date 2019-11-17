#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
int K, N, M, L, W;
lint query[100005][3];
struct BETA {
	lint a, b;
	BETA(){
		a = 1;
		b = 15;
	}
	BETA(lint aa, lint bb) :a(aa), b(bb) {

	}
};
inline double getVar(lint a, lint b) {
	//double ret = log(a);
	////to prevent overflow!
	//ret = ret -log(a + b);
	//ret = ret -log(a + b);
	//ret = ret -log (a + b + 1);
	//ret = ret+log(b);
	//return pow(10,ret);
	double ret = log(a);
	ret = ret -log(a + b);
	ret = ret+log(b);
	ret = ret -log(a + b);
	ret = ret -log(a + b + 1);
	return exp(ret);
}
bool vis[100004];
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		lint a, b;
		string str;
		vector<lint>id;
		memset(query, 0, sizeof(query));
		for (int i = 1; i <= N; i++) {
			cin >> a >> str >> b;
			if (str == "imp")query[i][2] = 0;
			else query[i][2] = 1;
			query[i][0] = a, query[i][1] = b;
			id.push_back(a);
		}
		sort(id.begin(), id.end());
		id.erase(unique(id.begin(), id.end()), id.end());
		vector<BETA>arr(sz(id));
		vector<double>S(N + 5, 0.0);
		memset(vis, false, sizeof(vis));
		double all_var_mean = 0.0, all_var = 0.0, all_var_mean_ln = 0.0;
		int vis_cnt = 0;
		for (int i = 1; i <= N; i++) {
			int idx = lower_bound(id.begin(), id.end(), query[i][0]) - id.begin();
			if (vis[idx]) {
				all_var -= getVar(arr[idx].a, arr[idx].b);
			}
			if (vis[idx] == false)vis_cnt++;
			vis[idx] = true;
			if (query[i][2] == 0) {
				arr[idx].b += query[i][1];
			}
			else {
				arr[idx].b -= query[i][1];
				arr[idx].a += query[i][1];
			}
			all_var += getVar(arr[idx].a, arr[idx].b);
			all_var_mean_ln = log(all_var)-log(vis_cnt);
			S[i] = all_var_mean_ln;
		}
		double Smin = (double)1e8, Smax = -(double)1e8;
		//find Smin,Smax!
		for (int i = 1; i <= N; i++) {
			Smin = min(Smin, S[i]), Smax = max(Smax, S[i]);
			//printf("%lf\n", S[i]);
		}
		arr = vector<BETA>(sz(id), BETA(1, 15));
		all_var_mean = 0.0, all_var = 0.0, all_var_mean_ln = 0.0;
		memset(vis, false, sizeof(vis));
		vis_cnt = 0;
		for (int i = 1; i <= N; i++) {
			int idx = lower_bound(id.begin(), id.end(), query[i][0]) - id.begin();
			if (vis[idx]) {
				all_var -= getVar(arr[idx].a, arr[idx].b);
			}
			if (vis[idx] == false)vis_cnt++;
			vis[idx] = true;
			if (query[i][2] == 0) {
				//imp
				arr[idx].b += query[i][1];	
			}
			else {
				//click
				arr[idx].b -= query[i][1];
				arr[idx].a += query[i][1];
			}
			all_var += getVar(arr[idx].a, arr[idx].b);
			all_var_mean_ln = log(all_var) - log(vis_cnt);
			if ((all_var_mean_ln - Smin) <= (Smax - Smin) * 0.05) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}