
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  using namespace std;
  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int MAX_N = 1000 + 11;
  typedef std::set<Int> IntSet;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int A[MAX_N];
    IntSet hit[MAX_N];
    IntSet pocket[MAX_N];
  };
  
  struct Output {
    Int AP;
    Int BP;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( ! ( s >> in.N >> in.M ) ) return false;
      for ( auto i = 0; i < in.N; ++ i ) {
        if ( ! ( s >> in.A[i] ) ) return false;
      }
      for ( auto i = 0; i < in.M; ++ i ) {
        in.hit[i].clear();
        in.pocket[i].clear();
        Int num1;
        s >> num1;
        for ( auto j = 0; j < num1; ++ j ) {
          Int id;
          s >> id;
          in.hit[i].insert(id);
        }
        Int num2;
        s >> num2;
        for ( auto j = 0; j < num2; ++ j ) {
          Int id;
          s >> id;
          in.pocket[i].insert(id);
        }
      }
      return s;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.AP << " : " << out.BP << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}

    IntSet rem;
    Int AP;
    Int BP;
    bool flag;
    
    bool solve() {
      rem.clear();
      AP = 0;
      BP = 0;
      for ( auto i = 0; i < in.N; ++ i ) {
        rem.insert(in.A[i]);
      }
      flag = true;
      for ( auto i = 0; i < in.M; ++ i ) {
        if ( ! move(i) ) {
          flag = ! flag;
        }
        remove(i);
      }
      out.AP = AP;
      out.BP = BP;
      return true;
    }

    void remove( const Int& cur ) {
      for ( auto v : in.pocket[cur] ) {
        if ( v == 0 ) continue;
        rem.erase(v);
      }
    }

    bool move( const Int& cur ) {
      Int t_id = *rem.begin();
      if ( in.hit[cur].empty() ) {
        get_penalty(t_id);
        return false;
      } else if ( ! in.pocket[cur].count(0) && in.hit[cur].size() ) {
        if ( ! in.hit[cur].count(t_id) ) {
          get_penalty(*in.hit[cur].rbegin());
          return false;
        }
        if ( in.hit[cur].size() > 1 ) {
          get_penalty(*in.hit[cur].rbegin());
          return false;
        }
      } else if ( in.pocket[cur].count(0) ) {
        if ( in.hit[cur].size() ) {
          get_penalty(*in.hit[cur].rbegin());
          return false;
        }
      }
      if ( in.pocket[cur].count(t_id) ) {
        get_point(std::accumulate(begin(in.pocket[cur]), end(in.pocket[cur]), Int(0)));
        return true;
      }
      get_penalty(std::accumulate(begin(in.pocket[cur]), end(in.pocket[cur]), Int(0)));
      return false;
    }

    void get_point( const Int& p ) {
      if ( flag ) {
        AP += p;
      } else {
        BP += p;
      }
    }

    void get_penalty( const Int& p ) {
      if ( flag ) {
        BP += p;
      } else {
        AP += p;
      }
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

