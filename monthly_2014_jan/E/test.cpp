#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

const int SIZE = 1000;
const int NONE = -3;
int N;
int G[SIZE][SIZE];
int best[SIZE][SIZE];
bool used[SIZE * SIZE];
int sum;
int best_sum;

void show_grid( int G[SIZE][SIZE] ) {
  for ( int i = 0; i < N; ++ i ) {
    for ( int j = 0; j < N; ++ j ) {
      cout << setw(4) << G[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool check( int sr, int sc ) {
  if ( G[sr][sc] == 1 )
    return true;
  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};
  for ( int k = 0; k < 4; ++ k ) {
    int nr = sr + dr[k];
    int nc = sc + dc[k];
    if ( nr < 0 || nr >= N || nc < 0 || nc >= N )
      continue;
    if ( abs(G[sr][sc] - G[nr][nc]) == 1 )
      return true;
  }
  return false;
}

bool check() {
  for ( int i = 0; i < N; ++ i )
    for ( int j = 0; j < N; ++ j )
      if ( ! ( check(i, j) ) )
        return false;
  return true;
}

void rec_bad( int sr, int sc ) {
  if ( sc >= N )
    return rec_bad(sr + 1, 0);
  if ( sr >= N ) {
    if ( check() ) {
      if ( sum > best_sum ) {
        best_sum = sum;
        std::copy((int*)G, (int*)G + SIZE * SIZE, (int*)best);
      }
    }
    return;
  }

  for ( int i = 1; i <= N * N; ++ i ) {
    if ( used[i] )
      continue;
    G[sr][sc] = i;
    used[i] = true;
    if ( sr == sc )
      sum += i;
    rec_bad(sr, sc + 1);
    if ( sr == sc )
      sum -= i;
    used[i] = false;
    G[sr][sc] = NONE;
  }
}

void update_best() {
  if ( sum > best_sum ) {
    best_sum = sum;
    std::copy((int*)G, (int*)G + SIZE * SIZE, (int*)best);
  }
}

void rec( int sr, int sc, int prev = 1 ) {
  if ( prev == N * N ) {
    if ( check() ) {
      update_best();
    }
    return;
  }

  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};
  for ( int k = 0; k < 4; ++ k ) {
    int nr = sr + dr[k];
    int nc = sc + dc[k];
    if ( nr < 0 || nr >= N || nc < 0 || nc >= N )
      continue;
    if ( G[nr][nc] != NONE )
      continue;
    int next = prev + 1;
    G[nr][nc] = next;
    if ( nr == nc )
      sum += next;
    rec(nr, nc, next);
    if ( nr == nc )
      sum -= next;
    G[nr][nc] = NONE;
  }
}

int main() {
  for ( int i = 1; i <= 5; ++ i ) {
    N = i;
    std::fill((int*)G, (int*) G + SIZE * SIZE, NONE);
    sum = 0;
    best_sum = -1;

    for ( int sr = 0; sr < N; ++ sr ) {
      for ( int sc = 0; sc < N; ++ sc ) {
        G[sr][sc] = 1;
        if ( sr == sc )
          sum += 1;
        rec(sr, sc);
        if ( sr == sc )
          sum -= 1;
        G[sr][sc] = NONE;
      }
    }

    cout << "best_sum = " << best_sum << endl;
    show_grid(best);
  }
  return 0;
}
