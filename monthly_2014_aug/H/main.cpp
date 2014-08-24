#include <iostream>
using namespace std;

typedef long long Int;

const Int N_MAX = 10000 + 11;

Int N;
Int A[N_MAX];

bool input() {
  if ( cin >> N ) {
    for ( int i = 0; i < N - 1; ++ i ) cin >> A[i];
    return true;
  }
  return false;
}

Int G[N_MAX][2];
Int DN[N_MAX]; // number of deps
Int RDN[N_MAX]; // number of deps has two deps

void init() {
  fill(DN, DN + N_MAX, 0);
  fill(RDN, RDN + N_MAX, 0);
}

void rec_rdn( const Int& cur, Int sum ) {
  if ( DN[cur] == 2 ) sum ++;
  RDN[cur] = sum;
  for ( int i = 0; i < DN[cur]; ++ i ) {
    rec_rdn(G[cur][i], sum);
  }
}

Int rec( const Int& cur ) {
  Int res = 0;
  if ( DN[cur] == 2 ) {
    if ( RDN[G[cur][0]] > RDN[G[cur][1]] ) {
      res = max(rec(G[cur][0]), rec(G[cur][1]) + 1);
    } else {
      res = max(rec(G[cur][0]) + 1, rec(G[cur][1]));
    }
  } else if ( DN[cur] == 1 ) {
      res = rec(G[cur][0]);
  }
  return res;
}

Int solve() {
  for ( int i = 0; i < N; ++ i ) A[i] --;
  for ( int i = 0; i < N; ++ i ) {
    G[A[i]][DN[A[i]] ++] = i + 1;
  }
  rec_rdn(0, 0);
  // for ( int i = 0; i < N; ++ i ) { cout << i << ": " << DN[i] << ", " << RDN[i] << endl; }
  return rec(0) + 1;
}

int main() {
  while ( input() ) {
    init();
    cout << solve() << endl;
  }
  return 0;
}
