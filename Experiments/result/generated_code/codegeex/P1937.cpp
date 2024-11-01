#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Request;

int cmp(const void *a, const void *b) {
    Request *reqA = (Request *)a;
    Request *reqB = (Request *)b;
    if (reqA->end == reqB->end) {
        return reqA->start - reqB->start;
    }
    return reqA->end - reqB->end;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *capacities = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &capacities[i]);
    }

    Request *requests = (Request *)malloc(M * sizeof(Request));
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
        requests[i].start--;
        requests[i].end--;
    }

    qsort(requests, M, sizeof(Request), cmp);

    int *max_cows = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        max_cows[i] = capacities[i];
    }

    int *stack = (int *)malloc(N * sizeof(int));
    int top = 0;

    int result = 0;
    for (int i = 0; i < M; i++) {
        int start = requests[i].start;
        int end = requests[i].end;

        while (top > 0 && start < stack[top - 1]) {
            top--;
        }

        if (top > 0) {
            max_cows[top - 1] -= (end - start + 1);
        }

        stack[top++] = end;

        int max_cows_in_range = capacities[end] - max_cows[top - 1];
        if (max_cows_in_range > 0) {
            result++;
        }
    }

    printf("%d\n", result);

    free(capacities);
    free(requests);
    free(max_cows);
    free(stack);

    return 0;
}