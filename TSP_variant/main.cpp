#include <iostream>
#include <cmath>

using namespace std;

const double INF = 1e18;
const int MX = 11;

int n, m, curr_mask;
double x[MX], y[MX];
double mem1[MX][1 << MX], mem2[MX][1 << MX];
double dist[MX][MX], distTSP[1 << MX];

#define on(x, i) (x & (1 << (i)))

double TSP(int idx, int mask) {
	if (mask == curr_mask)
		return dist[idx][m];
	double& ret = mem1[idx][mask];
	if (ret > -1)
		return ret;
	ret = INF;
	for (int i = 0; i < m; ++i)
		if (on(curr_mask,i) && !on(mask, i))
			ret = min(ret, dist[idx][i] + TSP(i, mask | (1 << i)));
	return ret;
}

double dp(int left_salesmen, int left_points) {
	if (left_salesmen == 1)
		return distTSP[left_points];
	double&ret = mem2[left_salesmen][left_points];
	if (ret > -1)
		return ret;
	ret = INF;
	for (int i = 0; i < (1 << m); ++i)
		if ((left_points | i) == left_points)
			ret = min(ret, max(distTSP[i], dp(left_salesmen - 1, left_points ^ i)));
	return ret;
}

double get_dist(int i, int j) {
	return hypot(x[i] - x[j], y[i] - y[j]);
}

int main() {
	ios::sync_with_stdio(false);
	cout.precision(10);
	cout << fixed;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
		cin >> x[i] >> y[i];
	x[m] = y[m] = 0;
	for (int i = 0; i <= m; ++i)
		for (int j = 0; j <= m; ++j)
			dist[i][j] = get_dist(i, j);
	if (n >= m) {
		double mx_dist = 0;
		for (int i = 0; i < m; ++i)
			mx_dist = max(mx_dist, dist[i][m]);
		cout << mx_dist * 2 << '\n';
		return 0;
	}
	for (int i = 0; i < (1 << m); ++i) {
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k < (1 << m); ++k)
				mem1[j][k] = -10;
		curr_mask = i;
		distTSP[i] = TSP(m, 0);
	}
	for (int i = 0; i <= m; ++i)
		for (int j = 0; j < (1 << (m + 1)); ++j)
			mem2[i][j] = -10;
	cout << dp(n, (1 << m) - 1) << '\n';
	return 0;
}
