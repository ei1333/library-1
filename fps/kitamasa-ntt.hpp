#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../ntt/ntt-avx2.hpp"
#include "formal-power-series.hpp"

template <typename mint>
mint LinearRecursionFormula(long long k, FormalPowerSeries<mint> Q,
                            FormalPowerSeries<mint> P) {
  NTT<mint> ntt;
  mint ret = 0;

  P.shrink();
  Q.shrink();
  if (P.size() >= Q.size()) {
    auto R = P / Q;
    P -= R * Q;
    if (k < (int)R.size()) ret += R[k];
  }
  P.shrink();
  if ((int)P.size() == 0) return ret;

  int N = 1;
  while (N < (int)Q.size()) N <<= 1;

  vector<mint> F(2 * N), G(2 * N);
  for (int i = 0; i < (int)P.size(); i++) F[i] = P[i];
  for (int i = 0; i < (int)Q.size(); i++) G[i] = Q[i];
  ntt.ntt(F);
  ntt.ntt(G);
  vector<mint> S(2 * N), T(2 * N);

  vector<int> btr(N);
  for (int i = 0, logn = __builtin_ctz(N); i < (1 << logn); i++) {
    btr[i] = (btr[i >> 1] >> 1) + ((i & 1) << (logn - 1));
  }
  mint dw = mint(ntt.pr).inverse().pow((mint::get_mod() - 1) / (2 * N));

  while (k) {
    mint inv2 = mint(2).inverse();
    // G(x)G(-x)の偶数次
    T.resize(N);
    for (int i = 0; i < N; i++) T[i] = G[(i << 1) | 0] * G[(i << 1) | 1];

    S.resize(N);
    if (k & 1) {
      // P(x)Q(-x)の奇数次
      for (auto &i : btr) {
        S[i] = (F[(i << 1) | 0] * G[(i << 1) | 1] -
                F[(i << 1) | 1] * G[(i << 1) | 0]) *
               inv2;
        inv2 *= dw;
      }
    } else {
      // P(x)Q(-x)の偶数次
      for (int i = 0; i < N; i++) {
        S[i] = (F[(i << 1) | 0] * G[(i << 1) | 1] +
                F[(i << 1) | 1] * G[(i << 1) | 0]) *
               inv2;
      }
    }

    swap(F, S);
    swap(G, T);
    ntt.ntt_doubling(F);
    ntt.ntt_doubling(G);
    k >>= 1;
  }

  mint f0 = 0;
  for (auto Fi : F) f0 += Fi;
  f0 *= mint((int)F.size()).inverse();
  return ret + f0;
}

template <typename mint>
mint kitamasa(long long N, FormalPowerSeries<mint> Q,
              FormalPowerSeries<mint> a) {
  int k = Q.size() - 1;
  assert((int)a.size() == k);
  FormalPowerSeries<mint> P = a * Q;
  P.resize(Q.size() - 1);
  return LinearRecursionFormula<mint>(N, Q, P);
}