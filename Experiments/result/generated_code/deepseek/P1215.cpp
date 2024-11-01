#include <stdio.h>
#include <stdlib.h>

#define MAX_C 20

int a, b, c;
int possible[MAX_C + 1];

void dfs(int x, int y, int z) {
    if (possible[z] == 0) {
        possible[z] = 1;
        dfs(x, y, z);
        dfs(x, z, y);
        dfs(y, x, z);
        dfs(y, z, x);
        dfs(z, x, y);
        dfs(z, y, x);
    }
}

int main() {
    scanf("%d %d %d", &a, &b, &c);
    
    dfs(0, 0, c);
    
    for (int i = 0; i <= c; i++) {
        if (possible[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}