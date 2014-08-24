#include <iostream>
#include <vector>
using namespace std;

typedef long long Int;
typedef vector<Int> IntVector;

const Int N_MAX = 50000 + 11;

Int N;

bool input() {
  return cin >> N;
}

IntVector pattern_max_a() {
  IntVector res(N);
  res[0] = N;
  for ( int i = 1; i < N - 1; ++ i ) {
    res[i] = N - i - 1;
  }
  res[N - 1] = N - 1;
  return res;
}

IntVector pattern_max_b() {
  IntVector res(N);
  for ( int i = 0; i < N - 1; ++ i ) {
    res[i] = N - i - 1;
  }
  res[N - 1] = N;
  return res;
}

IntVector pattern_min() {
  IntVector res(N);
  for ( int i = 0; i < N; ++ i ) {
    res[i] = N - i;
  }
  return res;
}

IntVector gen_b( const IntVector& a, const int& n ) {
  IntVector b(n);
  b[0] = a[0];
  for ( int i = 1; i < n; ++ i ) {
    b[i] = abs(a[i] - b[i - 1]);
  }
  return b;
}

void print_vector( const IntVector& v ) {
  bool flag = false;
  for ( const auto& x : v ) {
    if ( flag ) cout << " ";
    flag = true;
    cout << x;
  }
  cout << endl;
}

void solve() {
  IntVector max_a;
  IntVector min_a = pattern_min();
  Int max_b, min_b;
  IntVector ma_a = pattern_max_a();
  IntVector ma_b = pattern_max_b();
  IntVector mb_a = gen_b(ma_a, N);
  IntVector mb_b = gen_b(ma_b, N); 
  if ( mb_a[N - 1] < mb_b[N - 1] ) {
    max_a = ma_b;
    max_b = mb_b[N - 1];
  } else {
    max_a = ma_a;
    max_b = mb_a[N - 1];
  }
  min_b = gen_b(min_a, N)[N - 1];
  cout << min_b << " " << max_b << endl;
  print_vector(max_a);
  print_vector(min_a);
}

int main() {
  while ( input() ) {
    solve();
  }
  return 0;
}
