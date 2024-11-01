#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXR 40
#define MAXC 26
#define MAXK 1000

int R, C, K;
int kr, kc;
int kr2[MAXK], kc2[MAXK];

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int abs(int x) { return x < 0 ? -x : x; }

int kingMove(int r1, int c1, int r2, int c2) {
    return max(abs(r1-r2), abs(c1-c2));
}

int knightMove(int r1, int c1, int r2, int c2) {
    int dr = abs(r1-r2), dc = abs(c1-c2);
    return (dr+dc+max(dr,dc))/3;
}

int main() {
    scanf("%d %d", &R, &C);
    char col;
    scanf(" %c %d", &col, &kr);
    kc = col - 'A' + 1;
    
    while(scanf(" %c %d", &col, &kr2[K]) != EOF) {
        kc2[K] = col - 'A' + 1;
        K++;
    }

    int result = INT_MAX;
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            int moves = 0;
            int kingDist = kingMove(kr, kc, r, c);
            for(int i = 0; i < K; i++) {
                int knightDist = knightMove(kr2[i], kc2[i], r, c);
                moves += min(knightDist, kingDist + knightMove(kr, kc, kr2[i], kc2[i]));
            }
            result = min(result, moves);
        }
    }

    printf("%d\n", result);
    return 0;
}