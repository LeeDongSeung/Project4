#include <bits/stdc++.h>
using namespace std;

#define sz(v) (int)((v).size())
using lint = long long;
using ii = pair<int, int>;
const int INF = (int)2e9 + 1;
int N, A;
struct Point {
	lint x, y;
	Point(){
		x = 0, y = 0;
	}
	Point(lint x, lint y) :x(x), y(y) {

	}
	bool operator<(const Point& A)const {
		return x != A.x ? x < A.x : y < A.y;
	}
	Point operator-(const Point& A)const {
		return Point(x - A.x, y - A.y);
	}
	lint dot()const {
		return x * x + y * y;
	}
};
double pSum_wdist[100005], pSum[100005];
double Calc(double r,int idx) {
	double ret = -A * r * r;
	ret += pSum[idx] * r;
	ret -= pSum_wdist[idx];
	return ret;
}
int main(void) {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> A;
	vector<pair<Point,lint>>vec(N+2);
	vec[0] = { Point(0,0),0 };
	for (int i = 1; i <= N; i++) {
		lint x, y, w;
		cin >> x >> y >> w;
		vec[i] = {Point( x,y),w };
	}
	vec[N + 1] = { Point(1e3 + 2,1e3 + 2),0 };
	Point origin = Point(0, 0);
	sort(vec.begin()+1, vec.end(), [&origin](const pair<Point, lint>& A, const pair<Point, lint>& B) {
		lint dist1 = (A.first - origin).dot(), dist2 = (B.first - origin).dot();
		return dist1 < dist2;
		});
	for (int i = 1; i <= N; i++) {
		pSum_wdist[i] = pSum_wdist[i - 1] + (double)vec[i].second*sqrt((vec[i].first).dot());
		pSum[i] = pSum[i - 1] + (double)vec[i].second;
	}
	double ans = 0;
	int last = 0;
	for (int here = 1; here <= N; ) {
		last = here;
		while (last<= N && vec[here].first.dot() == vec[last].first.dot())last++;
		double r = pSum[last - 1] / (2 * A);
		if (r >= sqrt(vec[here].first.dot()) && r < sqrt(vec[last].first.dot())) {
			r = r;
		}
		else {
			//vec[last].first.dot()를 포함하지 않아야 하는데 어차피 너무나도 작은 차이니 무시;
			//minimum이 되는 r과 가까운 것을 선택해서 Calc()한다
			double cand = fabs(r - sqrt(vec[here].first.dot()));
			if (cand > fabs(r - sqrt(vec[last].first.dot()))) {
				r = sqrt(vec[last].first.dot());
			}
			else
				r = sqrt(vec[here].first.dot());
		}
		double cand = Calc(r,last-1);
		if (ans < cand)ans = cand;
		here = last;
	}
	printf("%.6lf\n", ans);
	return 0;
}