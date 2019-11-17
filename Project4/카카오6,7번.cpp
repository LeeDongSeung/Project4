#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using ii = pair<int, int>;
#define sz(v) (int)((v).size())
int N,arr[10];
const int dir[2][4][2] = {
	{{0,0},{-1,0},{0,1},{-1,1}},
{{0,0},{0,-1},{1,1},{1,-1}}
};
const int chk[2][4][2] = {
	{{1,1},{-1,1},{1,0},{-1,0}},
{{1,1},{1,-1},{0,1},{0,-1}}
};
const int dd[2][2] = {
	{0,1},{1,0}
};
const int dy[] = { 1,0,-1,0 };
const int dx[] = { 0,-1,0,1 };
struct INFO {
	int y, x, d,lv;
	INFO() {

	}
	INFO(int y,int x,int d,int lv):y(y),x(x),d(d),lv(lv){}
};
int visited[101][101][2],board[101][101];
inline bool isRange(int y, int x) {
	return !(y < 0 || x < 0 || y >= N || x >= N);
}
int solve(int y, int x) {
	visited[y][x][0] = 1;
	queue<INFO>q;
	q.push({ y,x,0,0 });
	while (!q.empty()) {
		int y = q.front().y, x = q.front().x, d = q.front().d, lv = q.front().lv;
		q.pop();
		int y1 = y + dd[d][0], x1 = x + dd[d][1];
		if ((y == N - 1 && x == N - 1) || (y1 == N - 1 && x == N - 1))return lv;
		//회전!
		for (int i = 0; i < 4; i++) {
			int movy = y + dir[d][i][0], movx = x + dir[d][i][1];
			int chky = y + chk[d][i][0], chkx = x + chk[d][i][1];
			if (isRange(movy, movx) && board[movy][movx] == 0) {
				if (isRange(chky, chkx) && board[chky][chkx] == 0 && visited[movy][movx][!d]) {
					visited[movy][movx][!d] = 1;
					q.push({ movy,movx,!d,lv + 1 });
				}
			}
			movy = y + dy[i], movx = x + dx[i];
			chky = y1 + dy[i], chkx = x1 + dx[i];
			//그대로 이동
			if (isRange(movy, movx) && board[movy][movx]==0) {
				if (isRange(chky, chkx) && board[chky][chkx] == 0) {
					if (visited[movy][movx][d] == 0) {
						visited[movy][movx][d] = 1;
						q.push({ movy,movx,d,lv + 1 });
					}
				}
			}
		}
	}
	return -1;
}
int main(void) {
	freopen("input.txt", "r", stdin);

	return 0;
}