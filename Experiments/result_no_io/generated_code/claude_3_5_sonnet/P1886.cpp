#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000005

int n, k;
int a[MAX_N];
int q[MAX_N], head, tail;

void solve(int is_max) {
    head = tail = 0;
    for (int i = 0; i < n; i++) {
        while (head < tail && (is_max ? a[q[tail-1]] <= a[i] : a[q[tail-1]] >= a[i])) {
            tail--;
        }
        q[tail++] = i;
        if (q[head] <= i - k) {
            head++;
        }
        if (i >= k - 1) {
            printf("%d ", a[q[head]]);
        }
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    solve(0);  // 求最小值
    solve(1);  // 求最大值
    
    return 0;
}