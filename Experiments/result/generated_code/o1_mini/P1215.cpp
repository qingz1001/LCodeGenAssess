#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a, b, c;
} State;

int aMax, bMax, cMax;
int visited[21][21][21];
int possible[21];
int count = 0;

void dfs(int a, int b, int c) {
    if (visited[a][b][c]) return;
    visited[a][b][c] = 1;
    if (a == 0) {
        possible[c] = 1;
    }
    // Pour A -> B
    if (a > 0 && b < bMax) {
        int pour = a < (bMax - b) ? a : (bMax - b);
        dfs(a - pour, b + pour, c);
    }
    // Pour A -> C
    if (a > 0 && c < cMax) {
        int pour = a < (cMax - c) ? a : (cMax - c);
        dfs(a - pour, b, c + pour);
    }
    // Pour B -> A
    if (b > 0 && a < aMax) {
        int pour = b < (aMax - a) ? b : (aMax - a);
        dfs(a + pour, b - pour, c);
    }
    // Pour B -> C
    if (b > 0 && c < cMax) {
        int pour = b < (cMax - c) ? b : (cMax - c);
        dfs(a, b - pour, c + pour);
    }
    // Pour C -> A
    if (c > 0 && a < aMax) {
        int pour = c < (aMax - a) ? c : (aMax - a);
        dfs(a + pour, b, c - pour);
    }
    // Pour C -> B
    if (c > 0 && b < bMax) {
        int pour = c < (bMax - b) ? c : (bMax - b);
        dfs(a, b + pour, c - pour);
    }
}

int cmp(const void *x, const void *y) {
    return (*(int*)x - *(int*)y);
}

int main(){
    scanf("%d %d %d", &aMax, &bMax, &cMax);
    dfs(0, 0, cMax);
    int results[21];
    int resCount = 0;
    for(int i=0;i<=cMax;i++) {
        if(possible[i]){
            results[resCount++] = i;
        }
    }
    qsort(results, resCount, sizeof(int), cmp);
    for(int i=0;i<resCount;i++) {
        if(i>0) printf(" ");
        printf("%d", results[i]);
    }
    printf("\n");
    return 0;
}