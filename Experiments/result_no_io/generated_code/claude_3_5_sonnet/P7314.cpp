#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100000

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);

    int A[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int result = INT_MAX;
    int stack[MAX_N];
    int top = -1;

    for (int i = 0; i < N; i++) {
        while (top >= 0 && A[stack[top]] > A[i]) {
            int height = A[stack[top--]];
            int width = top >= 0 ? i - stack[top] - 1 : i;
            result = min(result, height - min(A[i], top >= 0 ? A[stack[top]] : INT_MIN));
        }
        stack[++top] = i;
    }

    while (top >= 0) {
        int height = A[stack[top--]];
        int width = top >= 0 ? N - stack[top] - 1 : N;
        result = min(result, height - (top >= 0 ? A[stack[top]] : INT_MIN));
    }

    printf("%d\n", result);

    return 0;
}