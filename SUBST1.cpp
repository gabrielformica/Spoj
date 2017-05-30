#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)
#define ALL(container) (container).begin(), (container).end()
#define pb push_back
#define eb emplace_back
const int MAXMAX = 50005;
using namespace std;

namespace SuffixArray {
    const int MAXN = MAXMAX + 5;
    char *S;
    int N, gap;
    int sa[MAXN], pos[MAXN], tmp[MAXN], PLCP[MAXN], LCP[MAXN], phi[MAXN];
    bool sufCmp(int i, int j) {
        if (pos[i] != pos[j]) return pos[i] < pos[j];
        i += gap; j += gap;
        return (i < N && j < N) ? pos[i] < pos[j] : i > j;
    }
    void buildSA() {
        tmp[0] = 0;
        N = strlen(S);
        FOR(i, N) sa[i] = i, pos[i] = S[i];
        for (gap = 1; ; gap <<= 1) {
            sort(sa, sa + N, sufCmp);
            FOR(i, N-1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
            FOR(i, N) pos[sa[i]] = tmp[i];
            if (tmp[N-1] == N-1) break;
        }
    }
    // O(N^2)
    void buildLCP() {
        LCP[0] = 0;
        for (int i = 1; i < N; i++) {
            int L = 0;
            while (S[sa[i] + L] == S[sa[i-1] + L]) L++;
            LCP[i] = L;
        }
    }
    // O(N)
    void buildLCP2() {
        int i, L;
        phi[sa[0]] = -1;
        for (i = 1; i < N; i++) phi[sa[i]] = sa[i-1];
        for (i = L = 0; i < N; i++) {
            if (phi[i] == -1) { PLCP[i] = 0; continue; }
            while (S[i + L] == S[phi[i] + L]) L++;
            PLCP[i] = L;
            L = max(L-1, 0);
        }
        for (i = 1; i < N; i++) LCP[i] = PLCP[sa[i]];
    }
    void clear() {
        FOR(i, MAXN) sa[i] = pos[i] = tmp[i] = PLCP[i] = phi[i] = LCP[i] = 0;
    }
}

char str[MAXMAX];
int T;
int main() {
    ri(T); 
    while (T--) {
        scanf("%s", str);
        SuffixArray::S = str;
        SuffixArray::buildSA();
        SuffixArray::buildLCP();
        int N = SuffixArray::N, sum = 0;
        int *sa = SuffixArray::sa;
        int *lcp = SuffixArray::LCP;
        int ll = 0;
        for (int i = 0; i < N; i++) sum += (N - sa[i]);
        for (int i = 0; i < N; i++) ll += lcp[i];
        printf("%d\n", sum - ll);
        SuffixArray::clear();
    }
    return 0;
}
