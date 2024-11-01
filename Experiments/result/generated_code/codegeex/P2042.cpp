#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int a[MAXN];

void insert(int posi, int tot, int c[]) {
    for (int i = 0; i < tot; i++) {
        a[posi + i] = c[i];
    }
}

void delete(int posi, int tot) {
    for (int i = 0; i < tot; i++) {
        a[posi + i] = 0;
    }
}

void make_same(int posi, int tot, int c) {
    for (int i = 0; i < tot; i++) {
        a[posi + i] = c;
    }
}

void reverse(int posi, int tot) {
    for (int i = 0; i < tot / 2; i++) {
        int temp = a[posi + i];
        a[posi + i] = a[posi + tot - i - 1];
        a[posi + tot - i - 1] = temp;
    }
}

int get_sum(int posi, int tot) {
    int sum = 0;
    for (int i = 0; i < tot; i++) {
        sum += a[posi + i];
    }
    return sum;
}

int max_sum() {
    int max_sum = a[0];
    int current_sum = a[0];
    for (int i = 1; i < MAXN; i++) {
        current_sum = (current_sum > 0) ? current_sum + a[i] : a[i];
        max_sum = (current_sum > max_sum) ? current_sum : max_sum;
    }
    return max_sum;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < M; i++) {
        char op[20];
        int posi, tot, c;
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0) {
            scanf("%d %d", &posi, &tot);
            int *c = (int *)malloc(tot * sizeof(int));
            for (int j = 0; j < tot; j++) {
                scanf("%d", &c[j]);
            }
            insert(posi, tot, c);
            free(c);
        } else if (strcmp(op, "DELETE") == 0) {
            scanf("%d %d", &posi, &tot);
            delete(posi, tot);
        } else if (strcmp(op, "MAKE-SAME") == 0) {
            scanf("%d %d %d", &posi, &tot, &c);
            make_same(posi, tot, c);
        } else if (strcmp(op, "REVERSE") == 0) {
            scanf("%d %d", &posi, &tot);
            reverse(posi, tot);
        } else if (strcmp(op, "GET-SUM") == 0) {
            scanf("%d %d", &posi, &tot);
            printf("%d\n", get_sum(posi, tot));
        } else if (strcmp(op, "MAX-SUM") == 0) {
            printf("%d\n", max_sum());
        }
    }

    return 0;
}