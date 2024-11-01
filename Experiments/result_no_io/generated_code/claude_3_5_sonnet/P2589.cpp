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

double calculate_height(int *order) {
    double height = 0;
    double prev_r2 = 0;
    for (int i = 0; i < n; i++) {
        Bowl b = bowls[order[i]];
        if (i == 0 || b.r2 <= prev_r2) {
            height += b.h;
        } else {
            double overlap = (b.r2 - prev_r2) * b.h / (b.r2 - b.r1);
            height += b.h - overlap;
        }
        prev_r2 = b.r2;
    }
    return height;
}

void dfs(int depth, int *order) {
    if (depth == n) {
        double height = calculate_height(order);
        if (height < min_height) {
            min_height = height;
        }
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            order[depth] = i;
            dfs(depth + 1, order);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    
    int order[MAX_N];
    dfs(0, order);
    
    printf("%d\n", (int)round(min_height));
    
    return 0;
}