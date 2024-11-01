#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int scores[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &scores[i]);
    }

    while (m--) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);
        if (op == 'Q') {
            int max = scores[a];
            for (int i = a + 1; i <= b; i++) {
                if (scores[i] > max) {
                    max = scores[i];
                }
            }
            printf("%d\n", max);
        } else if (op == 'U') {
            if (scores[a] < b) {
                scores[a] = b;
            }
        }
    }

    return 0;
}