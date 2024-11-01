#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000

typedef struct {
    int x, y, l;
} Star;

int cmp(const void *a, const void *b) {
    return ((Star*)a)->x - ((Star*)b)->x;
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long solve(Star *stars, int n, int W, int H) {
    qsort(stars, n, sizeof(Star), cmp);
    
    long long result = 0;
    long long sum[MAX_N + 1];
    
    for (int left = 0; left < n; left++) {
        int right = left;
        memset(sum, 0, sizeof(sum));
        
        while (right < n && stars[right].x - stars[left].x < W) {
            if (stars[right].y < H) {
                sum[stars[right].y] += stars[right].l;
            }
            right++;
        }
        
        long long current = 0;
        long long max_sum = 0;
        
        for (int i = 0; i < H; i++) {
            current += sum[i];
            if (i >= H) current -= sum[i - H];
            max_sum = max(max_sum, current);
        }
        
        result = max(result, max_sum);
    }
    
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n, W, H;
        scanf("%d %d %d", &n, &W, &H);
        
        Star stars[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].l);
        }
        
        printf("%lld\n", solve(stars, n, W, H));
    }
    
    return 0;
}