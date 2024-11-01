#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int l;
    int r;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *ia = (Interval*)a;
    Interval *ib = (Interval*)b;
    if (ia->r != ib->r)
        return ia->r - ib->r;
    return ia->l - ib->l;
}

typedef long long ll;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);

    Interval intervals[m];
    for(int i=0;i<m;i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        intervals[i].l = y;
        intervals[i].r = x;
    }

    qsort(intervals, m, sizeof(Interval), cmp);

    // Build logs
    int logn = 0;
    while((1 << (logn +1)) <= n) logn++;
    int logs[n+1];
    logs[1] = 0;
    for(int i=2;i<=n;i++) logs[i] = logs[i/2] +1;

    // Build sparse table
    int K = logn +1;
    int st_pos[K][n+1];
    for(int i=1;i<=n;i++) st_pos[0][i] = i;
    for(int k=1;k<K;k++) {
        for(int i=1;i + (1 << k) -1 <=n;i++) {
            int first = st_pos[k-1][i];
            int second = st_pos[k-1][i + (1 << (k-1))];
            if(a[first] < a[second]) st_pos[k][i] = first;
            else st_pos[k][i] = second;
        }
    }

    // Function to get position with minimal a in [L, R]
    auto get_min_pos = [&](int L, int R) -> int {
        int j = logs[R - L +1];
        int first = st_pos[j][L];
        int second = st_pos[j][R - (1 << j) +1];
        if(a[first] < a[second]) return first;
        else return second;
    };

    ll total_cost = 0;
    int last_chosen = 0;
    for(int i=0;i<m;i++) {
        if(intervals[i].l > last_chosen){
            int p = get_min_pos(intervals[i].l, intervals[i].r);
            last_chosen = p;
            total_cost += (ll)a[p];
        }
    }

    printf("%lld\n", total_cost);
    return 0;
}