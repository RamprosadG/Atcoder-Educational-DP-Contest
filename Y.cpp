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
#define ff             first
#define ss             second
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

const int N          = 2e5 + 5;
const ll  Mod        = (ll)1e9 + 7;
const int inf        = (int)2e9;
const ll  Inf        = (ll)1e18;
const int mod        = (int)1e9 + 7;

int fac[N], inv_fac[N];

int bigmod(int a, int b, int c) {
	if (b == 0) return 1;
	int x = bigmod(a, b / 2, c);
	x = mul(x, x, c);
	if (b & 1) x = mul(x, a, c);
	return x;
}

int inv_mod(int a, int c) {
	return bigmod(a, c - 2, c);
}

int binomial(int n, int r) {
	if (n < 0 || r < 0 || n < r) return 0;
	return mul(fac[n], mul(inv_fac[r], inv_fac[n - r], mod), mod);
}

int f(int a, int b) {
	return binomial(a + b, b);
}

int solve() {
	fac[0] = inv_fac[0] = 1;
	for (int i = 1; i <= 2e5 + 2; i++) {
		fac[i] = mul(fac[i - 1], i, mod);
		inv_fac[i] = inv_mod(fac[i], mod);
	}
	int h = in(), w = in(), n = in();
	vii a(n);
	for (int i = 0; i < n; i++) {
		a[i].ff = in(), a[i].ss = in();
	}
	sort(all(a), [&](pii a, pii b) {
		return a.ff + a.ss < b.ff + b.ss;
	});
	vi dp(n + 1);
	a.push_back({h, w});
	for (int i = 0; i <= n; i++) {
		int cur = f(a[i].ff - 1, a[i].ss - 1);
		for (int j = 0; j < i; j++) {
			if (a[j].ff <= a[i].ff && a[j].ss <= a[i].ss) {
				cur = sub(cur, mul(dp[j], f(a[i].ff - a[j].ff, a[i].ss - a[j].ss), mod), mod);
			}
		}
		dp[i] = cur;
	}
	printf("%d\n", dp[n]);
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



