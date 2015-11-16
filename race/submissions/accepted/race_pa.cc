// Rocky Mountain Regional Contest 2015: Amazing Race
// Author: Per Austrin
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> vi;
const double oo = 1<<20;
int mint[1<<20][22], back[1<<20][22];
int n, T, p[30], t[30], d[30], A[30][30];

int MinT(int S, int at) {
    if (S & (1<<at)) {
        int r = MinT(S & ~(1<<at), at);
        return (r <= d[at]-t[at]) ? r + t[at] : oo;
    }
    if (!S) return A[n][at];
    int &r = mint[S][at];
    if (r == -1) {
        r = oo;
        for (int i = 0; i < n; ++i)
            if (S & (1<<i))
                r = min(r, MinT(S, i) + A[i][at]);
    }
    return r;
}

int main(void) {
    scanf("%d%d", &n, &T);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", p+i, t+i, d+i);
        if (d[i] < 0) d[i] = oo;
    }
    for (int i = 0; i < n+2; ++i)
        for (int j = 0; j < n+2; ++j)
            scanf("%d", A[i]+j);
    int ans = 0;
    vi best;
    memset(mint, -1, sizeof(mint));
    for (int S = 0; S < (1<<n); ++S) {
        if (MinT(S, n+1) <= T) {
            int v = 0;
            vi vis;
            for (int i = 0; i < n; ++i)
                if (S & (1<<i)) {
                    v += p[i];
                    vis.push_back(i+1);
                }
            if (v > ans || v == ans && vis < best)
                ans = v, best = vis;
        }
    }
    printf("%d\n", ans);
    for (int i = 0; i < best.size(); ++i)
        printf("%d%c", best[i], i==best.size()-1 ? '\n' : ' ');
    return 0;
}
