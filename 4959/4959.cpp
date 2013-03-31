
// @snippet<sh19910711/contest:headers.cpp>
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
    typedef std::istringstream ISS;
    typedef std::ostringstream OSS;
    typedef std::vector<std::string> VS;
    typedef long long LL;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}


// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
    const std::string OUTPUT_VECTOR_DELIMITER = ",";
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
    template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
        typedef typename std::vector<T>::const_iterator Iterator;
        for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
            os << *it_i;
            if ( it_i + 1 != v.end() )
                os << OUTPUT_VECTOR_DELIMITER;
        }
        return os;
    }
    template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
        int n = v.size();
        for ( int i = 0; i < n; ++ i ) {
            is >> v[i];
        }
        return is;
    }
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    using namespace io;
    
    const int SIZE = 100011;
    const int DEPTH = 20;
    int n, m;
    int P[SIZE];
    int T[SIZE][DEPTH];
    int TC[SIZE];
    
    class Solution: public ISolution {
    public:
        
        void init () {
            fill( TC, TC+SIZE, 0 );
        }
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            P[1] = -1;
            for ( int i = 2; i <= n; ++ i )
                cin >> P[i];
            return true;
        }
        
        void calc_path( int from ) {
            int& tc = TC[from];
            int cur = from;
            T[from][tc++] = cur;
            while ( P[cur] != -1 ) {
                cur = P[cur];
                T[from][tc++] = cur;
            }
        }
        
        void solve() {
            for ( int i = 1; i <= n; ++ i )
                calc_path(i);
            for ( int i = 1; i <= n; ++ i ) {
                cout << i << ": " << VI( T[i], T[i]+TC[i] ) << endl;
            }
        }
        
        int query( int target ) {
            return -1;
        }
        
        void operate( int target ) {
            cout << "@operator: target = " << target << endl;
        }
        
        void query() {
            string type;
            int info;
            for ( int i = 0; i < m; ++ i ) {
                cin >> type >> info;
                if ( type == "q" )
                    cout << query(info) << endl;
                else
                    operate(info);
            }
        }
        
        int run() {
            while ( init(), input() ) {
                solve();
                query();
            }
            return 0;
        }
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}


