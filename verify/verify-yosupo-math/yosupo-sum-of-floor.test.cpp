#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#include "../../competitive-template.hpp"
#include "../../math/sum_of_floor.hpp"

void solve() {
  ini(T);
  rep(_, T) {
    inl(N, M, A, B);
    out(sum_of_floor(N, M, A, B));
  }
}