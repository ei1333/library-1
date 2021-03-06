#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"

#include "../../competitive-template.hpp"
#include "../../math/elementary-function.hpp"

void solve() {
  ini(N);
  auto factor = PrimeFactors(N);
  vi ans;
  each(p,factor) rep(_,p.second)ans.pb(p.first);
  cout << N << ":";
  each(x,ans)cout<< " " << x;
  cout << endl;
}