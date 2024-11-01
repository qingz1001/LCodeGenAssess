#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20005
#define MAXQ 25005

int n, Q;
int s[MAXN], sorted[MAXN];
int st[MAXN][15], lg[MAXN];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void preprocess() {
    memcpy(sorted, s, n * sizeof(int));
    qsort(sorted, n, sizeof(int), cmp);
    
    for (int i = 0; i < n; i++)
        st[i][0] = sorted[i];
    
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = (st[i][j-1] > st[i+(1<<(j-1))][j-1]) ? st[i][j-1] : st[i+(1<<(j-1))][j-1];
    
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i/2] + 1;
}

int query(int l, int r) {
    int j = lg[r - l + 1];
    return (st[l][j] > st[r-(1<<j)+1][j]) ? st[l][j] : st[r-(1<<j)+1][j];
}

int findMedian(int l, int r) {
    int len = r - l + 1;
    int medianPos = (len - 1) / 2;
    int lo = 0, hi = n - 1;
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = 0;
        for (int i = l; i <= r; i++)
            if (s[i] <= sorted[mid])
                count++;
        
        if (count <= medianPos)
            lo = mid + 1;
        else
            hi = mid;
    }
    
    return sorted[lo];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &s[i]);
    
    preprocess();
    
    scanf("%d", &Q);
    int lastAns = 0;
    
    while (Q--) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        
        int q[4] = {(a + lastAns) % n, (b + lastAns) % n, (c + lastAns) % n, (d + lastAns) % n};
        qsort(q, 4, sizeof(int), cmp);
        
        int maxMedian = 0;
        for (int i = q[0]; i <= q[1]; i++)
            for (int j = q[2]; j <= q[3]; j++)
                maxMedian = (maxMedian > findMedian(i, j)) ? maxMedian : findMedian(i, j);
        
        printf("%d\n", maxMedian);
        lastAns = maxMedian;
    }
    
    return 0;
}