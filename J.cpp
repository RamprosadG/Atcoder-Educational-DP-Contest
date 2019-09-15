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

const int N          = 3e2 + 5;
const ll  Mod        = (ll)1e9 + 7;
const int inf        = (int)2e9;
const ll  Inf        = (ll)1e18;
const int mod        = (int)1e9 + 7;

double p[N][N][N], ev[N][N][N];
int cnt[4];

int solve() {
	int n = in();
	for (int i = 1; i <= n; i++) {
		int x = in();
		cnt[x]++;
	}

	p[cnt[1]][cnt[2]][cnt[3]] = 1.0;

	for (int c = n; c >= 0; c--) {
		for (int b = n; b >= 0; b--) {
			for (int a = n; a >= 0; a--) {

				if((a + b + c == 0) || (a + b + c > n)) continue;

				double waste = (double) (n - (a + b + c)) / n;
			    double waste_ev = waste / (1.0 - waste) + 1.0;
			    ev[a][b][c] += waste_ev * p[a][b][c];

				if (a > 0) {
					double go = (double) a / (a + b + c);
					p[a - 1][b][c] += p[a][b][c] * go;
					ev[a - 1][b][c] += ev[a][b][c] * go;
				}

				if (b > 0) {
					double go = (double) b / (a + b + c);
					p[a + 1][b - 1][c] += p[a][b][c] * go;
					ev[a + 1][b - 1][c] += ev[a][b][c] * go;
				}

				if (c > 0) {
					double go = (double) c / (a + b + c);
					p[a][b + 1][c - 1] += p[a][b][c] * go;
					ev[a][b + 1][c - 1] += ev[a][b][c] * go;
				}
			}
		}
	}

	printf("%.10f\n", ev[0][0][0]);
	
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


