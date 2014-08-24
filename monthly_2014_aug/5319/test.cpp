#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef vector<int> IntVector;

IntVector gen_b( const IntVector& a, const int& n ) {
  IntVector b(n);
  b[0] = a[0];
  for ( int i = 1; i < n; ++ i ) {
    b[i] = abs(a[i] - b[i - 1]);
  }
  return b;
}

void print_vector( const IntVector& v ) {
  for ( const auto& x : v ) {
    cout << x << ", ";
  }
  cout << endl;
}

void func( const int& n, const int& f = -1 ) {
  IntVector a(n);
  for ( int i = 0; i < n; ++ i ) a[i] = i + 1;
  cout << "n = " << n << endl;
  int mi = 50001, ma = -1;
  do {
    const auto& b = gen_b(a, n);
    // if ( f == -1 || b[n - 1] == f ) { cout << "a = "; print_vector(a); cout << "b = "; print_vector(b); cout << endl; }
    mi = min(mi, b[n - 1]);
    ma = max(ma, b[n - 1]);
  } while( next_permutation(begin(a), end(a)) );
  cout << "min: " << mi << ", max: " << ma << endl;
}

int main() {
  func(12);
  return 0;
  for ( int i = 1; i <= 7; ++ i ) {
    func(i);
  }
}
