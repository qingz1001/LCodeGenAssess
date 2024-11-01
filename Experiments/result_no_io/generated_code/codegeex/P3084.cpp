#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int n, m;
int left[MAXN], right[MAXN];
int *stack, *l, *r, top;

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    scanf("%d%d", &n, &m);
    stack = (int *)malloc(sizeof(int) * m);
    l = (int *)malloc(sizeof(int) * m);
    r = (int *)malloc(sizeof(int) * m);
    top = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &l[i], &r[i]);
        stack[i] = l[i];
        stack[i + m] = r[i];
    }

    qsort(stack, 2 * m, sizeof(int), cmp);

    for (int i = 0; i < 2 * m; i++) {
        if (top == 0 || stack[i] != stack[top - 1]) {
            stack[top++] = stack[i];
        }
    }

    for (int i = 0; i < m; i++) {
        left[i] = lower_bound(stack, top, l[i]) - stack;
        right[i] = lower_bound(stack, top, r[i]) - stack;
    }

    for (int i = 0; i < top; i++) {
        left[i] = lower_bound(stack, top, left[i]) - stack;
        right[i] = lower_bound(stack, top, right[i]) - stack;
    }

    int cnt = 0;
    int j = 0;
    for (int i = 0; i < top; i++) {
        while (j < m && right[j] <= i) {
            j++;
        }
        if (j < m && left[j] <= i) {
            cnt++;
            j++;
        }
    }

    if (j != m) {
        printf("-1\n");
    } else {
        printf("%d\n", cnt);
    }

    free(stack);
    free(l);
    free(r);

    return 0;
}