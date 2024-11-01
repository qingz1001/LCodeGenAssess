#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int u, v, type;
} Operation;

typedef struct {
    Operation data[MAXN];
    int top;
} Stack;

Stack stack;
int n, m;
int *color;

void initialize() {
    stack.top = 0;
    color = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        color[i] = 0;
    }
}

void push(Operation op) {
    stack.data[++stack.top] = op;
}

Operation pop() {
    return stack.data[stack.top--];
}

int is_empty() {
    return stack.top == 0;
}

int main() {
    scanf("%d %d", &n, &m);
    initialize();

    for (int i = 1; i <= m; i++) {
        int k, t, u, v;
        scanf("%d %d", &k, &t);

        // Adjust stack to the state after operation k
        while (!is_empty() && stack.top >= k) {
            Operation op = pop();
            if (op.type == 1 || op.type == 2) {
                color[op.u] = 0;
                color[op.v] = 0;
            }
        }

        if (t == 1 || t == 2) {
            scanf("%d %d", &u, &v);
            if (color[u] == 0) {
                color[u] = t;
            } else if (color[u] == 1 && t == 2) {
                color[u] = 3;
            } else if (color[u] == 2 && t == 1) {
                color[u] = 3;
            } else if (color[u] == 3 && t == 1) {
                color[u] = 1;
            } else if (color[u] == 3 && t == 2) {
                color[u] = 2;
            }

            if (color[v] == 0) {
                color[v] = 4 - t;
            } else if (color[v] == 1 && 4 - t == 2) {
                color[v] = 3;
            } else if (color[v] == 2 && 4 - t == 1) {
                color[v] = 3;
            } else if (color[v] == 3 && 4 - t == 1) {
                color[v] = 1;
            } else if (color[v] == 3 && 4 - t == 2) {
                color[v] = 2;
            }

            Operation op = {u, v, t};
            push(op);
        } else if (t == 3) {
            scanf("%d", &u);
            Operation op = pop();
            if (op.u == u) {
                color[op.u] = 0;
                color[op.v] = 0;
            } else {
                color[op.v] = 0;
                color[op.u] = 0;
            }
        }

        int all_zero = 1;
        for (int j = 1; j <= n; j++) {
            if (color[j] != 0) {
                all_zero = 0;
                break;
            }
        }

        if (all_zero) {
            printf("excited\n");
        } else {
            printf("naive\n");
        }
    }

    free(color);
    return 0;
}