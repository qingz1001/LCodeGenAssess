#include <stdio.h>
#include <stdlib.h>

void monotonicQueue(int n, int k, int *a, int *min_result, int *max_result) {
    int *deque = (int *)malloc(n * sizeof(int));
    int front = 0, rear = -1;

    // 计算最小值
    for (int i = 0; i < n; i++) {
        // 如果队列不为空且队首元素已经不在窗口内，则移除队首元素
        if (front <= rear && deque[front] <= i - k) {
            front++;
        }
        // 保持队列单调递增
        while (front <= rear && a[deque[rear]] >= a[i]) {
            rear--;
        }
        deque[++rear] = i;
        if (i >= k - 1) {
            min_result[i - k + 1] = a[deque[front]];
        }
    }

    front = 0;
    rear = -1;

    // 计算最大值
    for (int i = 0; i < n; i++) {
        // 如果队列不为空且队首元素已经不在窗口内，则移除队首元素
        if (front <= rear && deque[front] <= i - k) {
            front++;
        }
        // 保持队列单调递减
        while (front <= rear && a[deque[rear]] <= a[i]) {
            rear--;
        }
        deque[++rear] = i;
        if (i >= k - 1) {
            max_result[i - k + 1] = a[deque[front]];
        }
    }

    free(deque);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int *min_result = (int *)malloc((n - k + 1) * sizeof(int));
    int *max_result = (int *)malloc((n - k + 1) * sizeof(int));

    monotonicQueue(n, k, a, min_result, max_result);

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", min_result[i]);
    }
    printf("\n");

    for (int i = 0; i < n - k + 1; i++) {
        printf("%d ", max_result[i]);
    }
    printf("\n");

    free(a);
    free(min_result);
    free(max_result);

    return 0;
}