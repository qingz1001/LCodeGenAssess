#include <stdio.h>
#include <stdbool.h>

#define MAX 21

bool visited[MAX][MAX][MAX];
bool possible[MAX];

void dfs(int a, int b, int c, int A, int B, int C) {
    if (visited[a][b][c]) return;
    visited[a][b][c] = true;
    if (a == 0) possible[c] = true;

    // Pour from a to b
    if (a > 0 && b < B) {
        int pour = (a < (B - b)) ? a : (B - b);
        dfs(a - pour, b + pour, c, A, B, C);
    }
    // Pour from a to c
    if (a > 0 && c < C) {
        int pour = (a < (C - c)) ? a : (C - c);
        dfs(a - pour, b, c + pour, A, B, C);
    }
    // Pour from b to a
    if (b > 0 && a < A) {
        int pour = (b < (A - a)) ? b : (A - a);
        dfs(a + pour, b - pour, c, A, B, C);
    }
    // Pour from b to c
    if (b > 0 && c < C) {
        int pour = (b < (C - c)) ? b : (C - c);
        dfs(a, b - pour, c + pour, A, B, C);
    }
    // Pour from c to a
    if (c > 0 && a < A) {
        int pour = (c < (A - a)) ? c : (A - a);
        dfs(a + pour, b, c - pour, A, B, C);
    }
    // Pour from c to b
    if (c > 0 && b < B) {
        int pour = (c < (B - b)) ? c : (B - b);
        dfs(a, b + pour, c - pour, A, B, C);
    }
}

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    dfs(0, 0, C, A, B, C);

    for (int i = 0; i <= C; i++) {
        if (possible[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}