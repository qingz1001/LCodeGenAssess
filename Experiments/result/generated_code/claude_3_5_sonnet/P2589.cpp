#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 9

typedef struct {
    int h, r1, r2;
} Bowl;

Bowl bowls[MAX_N];
int n;
int used[MAX_N];
double min_height = 1e9;

int cmp(const void *a, const void *b) {
    Bowl *ba = (Bowl *)a;
    Bowl *bb = (Bowl *)b;
    return (bb->r2 - bb->r1) - (ba->r2 - ba->r1);
}

void dfs(int depth, double height, double top_r1, double top_r2) {
    if (depth == n) {
        if (height < min_height) {
            min_height = height;
        }
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            double new_height = height + bowls[i].h;
            double new_top_r1 = bowls[i].r1;
            double new_top_r2 = bowls[i].r2;
            
            if (depth > 0) {
                double ratio = (double)(top_r2 - bowls[i].r2) / (top_r2 - top_r1);
                new_height -= bowls[i].h * ratio;
            }
            
            if (new_height < min_height) {
                dfs(depth + 1, new_height, new_top_r1, new_top_r2);
            }
            
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    
    qsort(bowls, n, sizeof(Bowl), cmp);
    
    dfs(0, 0, 0, 0);
    
    printf("%d\n", (int)round(min_height));
    
    return 0;
}