
// @snippet<sh19910711/contest-base:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 3;
  const int BIT_SIZE = 1 << SIZE;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Double A[SIZE][2];
  };
  struct OutputStorage {
    Double result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Solver: public SolverInterface {
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = get_maximum_area(in->A);
      return out;
    }

  protected:
    static Double get_maximum_area( const Double A[SIZE][2] ) {
      Double res = 0.0;
      for ( int i = 0; i < BIT_SIZE; ++ i ) {
        Double B[SIZE][2];
        for ( int j = 0; j < SIZE; ++ j ) {
          int bj = 1 << j;
          B[j][0] = A[j][0];
          B[j][1] = A[j][1];
          if ( i & bj ) {
            std::swap(B[j][0], B[j][1]);
          }
        }
        res = std::max(res, get_area(B));
      }
      return std::sqrt(res);
    }

    static Double get_area( const Double A[SIZE][2] ) {
      Double res = 0.0;
      res = std::max(res, get_area_0(A));
      res = std::max(res, get_area_1(A));
      res = std::max(res, get_area_2(A));
      res = std::max(res, get_area_3(A));
      return res;
    }

    static Double get_area( Double a, Double b, Double c ) {
      if ( ! is_valid(a, b, c) )
        return 0.0;
      Double s = ( a + b + c ) * 0.5;
      return s * ( s - a ) * ( s - b ) * ( s - c );
    }

    static Double get_a( const Double A[SIZE][2], const int& id ) {
      return A[id][0] + A[id][1];
    }

    static Double get_l( const Double A[SIZE][2], const int& id ) {
      return A[id][0];
    }

    static Double get_u( const Double A[SIZE][2], const int& id ) {
      return A[id][1];
    }

    static bool is_valid( const Double& a, const Double& b, const Double& c ) {
      return a < b + c && b < a + c && c < b + a;
    }

    static Double get_area_0( const Double A[SIZE][2] ) {
      Double res = 0.0;
      int id[SIZE];
      for ( int i = 0; i < SIZE; ++ i )
        id[i] = i;
      do {
        int i = id[0];
        int j = id[1];
        int k = id[2];
        Double a = get_a(A, i);
        Double b = get_a(A, j);
        Double c = get_a(A, k);
        res = std::max(res, get_area(a, b, c));
      } while ( std::next_permutation(id, id + SIZE) );
      return res;
    }

    static Double get_area_1( const Double A[SIZE][2] ) {
      Double res = 0.0;
      int id[SIZE];
      for ( int i = 0; i < SIZE; ++ i )
        id[i] = i;
      do {
        int i = id[0];
        int j = id[1];
        int k = id[2];
        {
          Double a = get_l(A, i);
          Double b = get_a(A, j) + get_a(A, k);
          Double c = get_u(A, i);
          res = std::max(res, get_area(a, b, c));
        }
        {
          Double a = get_l(A, i);
          Double b = get_u(A, i) + get_a(A, j);
          Double c = get_a(A, k);
          res = std::max(res, get_area(a, b, c));
        }
      } while ( std::next_permutation(id, id + SIZE) );
      return res;
    }

    static Double get_area_2( const Double A[SIZE][2] ) {
      Double res = 0.0;
      int id[SIZE];
      for ( int i = 0; i < SIZE; ++ i )
        id[i] = i;
      do {
        int i = id[0];
        int j = id[1];
        int k = id[2];
        Double a = get_l(A, i);
        Double b = get_u(A, i) + get_a(A, j) + get_l(A, k);
        Double c = get_u(A, k);
        res = std::max(res, get_area(a, b, c));
      } while ( std::next_permutation(id, id + SIZE) );
      return res;
    }

    static Double get_area_3( const Double A[SIZE][2] ) {
      Double res = 0.0;
      int id[SIZE];
      for ( int i = 0; i < SIZE; ++ i )
        id[i] = i;
      do {
        int i = id[0];
        int j = id[1];
        int k = id[2];
        Double a = get_l(A, i) + get_u(A, j);
        Double b = get_l(A, j) + get_u(A, k);
        Double c = get_l(A, k) + get_u(A, i);
        res = std::max(res, get_area(a, b, c));
      } while ( std::next_permutation(id, id + SIZE) );
      return res;
    }

  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      for ( int i = 0; i < SIZE; ++ i ) {
        if ( ! ( std::cin >> in->A[i][0] >> in->A[i][1] ) )
          return false;
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      std::printf("%.20Lf\n", out->result);
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

