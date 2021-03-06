#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../competitive-template.hpp"
#include "../../graph/graph-utility.hpp"
#include "../../graph/strongly-connected-components.hpp"

void solve() {
  ini(N, M);
  auto g = graph(N, M, true, false);
  StronglyConnectedComponents<vvi> scc(g);
  out(scc.dag.size());
  rep(i, scc.dag.size()) {
    cout << scc.belong(i).size() << " ";
    out(scc.belong(i));
  }
}