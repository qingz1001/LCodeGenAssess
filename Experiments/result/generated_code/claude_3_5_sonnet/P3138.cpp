#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_COORD 1000000

typedef struct {
    int x, y;
} Cow;

Cow cows[MAX_N];
int N;

int compare_x(const void* a, const void* b) {
    return ((Cow*)a)->x - ((Cow*)b)->x;
}

int compare_y(const void* a, const void* b) {
    return ((Cow*)a)->y - ((Cow*)b)->y;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min_max_cows() {
    int result = N;
    
    for (int i = 0; i < N; i++) {
        int a = cows[i].x + 1;
        if (a % 2 != 0) a++;
        
        for (int j = 0; j < N; j++) {
            int b = cows[j].y + 1;
            if (b % 2 != 0) b++;
            
            int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
            
            for (int k = 0; k < N; k++) {
                if (cows[k].x < a && cows[k].y < b) q1++;
                else if (cows[k].x < a && cows[k].y > b) q2++;
                else if (cows[k].x > a && cows[k].y < b) q3++;
                else q4++;
            }
            
            int max_cows = max(max(q1, q2), max(q3, q4));
            result = min(result, max_cows);
        }
    }
    
    return result;
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].x, &cows[i].y);
    }
    
    printf("%d\n", min_max_cows());
    
    return 0;
}