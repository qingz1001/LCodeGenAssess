#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500001

typedef struct {
    int data[MAX_SIZE];
    int size;
} Sequence;

void insert(Sequence *seq, int posi, int tot, int *values) {
    for (int i = seq->size; i >= posi + tot; --i) {
        seq->data[i] = seq->data[i - tot];
    }
    for (int i = 0; i < tot; ++i) {
        seq->data[posi + i] = values[i];
    }
    seq->size += tot;
}

void delete(Sequence *seq, int posi, int tot) {
    for (int i = posi; i < seq->size - tot; ++i) {
        seq->data[i] = seq->data[i + tot];
    }
    seq->size -= tot;
}

void makeSame(Sequence *seq, int posi, int tot, int c) {
    for (int i = posi; i < posi + tot; ++i) {
        seq->data[i] = c;
    }
}

void reverse(Sequence *seq, int posi, int tot) {
    int left = posi, right = posi + tot - 1;
    while (left < right) {
        int temp = seq->data[left];
        seq->data[left++] = seq->data[right];
        seq->data[right--] = temp;
    }
}

int getSum(Sequence *seq, int posi, int tot) {
    int sum = 0;
    for (int i = posi; i < posi + tot; ++i) {
        sum += seq->data[i];
    }
    return sum;
}

int maxSum(Sequence *seq) {
    int currentMax = 0, globalMax = 0;
    for (int i = 0; i < seq->size; ++i) {
        currentMax = (currentMax > 0) ? currentMax + seq->data[i] : seq->data[i];
        if (currentMax > globalMax) {
            globalMax = currentMax;
        }
    }
    return globalMax;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    Sequence seq;
    seq.size = N;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &seq.data[i]);
    }

    for (int i = 0; i < M; ++i) {
        char op[20];
        int posi, tot, c;
        scanf("%s", op);
        if (op[0] == 'I') {
            scanf("%d %d", &posi, &tot);
            int *values = (int *)malloc(tot * sizeof(int));
            for (int j = 0; j < tot; ++j) {
                scanf("%d", &values[j]);
            }
            insert(&seq, posi, tot, values);
            free(values);
        } else if (op[0] == 'D') {
            scanf("%d %d", &posi, &tot);
            delete(&seq, posi, tot);
        } else if (op[0] == 'M') {
            scanf("%d %d %d", &posi, &tot, &c);
            makeSame(&seq, posi, tot, c);
        } else if (op[0] == 'R') {
            scanf("%d %d", &posi, &tot);
            reverse(&seq, posi, tot);
        } else if (op[0] == 'G' && op[1] == 'E') {
            scanf("%d %d", &posi, &tot);
            printf("%d\n", getSum(&seq, posi, tot));
        } else if (op[0] == 'M' && op[1] == 'A') {
            printf("%d\n", maxSum(&seq));
        }
    }

    return 0;
}