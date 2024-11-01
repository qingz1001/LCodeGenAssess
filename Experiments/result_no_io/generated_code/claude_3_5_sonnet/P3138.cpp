#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_COORD 1000000

typedef struct {
    int x, y;
} Cow;

Cow cows[MAX_N];
int N;

int compare_x(const void *a, const void *b) {
    return ((Cow*)a)->x - ((Cow*)b)->x;
}

int compare_y(const void *a, const void *b) {
    return ((Cow*)a)->y - ((Cow*)b)->y;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int solve() {
    int result = N;
    int left[MAX_N + 1] = {0};
    int right[MAX_N + 1] = {0};
    
    qsort(cows, N, sizeof(Cow), compare_x);
    
    for (int i = 0; i < N; i++) {
        right[cows[i].y]++;
    }
    
    for (int i = 0; i < N; i++) {
        if (i > 0 && cows[i].x == cows[i-1].x) continue;
        
        int a = cows[i].x + 1;
        if (a % 2) a++;
        
        memset(left, 0, sizeof(left));
        for (int j = 0; j < i; j++) {
            left[cows[j].y]++;
            right[cows[j].y]--;
        }
        
        int top_left = 0, top_right = 0;
        int bottom_left = 0, bottom_right = 0;
        
        for (int b = 0; b <= MAX_COORD; b += 2) {
            result = min(result, max(max(top_left, top_right), max(bottom_left, bottom_right)));
            
            if (b >= MAX_COORD) break;
            
            for (int j = b + 1; j <= MAX_COORD && j < b + 3; j++) {
                top_left += left[j];
                top_right += right[j];
                bottom_left -= left[j];
                bottom_right -= right[j];
            }
        }
    }
    
    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].x, &cows[i].y);
    }
    
    printf("%d\n", solve());
    
    return 0;
}