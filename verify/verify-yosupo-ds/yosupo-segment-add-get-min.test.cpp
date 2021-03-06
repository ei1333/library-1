#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include "../../competitive-template.hpp"
#include "../../segment-tree/li-chao-tree.hpp"

void solve() {
  ini(N, Q);
  vl a(N), b(N), l(N), r(N);
  in4(l, r, a, b);
  vl c(Q), d(Q), e(Q), f(Q), g(Q);
  vl xs;
  rep(i, Q) {
    in(c[i]);
    if (c[i])
      in(d[i]), xs.pb(d[i]);
    else
      in(d[i], e[i], f[i], g[i]);
  }
  xs.pb(-inf);
  xs.pb(inf);
  LiChaoTree<ll, infLL> lichao(xs);
  rep(_, N) lichao.update_segment(a[_], b[_], l[_], r[_] - 1);

  rep(i, Q) {
    if (c[i]) {
      ll ans = lichao.query(d[i]);
      if (ans == infLL)
        out("INFINITY");
      else
        out(ans);
    } else {
      lichao.update_segment(f[i], g[i], d[i], e[i] - 1);
    }
  }
}