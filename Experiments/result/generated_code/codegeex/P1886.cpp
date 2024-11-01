#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int q_min[MAXN], q_max[MAXN];
int a[MAXN];

void push_min(int *q, int *tail, int val, int k) {
    while (*tail > 0 && a[q[*tail - 1]] > val && q[*tail - 1] - *tail + 1 <= k) (*tail)--;
    q[(*tail)++] = val;
}

void push_max(int *q, int *tail, int val, int k) {
    while (*tail > 0 && a[q[*tail - 1]] < val && q[*tail - 1] - *tail + 1 <= k) (*tail)--;
    q[(*tail)++] = val;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int head_min = 0, tail_min = 0, head_max = 0, tail_max = 0;

    for (int i = 0; i < n; i++) {
        if (i >= k) {
            if (q_min[head_min] == i - k) head_min++;
            if (q_max[head_max] == i - k) head_max++;
        }
        push_min(&q_min, &tail_min, i, k);
        push_max(&q_max, &tail_max, i, k);
        if (i >= k - 1) {
            printf("%d ", a[q_min[head_min]]);
            printf("%d ", a[q_max[head_max]]);
        }
    }
    printf("\n");
    return 0;
}