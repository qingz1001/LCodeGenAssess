#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXK 200

int T, n, K, L;
int a[MAXN], b[MAXN];
int sum_a[MAXN], sum_b[MAXN];
int c[MAXK], d[MAXK];
int used[MAXN];
int heap[MAXN];
int heap_size;

void push(int val) {
    int i = ++heap_size;
    while (i > 1 && val > heap[i / 2]) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}

int pop() {
    int ret = heap[1], val = heap[heap_size--];
    int i = 1;
    while (i * 2 <= heap_size) {
        int child = i * 2;
        if (child < heap_size && heap[child] < heap[child + 1]) child++;
        if (val >= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = val;
    return ret;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &K, &L);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

        // 计算前缀和
        for (int i = 1; i <= n; i++) sum_a[i] = sum_a[i - 1] + a[i];
        for (int i = 1; i <= n; i++) sum_b[i] = sum_b[i - 1] + b[i];

        // 初始化堆
        heap_size = 0;
        for (int i = 1; i <= n; i++) push(a[i] + b[i]);

        // 选择前K-L个最大的下标
        for (int i = 0; i < K - L; i++) {
            int idx = pop();
            for (int j = 1; j <= n; j++) {
                if (a[j] + b[j] == idx) {
                    used[j] = 1;
                    break;
                }
            }
        }

        // 选择剩余的L个下标
        int max_sum = 0;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                c[++K] = i;
                max_sum += a[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                d[++K] = i;
                max_sum += b[i];
            }
        }

        printf("%d\n", max_sum);

        // 重置数组
        for (int i = 1; i <= n; i++) used[i] = 0;
        heap_size = 0;
        K = 0;
    }
    return 0;
}