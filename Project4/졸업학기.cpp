#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
int K, N, M, L, W;
const lint INF = (lint)1e18 + 1;
int num_sim_user_topk, num_item_rec_topk, num_reco_users, num_users, num_rows, num_items;
using id = pair<int, double>;
vector<id>adj[301];
vector<int>items;
inline double toNumber(const string& str) {
	int idx = str.find('.');
	double ret = 0.0;
	if (idx == -1) {
		for (int i = 0; i < sz(str); i++) {
			ret = ret * 10.0 + str[i] - '0';
		}
	}
	else {
		for (int i = 0; i < idx; i++) {
			ret = ret * 10.0 + str[i] - '0';
		}
		double dec = 0.0;
		for (int i = sz(str) - 1; i > idx; i--) {
			dec = dec * 0.1 + str[i] - '0';
		}
		dec *= 0.1;
		ret += dec;
	}
	return ret;
}
string str;
double user_mean[301];
double Pearson[301][301];
vector<int>user_item[301];
vector<pair<double, int>>temp_set_U[301];
vector<pair<double, int>>recommend[301];
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string str;
	cin >> num_sim_user_topk >> num_item_rec_topk >> num_users;
	cin >> num_items >> num_rows;
	for (int i = 0; i < num_rows; i++) {
		int a, b;
		cin >> a >> b;
		string str;
		cin >> str;
		adj[a].push_back(id(b, toNumber(str)));
		user_item[a].push_back(b);
		items.push_back(b);
	}
	sort(items.begin(), items.end());
	for (int i = 1; i <= num_users; i++) {
		sort(adj[i].begin(), adj[i].end());
		sort(user_item[i].begin(), user_item[i].end());
	}
	//user_mean 구하고
	for (int i = 1; i <= num_users; i++) {
		double sum = 0.0;
		for (int j = 0; j < adj[i].size(); j++) {
			sum += adj[i][j].second;
		}
		if (adj[i].size())sum /= sz(adj[i]);
		else sum = 0.0;
		user_mean[i] = sum;
	}
	//similarity 구하기
	for (int i = 1; i <= num_users; i++) {
		for (int j = i + 1; j <= num_users; j++) {
			double numer1 = 0.0, deno1 = 0.0, deno2 = 0.0;
			for (int k = 0; k < sz(user_item[i]); k++) {
				if (binary_search(user_item[j].begin(), user_item[j].end(), user_item[i][k])) {
					int idx = lower_bound(user_item[j].begin(), user_item[j].end(), user_item[i][k]) - user_item[j].begin();
					numer1 += (adj[i][k].second - user_mean[i]) * (adj[j][idx].second - user_mean[j]);
					deno1 += (adj[i][k].second - user_mean[i]) * (adj[i][k].second - user_mean[i]);
					deno2 += (adj[j][idx].second - user_mean[j]) * (adj[j][idx].second - user_mean[j]);
				}
			}
			deno1 = sqrt(deno1) * sqrt(deno2);
			if (deno1 != 0.0) {
				//symmetry!
				Pearson[j][i] = Pearson[i][j] = numer1 / deno1;
			}
		}
	}
	for (int i = 1; i <= num_users; i++) {
		for (int j = 1; j <= num_users; j++) {
			if (i == j)continue;
			temp_set_U[i].push_back({ -Pearson[i][j],j });
		}
	}
	for (int i = 1; i <= num_users; i++) {
		sort(temp_set_U[i].begin(), temp_set_U[i].end());
	}
	///for (auto it : temp_set_U[2])printf("%lf %d\n", it.first, it.second);

	for (int u = 1; u <= num_users; u++) {
	
		for (int i = 1; i <= num_items; i++) {
			if (!binary_search(items.begin(), items.end(), i))continue;
			double K = 0.0;
			//이미 추천으로 가지고 있으면 pass
			if (binary_search(user_item[u].begin(), user_item[u].end(), i))continue;
			double sum = 0.0;
			for (int k = 0; k < min(num_sim_user_topk, sz(temp_set_U[u])); k++) {
				double r_prime_item = 0.0;
				int r_prime = temp_set_U[u][k].second;
				if (binary_search(user_item[r_prime].begin(), user_item[r_prime].end(), i)) {
					int idx = lower_bound(user_item[r_prime].begin(), user_item[r_prime].end(), i) - user_item[r_prime].begin();
					r_prime_item = adj[r_prime][idx].second;
					sum += Pearson[u][r_prime] * (r_prime_item - user_mean[r_prime]);
					K += fabs(Pearson[u][temp_set_U[u][k].second]);
				}
			}
			if (K != 0.0)K = 1 / K;
			if (sum != 0.0) {
				sum *= K;
				sum += user_mean[u];
				recommend[u].push_back({ -sum,i });
			}
			else
				recommend[u].push_back({ -user_mean[u],i });
		}
	}
	for (int i = 1; i <= num_users; i++)sort(recommend[i].begin(), recommend[i].end());
	for (int i = 1; i <= num_users; i++) {
		int flag = 1;
		while (flag) {
			flag = 0;
			for (int j = 0; j < sz(recommend[i]); j++) {
				while (j + 1 < sz(recommend[i]) && recommend[i][j].first == recommend[i][j + 1].first) {
					recommend[i].erase(recommend[i].begin() + j + 1);
					flag = 1;
				}
			}
		}
		
	}
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		for (int j = 0; j < num_item_rec_topk; j++) {
			cout << recommend[a][j].second << ' ';
		}
		cout << '\n';
	}
	return 0;
}