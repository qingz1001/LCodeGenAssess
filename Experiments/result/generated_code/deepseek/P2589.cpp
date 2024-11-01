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

int calculate_height(Bowl *order) {
    int height = order[0].h;
    for (int i = 1; i < n; i++) {
        int top_r = order[i-1].r2;
        int bottom_r = order[i].r1;
        if (top_r <= bottom_r) {
            height += order[i].h;
        } else {
            height += order[i].h - (top_r - bottom_r);
        }
    }
    return height;
}

void permute(Bowl *order, int l, int r) {
    if (l == r) {
        int height = calculate_height(order);
        if (height < min_height) {
            min_height = height;
        }
    } else {
        for (int i = l; i <= r; i++) {
            swap(&order[l], &order[i]);
            permute(order, l+1, r);
            swap(&order[l], &order[i]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    permute(bowls, 0, n-1);
    printf("%d\n", min_height);
    return 0;
}