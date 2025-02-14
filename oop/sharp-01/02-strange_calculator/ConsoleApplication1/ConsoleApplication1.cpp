#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;

vector<ll> a, b, c;
vector<vector<vector<ll>>> d;

bool corr()
{
	vector<ll> ax, ay;
	ll i;
	for (i = 0; i < 3; i++) {
		ll j;
		for (j = 0; j < 3; j++) {
			if (i == j)
				continue;
			ll k;
			for (k = 0; k < 4; k++) {
				ax.push_back(d[i][k][0]);
				ax.push_back(d[j][k][0]);
				ay.push_back(d[i][k][1]);
				ay.push_back(d[j][k][1]);
			}
			vector<pair<ll, ll>> pt;
			for (ll x : ax) {
				for (ll y : ay) {
					ll imix = min(d[i][0][0], d[i][2][0]);
					ll imxx = max(d[i][0][0], d[i][2][0]);
					ll imiy = min(d[i][0][1], d[i][2][1]);
					ll imxy = max(d[i][0][1], d[i][2][1]);

					ll jmix = min(d[j][0][0], d[j][2][0]);
					ll jmxx = max(d[j][0][0], d[j][2][0]);
					ll jmiy = min(d[j][0][1], d[j][2][1]);
					ll jmxy = max(d[j][0][1], d[j][2][1]);

					if (imix <= x && x <= imxx && imiy <= y && y <= imxy
						&& jmix <= x && x <= jmxx && jmiy <= y && y <= jmxy)
						pt.push_back({x, y});
				}
			}
			sort(pt.begin(), pt.end());
			pt.erase(unique(pt.begin(), pt.end()), pt.end());
			//cout << "cnt: " << pt.size() << '\n';
			if (pt.size() > 2)
				return 0;
		}
	}

	for (i = 0; i < 3; i++) {
		ll k;
		for (k = 0; k < 3; k++) {
			if (k == i)
				continue;
			vector<pair<ll, ll>> f, s;
			ll j;
			for (j = 0; j < 4; j++) {
				f.push_back({d[i][j][0], d[i][j][1]});
				s.push_back({d[k][j][0], d[k][j][1]});
			}
			sort(f.begin(), f.end());
			sort(s.begin(), s.end());
			if (f == s)
				return 0;
		}
	}

	return 1;
}

void sh()
{
	ll i;
	for (i = 0; i < 3; i++) {
		ll j;
		for (j = 0; j < 4; j++) {
			ll k;
			for (k = 0; k < 2; k++)
				cout << d[i][j][k] << ' ';
			cout << '\n';
		}
		cout << '\n';
	}
}

ll f()
{
	d[0][0] = {0, 0};
	d[0][1] = {0, b[c[0]]};
	d[0][2] = {a[c[0]], b[c[0]]};
	d[0][3] = {a[c[0]], 0};
	ll i;
	ll mi = 3e18;
	for (i = 0; i < 4; i++) {
		d[1][0] = d[0][i];
		ll j;
		for (j = 0; j < 4; j++) {
			ll k;
			for (k = 0; k < 2; k++) {
				ll dx = a[c[1]];
				ll dy = b[c[1]];
				if (k % 2 == 1)
					swap(dx, dy);
				if ((j >> 0) & 1)
					dx = -dx;
				if ((j >> 1) & 1)
					dy = -dy;
				d[1][1] = {d[1][0][0], d[1][0][1] + dy};
				d[1][2] = {d[1][0][0] + dx, d[1][0][1] + dy};
				d[1][3] = {d[1][0][0] + dx, d[1][0][1]};

				ll h;
				for (h = 0; h < 2; h++) {
					auto &cur = d[2];
					ll w;
					for (w = 0; w < 4; w++) {
						cur[0] = d[h][w];
						ll o;
						for (o = 0; o < 4; o++) {
							ll m;
							for (m = 0; m < 2; m++) {
								ll cx = a[c[2]];
								ll cy = b[c[2]];
								if (m % 2 == 1)
									swap(cx, cy);
								if ((o >> 0) & 1)
									cx = -cx;
								if ((o >> 1) & 1)
									cy = -cy;
								cur[1] = {cur[0][0], cur[0][1] + cy};
								cur[2] = {cur[0][0] + cx, cur[0][1] + cy};
								cur[3] = {cur[0][0] + cx, cur[0][1]};
								if (!corr())
									continue;
								ll mix = 1e10;
								ll miy = 1e10;
								ll mxx = -1e10;
								ll mxy = -1e10;
								ll g;
								for (g = 0; g < 3; g++) {
									ll l;
									for (l = 0; l < 4; l++) {
										mix = min(mix, d[g][l][0]);
										miy = min(miy, d[g][l][1]);
										mxx = max(mxx, d[g][l][0]);
										mxy = max(mxy, d[g][l][1]);
									}
								}
								ll curs = abs((mix-mxx)*(miy-mxy));
								//cout << "curs: " << curs << '\n';

								//if (curs == 1)
								//cout << mix << ' ' << miy << ' ' << mxx << ' ' << mxy << '\n';
								mi = min(mi, curs);
							}
						}
					}
				}
			}
		}
	}
	return mi;
}

void solve()
{
	ll i;

	a.resize(3);
	b.resize(3);
	c.resize(3);
	d.resize(3);
	for (i = 0; i < 3; i++)
		cin >> a[i] >> b[i];
	iota(c.begin(), c.end(), 0);
	ll mi = 3e18;
	//do {
		for (i = 0; i < 3; i++)
			d[i].assign(4, {});
		ll curf = f();
		mi = min(mi, curf);
	//} while (next_permutation(c.begin(), c.end()));
	cout << mi << '\n';
}

int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(0);
	cout << fixed << setprecision(9);

	ll t;
	//t = 1;
	cin >> t;
	while (t--)
		solve();
}