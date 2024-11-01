#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int pos[MAXN];
int visited[MAXN];

void update(int x) {
    if (!visited[x]) {
        visited[x] = 1;
        printf("%d\n", 1);
    } else {
        printf("0\n");
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        pos[i] = 1;
    }

    while (q--) {
        char op;
        int a, b;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d", &a, &b);
            pos[a] = b;
        } else if (op == 'W') {
            scanf("%d %d", &a, &b);
            int sum = 0;
            for (int i = a; i <= b; i++) {
                sum += update(pos[i]);
            }
        }
    }

    return 0;
}