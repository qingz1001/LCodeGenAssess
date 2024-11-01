#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int h, r1, r2;
} Bowl;

int n;
Bowl bowls[9];
int min_height = INT_MAX;

void swap(Bowl *a, Bowl *b) {
    Bowl temp = *a;
    *a = *b;
    *b = temp;
}

void calculate_height(int *order) {
    int height = bowls[order[0]].h;
    for (int i = 1; i < n; i++) {
        int top_r = bowls[order[i-1]].r2;
        int bottom_r = bowls[order[i]].r1;
        if (top_r <= bottom_r) {
            height += bowls[order[i]].h;
        } else {
            height += bowls[order[i]].h - (top_r - bottom_r);
        }
    }
    if (height < min_height) {
        min_height = height;
    }
}

void permute(int *order, int l, int r) {
    if (l == r) {
        calculate_height(order);
        return;
    }
    for (int i = l; i <= r; i++) {
        swap(&bowls[order[l]], &bowls[order[i]]);
        permute(order, l+1, r);
        swap(&bowls[order[l]], &bowls[order[i]]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }

    int order[9];
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    permute(order, 0, n-1);

    printf("%d\n", (int)round(min_height));

    return 0;
}