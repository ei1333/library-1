#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

#include "../../competitive-template.hpp"
#include "../../shortest-path/dijkstra.hpp"

void solve() {
  ini(N, E, S);
  auto g = wgraph<int>(N, E, true, false);
  auto d = dijkstra<int>(g, S);
  each(x, d) {
    if (x > TEN(9))
      out("INF");
    else
      out(x);
  }
}