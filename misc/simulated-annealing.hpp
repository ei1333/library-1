#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "rng.hpp"
#include "timer.hpp"

namespace Simulated_Annealing {
// exp高速化用のlogテーブル
// exp(d/T) > rng()  <=>  d > T * log(rng)を使い前計算
struct gen_log {
  double l[65536];
  constexpr gen_log() : l() {
    unsigned long long x = 88172645463325252ULL;
    double log_u64max = log(2) * 64;
    for (int i = 0; i < 65536; i++) {
      x = x ^ (x << 7);
      x = x ^ (x >> 9);
      l[i] = log(double(x)) - log_u64max;
    }
  }
} constexpr rnd_log;

// 時間
double start_time = 0;
constexpr double end_time = 2900;
double inv_time = 1.0 / (end_time - start_time);
double cur_time = 0;

// 温度 開始温度は実行時に渡す
constexpr double end_temp = 1;
double cur_temp;

void set_time(double start) {
  start_time = start;
  inv_time = 1.0 / (end_time - start_time);
  cur_time = start_time;
}

void set_temp(double startTemp) {
  cur_temp =
      end_temp + (startTemp - end_temp) * (end_time - cur_time) * inv_time;
}

// スコア
using score_t = long long;
score_t score = 0, diff = 0;
// 遷移のパターン用の変数
int mode = 0;

void input();
void output();
void init();
void set_state(int);
void calc_diff();
void update();
void undo();

// 実行
score_t simulated_annealing(double startTemp, Timer *timer = nullptr,
                         bool is_tuning = false) {
  // タイマーの設定
  if (timer == nullptr) timer = new Timer();
  //チューニング時はタイマーをリセット
  if (is_tuning) timer->reset();

  // スコアの初期化
  score = diff = 0;

  // 初期解の構築
  init();

  // 焼きなまし関連のconstでない変数の初期化
  set_time(timer->elapsed());
  set_temp(startTemp);

  // イテレーションの回数
  int iter = 0;
  while (true) {
    // 256回に1回、時間と温度を更新する
    if ((++iter & 0xFF) == 0) {
      if ((cur_time = timer->elapsed()) > end_time) break;
      set_temp(startTemp);
    }

    // 次の遷移を設定
    set_state(iter);

    // 差分を計算
    calc_diff();

    // 条件を満たしたときに遷移を採用
    if (double(diff) > cur_temp * rnd_log.l[iter & 0xFFFF])
      // スコアと状態を更新
      update();
    else
      undo();

// デバッグ用に 65536 iteration毎に出力
#ifdef NyaanDebug
    if (!is_tuning and (iter & 0xFFFF) == 0) {
      cerr << cur_time << "\t" << iter << "\t" << score << endl;
    }
#endif
  }
// 結果を出力
#ifdef NyaanDebug
  cerr << iter << "\t" << score << endl;
#endif
  return score;
}

// 実行用
void run(double temp) {
  Timer timer;
  input();
  simulated_annealing(temp, &timer);
  output();
  return;
}

// テスト用
void test(const vector<string> &filenames, double temp, int loop = 1) {
  double result = 0.0;
  Timer timer;
  for (int i = 0; i < loop; i++) {
    for (auto &filename : filenames) {
      cerr << filename << "\t" << temp << "\t";
      ifstream is(filename);
      cin.rdbuf(is.rdbuf());
      input();
      simulated_annealing(temp, &timer, true);
      result += score;
    }
  }
  result /= 1.0 * loop * filenames.size();
  cerr << "result : " << result << endl;
}

}  // namespace Simulated_Annealing
namespace SA = Simulated_Annealing;

/*
namespace Simulated_Annealing{
// 入力
void input() {

}

void output() {

}

// 初期解を構築してスコアを計算
// スコア: score (型 : score_t)
void init() {
  score = diff = 0;

}

// 遷移先を設定(変数 : mode)
void set_state(int iter) {

}

// 差分を計算(遷移をするかは問題によって決める)
// 差分の変数はdiff
void calc_diff() {

}

// 遷移を採用して更新
void update() {
  score += diff;

}

// 元の状態に復元
void undo() {

}
}
*/