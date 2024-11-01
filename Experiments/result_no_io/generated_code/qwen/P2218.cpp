#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_COORD 1000000000

int main() {
    int N;
    scanf("%d", &N);
    int X[MAX_N], Y[MAX_N];
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    
    int minX = MAX_COORD, minY = MAX_COORD, maxX = -MAX_COORD, maxY = -MAX_COORD;
    
    for (int i = 0; i < N; i++) {
        if (X[i] < minX) minX = X[i];
        if (X[i] > maxX) maxX = X[i];
        if (Y[i] < minY) minY = Y[i];
        if (Y[i] > maxY) maxY = Y[i];
    }
    
    int width = maxX - minX + 1;
    int height = maxY - minY + 1;
    int L = (width > height) ? width : height;
    
    printf("%d\n", L);
    
    return 0;
}