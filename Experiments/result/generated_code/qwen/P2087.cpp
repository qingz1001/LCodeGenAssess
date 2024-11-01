#include <stdio.h>
#include <stdlib.h>

#define MAXN 100010

int n, m, q;
int people[MAXN];
int visited[MAXN];

void init() {
    for (int i = 1; i <= n; i++) {
        people[i] = 1;
        visited[i] = 0;
    }
}

int query(int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; i++) {
        if (!visited[i]) {
            sum += people[i];
            visited[i] = 1;
        }
    }
    return sum;
}

void update(int i, int j) {
    people[j] += 1;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    init();

    for (int i = 0; i < q; i++) {
        char op[2];
        int a, b;
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d", &a, &b);
            update(a, b);
        } else if (op[0] == 'W') {
            scanf("%d %d", &a, &b);
            printf("%d\n", query(a, b));
        }
    }

    return 0;
}