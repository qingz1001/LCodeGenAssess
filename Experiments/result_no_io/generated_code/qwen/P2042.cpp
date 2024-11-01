#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500005
#define MAX_M 20000
#define MAX_INSERT 4000000

typedef struct {
    int value;
    int next;
} Node;

Node nodes[MAX_N * 2];
int head[MAX_N], pos = 1;
int n, m;

void init() {
    for (int i = 0; i <= n; i++) {
        head[i] = -1;
    }
}

void insert(int posi, int tot, int *values) {
    for (int i = 0; i < tot; i++) {
        nodes[pos].value = values[i];
        nodes[pos].next = head[posi + 1];
        head[posi + 1] = pos++;
    }
}

void delete(int posi, int tot) {
    int p = head[posi + 1];
    for (int i = 0; i < tot; i++) {
        head[posi + 1] = nodes[p].next;
        free(p);
        p = head[posi + 1];
    }
}

void make_same(int posi, int tot, int c) {
    int p = head[posi + 1];
    for (int i = 0; i < tot; i++) {
        nodes[p].value = c;
        p = nodes[p].next;
    }
}

void reverse(int posi, int tot) {
    int p = head[posi + 1];
    int stack[MAX_TOT], top = 0;
    for (int i = 0; i < tot; i++) {
        stack[top++] = nodes[p].value;
        p = nodes[p].next;
    }
    p = head[posi + 1];
    for (int i = 0; i < tot; i++) {
        nodes[p].value = stack[--top];
        p = nodes[p].next;
    }
}

int get_sum(int posi, int tot) {
    int sum = 0;
    int p = head[posi + 1];
    for (int i = 0; i < tot; i++) {
        sum += nodes[p].value;
        p = nodes[p].next;
    }
    return sum;
}

int max_sum() {
    int max_sum = -1e9;
    int current_sum = 0;
    int p = head[0];
    while (p != -1) {
        current_sum += nodes[p].value;
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        if (current_sum < 0) {
            current_sum = 0;
        }
        p = nodes[p].next;
    }
    return max_sum;
}

int main() {
    scanf("%d %d", &n, &m);
    init();
    int initial_values[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &initial_values[i]);
        insert(i, 1, &initial_values[i]);
    }

    for (int i = 0; i < m; i++) {
        char operation[10];
        int posi, tot, c;
        scanf("%s", operation);
        if (operation[0] == 'I') {
            scanf("%d %d", &posi, &tot);
            int values[tot];
            for (int j = 0; j < tot; j++) {
                scanf("%d", &values[j]);
            }
            insert(posi, tot, values);
        } else if (operation[0] == 'D') {
            scanf("%d %d", &posi, &tot);
            delete(posi, tot);
        } else if (operation[0] == 'M') {
            scanf("%d %d %d", &posi, &tot, &c);
            make_same(posi, tot, c);
        } else if (operation[0] == 'R') {
            scanf("%d %d", &posi, &tot);
            reverse(posi, tot);
        } else if (operation[0] == 'G') {
            scanf("%d %d", &posi, &tot);
            printf("%d\n", get_sum(posi, tot));
        } else if (operation[0] == 'X') {
            printf("%d\n", max_sum());
        }
    }

    return 0;
}