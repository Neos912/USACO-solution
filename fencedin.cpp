#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> ii;
typedef complex<ld> cp;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef vector<cp> vcp;
typedef vector<ld> vld;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<vii> vvii;

#define fastIO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define forw(i,l,r) for( ll i = (l) ; i < (r) ; i++ )
#define forb(i,r,l) for( ll i = (r) ; i >= (l) ; i-- )
#define log2i(x) (32 - __builtin_clz((x)) - 1)
#define log2ll(x) (64 - __builtin_clzll((x)) - 1)
#define Pi 3.141592653589793
#define sz(x) (int)x.size()
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

struct DSU {
  vi p;
  void init(int n) { p = vi(n+1, -1); }
  int get(int x) {
    return (p[x] < 0 ? x : p[x] = get(p[x]));
  }
  bool sameSet(int x, int y) {
    return get(x) == get(y);
  }
  int getSize(int x) {
    return -p[get(x)];
  }
  bool join(int x, int y) {
    if ((x = get(x)) == (y = get(y))) return 0;
    if (p[x] > p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return 1;
  }
};

int A, B, n, m;

int compute(int r, int c){
  return r*m + c;
}

int main() {
  fastIO;

  #ifndef ONLINE_JUDGE
  freopen("fencedin.in", "r", stdin);
  freopen("fencedin.out", "w", stdout);
  #endif // ONLINE_JUDGE

  cin >> A >> B >> n >> m;
  vi a(n+1, 0), b(m+1, 0);
  forw(i, 0, n) cin >> a[i];
  forw(i, 0, m) cin >> b[i];

  sort(all(a));
  sort(all(b));

  forw(i, 0, n)
    a[i] = a[i+1] - a[i];
  a[n] = A - a[n];

  forw(i, 0, m)
    b[i] = b[i+1] - b[i];
  b[m] = B - b[m];

  sort(all(a));
  sort(all(b));

  int vi, hi;
  ll res = 0;
  DSU dsu;
  ++n, ++m;
  dsu.init(n*m);
  for (vi = 0, hi = 0; vi < n || hi < m;) {
    if (hi == m || (vi < n && a[vi] < b[hi])) {
      forw(i, 0, m-1)
        if (dsu.join(compute(vi, i), compute(vi, i+1))) {
          res += a[vi];
        }
      ++vi;
    } else {
      forw(i, 0, n-1)
        if (dsu.join(compute(i+1, hi), compute(i, hi)))
          res += b[hi];
      ++hi;
    }
  }
  cout << res << endl;
}
