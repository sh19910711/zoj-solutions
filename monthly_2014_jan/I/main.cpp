
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
  typedef int Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 11;
  const Int NONE = -1;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Int EG[SIZE][SIZE];
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Search {
  public:
    const InputStorage* in;

    Int D[SIZE][SIZE];
    Int limit_start;
    Int limit;
    Int mines;
    Int remains;

    bool can_put( Int r, Int c ) {
      // left
      if ( c > 0 ) {
        for ( Int dr = -1; dr <= 1; ++ dr ) {
          Int nr = r + dr;
          if ( nr < 0 || nr >= in->N )
            continue;
          if ( D[nr][c] + 1 > in->EG[nr][c] )
            return false;
        }
      }
      // right
      if ( c < in->M - 1 ) {
        for ( Int dr = -1; dr <= 1; ++ dr ) {
          Int nr = r + dr;
          if ( nr < 0 || nr >= in->N )
            continue;
          if ( D[nr][c] + 1 > in->EG[nr][c] )
            return false;
        }
      }
      return true;
    }

    bool put( Int r, Int c, Int val ) {
      // left
      if ( c - 1 >= 0 ) {
        for ( Int dr = -1; dr <= 1; ++ dr ) {
          Int nr = r + dr;
          if ( nr < 0 || nr >= in->N )
            continue;
          D[nr][c - 1] += val;
          remains -= val;
        }
      }
      // right
      if ( c < in->M ) {
        for ( Int dr = -1; dr <= 1; ++ dr ) {
          Int nr = r + dr;
          if ( nr < 0 || nr >= in->N )
            continue;
          D[nr][c] += val;
          remains -= val;
        }
      }
      return true;
    }

    void show_table( const Int table[SIZE][SIZE] ) {
      for ( int i = 0; i < in->N; ++ i ) {
        for ( int j = 0; j < in->M; ++ j ) {
          cout << table[i][j] << ", ";
        }
        cout << endl;
      }
    }

    bool rec( Int sr, Int sc ) {
      if ( sr >= in->N ) { 
        return rec(0, sc + 1);
      }
      if ( sc > in->M ) {
        // cout << "mines = " << mines << endl;
        // cout << "D: " << endl;
        // cout << "mines = " << mines << " / remains = " << remains << endl;
        // show_table(D);
        return mines == limit && remains == 0;
      }

      // put if can put
      // cout << "@rec: sr = " << sr << ", " << sc << endl;
      // show_table(D);
      if ( remains && mines < limit && can_put(sr, sc) ) {
        // cout << "@rec: can_put: " << sr << ", " << sc << endl;
        put(sr, sc, 1);
        mines ++;
        if ( rec(sr + 1, sc) )
          return true;
        mines --;
        put(sr, sc, -1);
      }
      // no put
      return rec(sr + 1, sc);
    }

    Int run( const InputStorage* in ) {
      this->in = in;
      limit_start = 0;
      for ( int r = 0; r < in->N; ++ r ) {
        for ( int c = 0; c < in->M; ++ c ) {
          limit_start = std::max(limit_start, in->EG[r][c]);
        }
      }

      remains = 0;
      for ( int r = 0; r < in->N; ++ r ) {
        for ( int c = 0; c < in->M; ++ c ) {
          remains += in->EG[r][c];
        }
      }

      for ( int r = 0; r < SIZE; ++ r ) {
        for ( int c = 0; c < SIZE; ++ c ) {
          D[r][c] = 0;
        }
      }

      mines = 0;
      // cout << endl;
      for ( limit = limit_start; ; ++ limit ) {
        // cout << "limit = " << limit << endl;
        if ( rec(0, 0) ) {
          return limit;
        }
        break;
      }
      return -1;
    }
  };

  class Solver: public SolverInterface {
  public:
    Search search;

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = search.run(in);
      return out;
    }
  protected:
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( int i = 0; i < in->N; ++ i ) {
        for ( int j = 0; j < in->M; ++ j ) {
          std::cin >> in->EG[i][j];
        }
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
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

