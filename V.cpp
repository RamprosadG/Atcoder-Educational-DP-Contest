#include<bits/stdc++.h>
using namespace std;

#define ll             long long
#define LL             long long
#define pii            pair<int, int>
#define pll            pair<ll, ll>
#define pil            pair<int, ll>
#define pli            pair<ll, int>
#define vi             vector<int>
#define vl             vector<ll>
#define vii            vector<pii>
#define vll            vector<pll>
#define vil            vector<pil>
#define vli            vector<pli>
#define pb             push_back
#define ppb            pop_back
#define mp             make_pair
#define all_white      first
#define sth_is_black   second
#define sz(x)          (int)x.size()
#define TN             typename
#define all(v)         v.begin(), v.end()
#define fill(a, b)     memset(a, b, sizeof(a))
#define endl           '\n'

template <TN T> T gcd(T a, T b) {return !b ? a : gcd(b, a % b);}
template <TN T> T lcm(T a, T b) {return a * (b / gcd(a, b));}
template <TN T> T sqr(T a) {return a * a;}
template <TN T> T cube(T a) {return a * a * a;}
template <TN T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <TN T> inline void smax(T &a, T b) {a = a > b ? a : b;}

template <TN T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

#define error(args...) {vector <string> _v = split(#args, ','); err(_v.begin(), args); cout << endl;}
vector <string> split(const string &s, char c) {
	vector <string> v;
	stringstream ss(s); string x;
	while (getline(ss, x, c)) v.emplace_back(x);
	return move(v);
}
void err(vector <string> :: iterator it) {}
template <typename T, typename... Args>
void err(vector <string> :: iterator it, T a, Args... args) {
	cout << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << ", ";
	err(++it, args...);
}

inline int in() {int n; scanf("%d", &n); return n;}
inline ll Lin() {ll n; scanf("%lld", &n); return n;}
inline double Din() {double n; scanf("%lf", &n); return n;}

inline int add(int a, int b, int mod) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b, int mod) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod;}

const int N          = 1e5 + 5;
const ll  Mod        = (ll)1e9 + 7;
const int inf        = (int)2e9;
const ll  Inf        = (ll)1e18;

int mod;
vi g[N];
vi child[N];
vii pref[N], suf[N], downs[N];
pii up[N], down[N];

pii merge(const pii& a, const pii& b) {
	pii p;
	p.all_white = mul(a.all_white, b.all_white, mod);
	p.sth_is_black = add(mul(a.sth_is_black, add(b.all_white, b.sth_is_black, mod), mod),
	                     mul(a.all_white, b.sth_is_black, mod), mod);
	return p;
}

pii process(pii p) {
	return {p.all_white, add(p.sth_is_black, p.all_white, mod)};
}

void dfs_one(int u, int parent) {
	pii p = {1, 0};
	for (auto v : g[u]) {
		if (parent != v) {
			child[u].pb(v);
			dfs_one(v, u);
			p = merge(p, down[v]);
			downs[u].pb(down[v]);
		}
	}
	down[u] = process(p);
}

void dfs_two(int u) {
	for (int i = 0; i < sz(child[u]); i++) {
		pii p = {1, 0};
		if (i != 0) {
			p = merge(p, pref[u][i - 1]);
		}
		if (i != sz(downs[u]) - 1) {
			p = merge(p, suf[u][i + 1]);
		}
		if (u != 1) {
			p = merge(p, up[u]);
		}
		int v = child[u][i];
		up[v] = process(p);
		dfs_two(v);
	}
}

int solve() {
	int n = in();
	mod = in();
	for (int i = 0; i < n - 1; i++) {
		int u = in(), v = in();
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs_one(1, -1);
	for (int u = 1; u <= n; u++) {
		int k = sz(downs[u]);
		pii p = {1, 0};
		for (int i = 0; i < k; i++) {
			p = merge(p, downs[u][i]);
			pref[u].pb(p);
		}
		p = {1, 0};
		for (int i = k - 1; i >= 0; i--) {
			p = merge(p, downs[u][i]);
			suf[u].pb(p);
		}
		reverse(all(suf[u]));
	}
	dfs_two(1);
	for (int u = 1; u <= n; u++) {
		pii p = {1, 0};
		if (u != 1) {
			p = merge(p, up[u]);
		}
		if (!child[u].empty()) {
			p = merge(p, pref[u].back());
		}
		p = process(p);
		printf("%d\n", p.sth_is_black);
	}
	return 0;
}

int main() {
	int test = 1, tc = 0;
	//scanf("%d", &test);
	while (test--) {
		//printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}