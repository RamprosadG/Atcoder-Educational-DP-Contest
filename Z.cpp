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

struct CHT_INC_MIN {
	vl m, b;

	bool bad(int f1, int f2, int f3) {
		return 1.0 * (b[f2] - b[f1]) * (m[f1] - m[f3]) <= 1.0 * (b[f3] - b[f1]) * (m[f1] - m[f2]);
	}

	void add(ll M, ll B) {
		m.pb(M), b.pb(B);
		int sz = (int)m.size();
		while (sz >= 3 && bad(sz - 3, sz - 2, sz - 1)) {
			m.erase(m.end() - 2);
			b.erase(b.end() - 2);
			sz--;
		}
	}

	ll f(int idx, ll X) {
		return m[idx] * X + b[idx];
	}

	ll query(ll X) {
		int low = 0, high = (int) m.size() - 1;
		while (high - low >= 5) {
			int mid1 = (low + low + high) / 3;
			int mid2 = (low + high + high) / 3;
			if (f(mid1, X) >= f(mid2, X)) {
				low = mid1 + 1;
			} else {
				high = mid2 - 1;
			}
		}
		ll res = f(low, X);
		for (int i = low + 1; i <= high; i++) {
			res = min(res, f(i, X));
		}
		return res;
	}
};

int solve() {
	int n = in();
	ll C = Lin();
	CHT_INC_MIN dp;
	vl h(n);
	for (int i = 0; i < n; i++) {
		h[i] = Lin();
	}
	dp.add(h[0], h[0] * h[0]);
	ll ans;
	for (int i = 1; i < n; i++) {
		ans = dp.query(-2LL * h[i]) + h[i] * h[i] + C;
		dp.add(h[i], h[i] * h[i] + ans);
	}
	printf("%lld\n", ans);
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