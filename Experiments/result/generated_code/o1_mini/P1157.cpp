#include <stdio.h>

void combine(int n, int r, int start, int depth, int comb[]) {
    if (depth == r) {
        for(int i = 0; i < r; i++) {
            printf("%3d", comb[i]);
        }
        printf("\n");
        return;
    }
    for(int i = start; i <= n - r + depth +1; i++) {
        comb[depth] = i;
        combine(n, r, i +1, depth +1, comb);
    }
}

int main(){
    int n, r;
    scanf("%d %d", &n, &r);
    if(r ==0){
        return 0;
    }
    int comb[r];
    combine(n, r, 1, 0, comb);
    return 0;
}