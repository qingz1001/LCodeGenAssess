#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 200001
#define MAX_OPERATIONS 5001

int scores[MAX_STUDENTS];
int n, m;

void update(int a, int b) {
    if (scores[a] < b) {
        scores[a] = b;
    }
}

int query(int a, int b) {
    int max_score = 0;
    for (int i = a; i <= b; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
        }
    }
    return max_score;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &scores[i]);
    }

    for (int i = 0; i < m; i++) {
        char c;
        int a, b;
        scanf(" %c %d %d", &c, &a, &b);
        if (c == 'Q') {
            printf("%d\n", query(a, b));
        } else if (c == 'U') {
            update(a, b);
        }
    }

    return 0;
}