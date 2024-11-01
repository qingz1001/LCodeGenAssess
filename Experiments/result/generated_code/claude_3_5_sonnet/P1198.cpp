#include <stdio.h>
#include <stdlib.h>

#define MAX_M 200000

typedef struct {
    int* data;
    int* max;
    int size;
    int capacity;
} Deque;

void init_deque(Deque* dq, int capacity) {
    dq->data = (int*)malloc(sizeof(int) * capacity);
    dq->max = (int*)malloc(sizeof(int) * capacity);
    dq->size = 0;
    dq->capacity = capacity;
}

void push_back(Deque* dq, int value) {
    if (dq->size == dq->capacity) {
        dq->capacity *= 2;
        dq->data = (int*)realloc(dq->data, sizeof(int) * dq->capacity);
        dq->max = (int*)realloc(dq->max, sizeof(int) * dq->capacity);
    }
    dq->data[dq->size] = value;
    while (dq->size > 0 && dq->max[dq->size - 1] < value) {
        dq->size--;
    }
    dq->max[dq->size++] = value;
}

int query(Deque* dq, int L) {
    return dq->max[dq->size - L];
}

int main() {
    int M, D;
    scanf("%d %d", &M, &D);

    Deque dq;
    init_deque(&dq, MAX_M);

    int last_answer = 0;

    for (int i = 0; i < M; i++) {
        char op;
        scanf(" %c", &op);

        if (op == 'A') {
            int n;
            scanf("%d", &n);
            int value = (n + last_answer) % D;
            push_back(&dq, value);
        } else if (op == 'Q') {
            int L;
            scanf("%d", &L);
            last_answer = query(&dq, L);
            printf("%d\n", last_answer);
        }
    }

    free(dq.data);
    free(dq.max);

    return 0;
}