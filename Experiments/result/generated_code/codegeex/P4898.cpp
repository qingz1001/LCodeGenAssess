#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXQ 50000

int H, W, Q;
int R[MAXN], C[MAXN];
int A[MAXQ], B[MAXQ];
int ans[MAXQ];

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int main() {
    scanf("%d%d%d", &H, &W, &Q);

    for (int i = 0; i < H * W; i++) {
        scanf("%d%d", &R[i], &C[i]);
        R[i] *= W;
        R[i] += C[i];
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d%d", &A[i], &B[i]);
        A[i] *= W;
        A[i] += C[A[i]];
        B[i] *= W;
        B[i] += C[B[i]];
    }

    for (int i = 0; i < Q; i++) {
        int r1 = R[A[i]], c1 = A[i] - r1, r2 = R[B[i]], c2 = B[i] - r2;
        swap(&R[A[i]], &R[B[i]]);
        swap(&C[A[i]], &C[B[i]]);
        int new_r1 = R[A[i]], new_c1 = A[i] - new_r1, new_r2 = R[B[i]], new_c2 = B[i] - new_r2;
        // 计算美妙度并更新答案
        // 这里需要根据题目要求实现计算美妙度的逻辑
        // 假设计算出的美妙度为 x
        ans[i] = x;
    }

    for (int i = 0; i < Q; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}