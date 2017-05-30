#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <set>
 
// Macros (repetición).
#define REP(n) while((n)--)
#define FOR(i, from, to) for (int i = (from) ; i < (to) ; i++)
#define FORS(i, from, to, step) for (int i = (from) ; i != (to) ; i += (step))
#define FOREACH(obj, it) for (typeof((obj).begin()) it = (obj).begin() ; it != (obj).end() ; it++)
#define FOREACHR(obj, it) for (typeof((obj).rbegin()) it = (obj).rbegin() ; it != (obj).rend() ; it++)
#define RI(x) scanf("%d", &x)
#define RLL(x) scanf("%lld", &x)
 
// Macros (contenedores).
#define FILL(obj, val) memset(obj, val, sizeof(obj))
#define SIZE(obj) ((int)(obj.size()))
#define ALL(obj) (obj).begin(), (obj).end()
#define RALL(obj) (obj).rbegin(), (obj).rend()
#define IN(elem, obj) (find(ALL(obj), elem) != (obj).end())
 
// Macros (miscelaneas).
#define BIT(n, i) ((n)&(1<<(i)))
#define LOWBIT(n) ((n)&((n)^((n)-1)))
#define SYNC ios_base::sync_with_stdio(0);
#define CONV(from, to) if (true) {stringstream ss; ss << from; ss >> to;}
 
// Macros (abreviaturas).
#define MP make_pair
#define PB push_back
 
// Macros constantes).
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define PI 3.1415926535897932384626
 
using namespace std;
 
// Aliases de tipos 
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
 
typedef pair<int, int> ii;
 
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<string> vs;
 
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<int, vi> miv;
 
// Funciones 
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int mcm(int a, int b){ return a * b / gcd(a, b); }
int sq(int a) { return a*a; }
int pot(int a, int b){ return b ? sq(pot(a, b >> 1))*(b & 1 ? a : 1) : 1; }
int roofLog2(int n) { int r = 1; for ( ; r < n ; r <<= 1); return r; }
 
int column[2500];
bool visited[2500];
vector<vi> AdjList; 

bool find_match(int where) {
    if (where == -1) 
        return true;
    FOR(i, 0, AdjList[where].size()) {
        int match = AdjList[where][i];
        if (! visited[match]) {
            visited[match] = true;
            if (find_match(column[match])) {
                column[match] = where;
                return true;
            }
        }
    }
    return false;
}

int t, r, c;
char farm[55][55];
int gridh[55][55], gridv[55][55];

int main() {
    RI(t);
    REP(t) {
        RI(r); RI(c);
        FILL(gridh, -1);
        FILL(gridv, -1);
        FILL(column, -1);
        FOR(i, 0, r) scanf("%s", farm[i]);

        int counth= 0, countv = 0;
        AdjList.assign(2500, vi());
        FOR(i, 0, r) {
            bool last = false;
            FOR(j, 0, c) {
                if (farm[i][j] == '*') {
                    if (last) gridh[i][j] = counth;
                    else gridh[i][j] = ++counth;
                    last = true;
                } else last = false;
            }
        }
        FOR(j, 0, c) {
            bool last = false;
            FOR(i, 0, r) {
                if (farm[i][j] == '*') {
                    if (last) gridv[i][j] = countv;
                    else gridv[i][j] = ++countv;
                    last = true;
                } else last = false;
            }
        }
        FOR(i, 0, r)
            FOR(j, 0, c)
                if (farm[i][j] == '*')
                    AdjList[ gridh[i][j] ].push_back( gridv[i][j] ); 

        int ret = 0;
        FOR(i, 0, 2500)
            if (AdjList[i].size() > 0) {
                FILL(visited, false);
                ret += find_match(i);
            }

        AdjList.clear();
        printf("%d\n", ret);
    }

    return 0;
}
