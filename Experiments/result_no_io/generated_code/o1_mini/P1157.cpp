#include <stdio.h>

int n, r;
int comb[20];

void backtrack(int start, int depth) {
    if (depth == r) {
        for(int i = 0; i < r; i++) {
            printf("%3d", comb[i]);
        }
        printf("\n");
        return;
    }
    for(int i = start; i <= n - (r - depth) + 1; i++) {
        comb[depth] = i;
        backtrack(i + 1, depth + 1);
    }
}

int main(){
    scanf("%d %d", &n, &r);
    if(r > 0){
        backtrack(1, 0);
    }
    return 0;
}