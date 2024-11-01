#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define INF 0x7FFFFFFF

typedef struct {
    int size;
    int value;
} File;

int n, p, S;
File files[MAX_N];

void input() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &files[i].size, &files[i].value);
    }
}

int cmp(const void *a, const void *b) {
    return ((File *)b)->value - ((File *)a)->value;
}

int knapsack(int capacity) {
    int dp[MAX_N] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= files[i].size; j--) {
            dp[j] = (dp[j] > dp[j - files[i].size] + files[i].value) ? dp[j] : dp[j - files[i].size] + files[i].value;
        }
    }
    return dp[capacity];
}

int main() {
    input();
    
    qsort(files, n, sizeof(File), cmp);
    
    int left = 1, right = INF, ans = INF;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (knapsack(mid) >= p) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    if (ans == INF) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", ans);
    }
    
    return 0;
}