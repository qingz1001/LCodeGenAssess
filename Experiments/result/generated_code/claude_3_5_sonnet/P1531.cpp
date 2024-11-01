#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int scores[MAX_N + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int query(int left, int right) {
    int max_score = scores[left];
    for (int i = left + 1; i <= right; i++) {
        max_score = max(max_score, scores[i]);
    }
    return max_score;
}

void update(int id, int new_score) {
    if (scores[id] < new_score) {
        scores[id] = new_score;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &scores[i]);
    }

    for (int i = 0; i < m; i++) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);

        if (op == 'Q') {
            printf("%d\n", query(a, b));
        } else if (op == 'U') {
            update(a, b);
        }
    }

    return 0;
}