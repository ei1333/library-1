#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../competitive-template.hpp"
#include "../../prime/fast-factorize.hpp"
#include "../../misc/fastio.hpp"

void solve() {
  int Q;
  rd(Q);
  rep(_, Q) {
    int64_t n;
    rd(n);
    auto prime = factorize(n);
    wt(sz(prime));
    rep(i, sz(prime)) {
      wt(' ');
      wt(prime[i]);
    }
    wt('\n');
  }
}