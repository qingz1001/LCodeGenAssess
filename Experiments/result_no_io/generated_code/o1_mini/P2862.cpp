#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Clover;

// Comparator for sorting clovers by x, then y
int compare(const void *a, const void *b) {
    Clover *c1 = (Clover *)a;
    Clover *c2 = (Clover *)b;
    if (c1->x != c2->x)
        return c1->x - c2->x;
    return c1->y - c2->y;
}

int N, C;
Clover clovers[500];
int sorted_y[500];

int check(int L) {
    int left = 0, right = 0;
    for (left = 0; left < N; left++) {
        // Move right as far as clovers[right].x <= clovers[left].x + L -1
        while (right < N && clovers[right].x <= clovers[left].x + L -1)
            right++;
        // Collect y's between left and right-1
        int m = right - left;
        for(int i = 0; i < m; i++) {
            sorted_y[i] = clovers[left + i].y;
        }
        // Sort the y's
        qsort(sorted_y, m, sizeof(int), (__compar_fn_t)(int (*)(const void*, const void*)) (int (*)(const int*, const int*)) 
            [](const int *a, const int *b) -> int {
                return (*a) - (*b);
            });
        // Sliding window on y
        int i_y = 0, j_y = 0;
        for(i_y = 0; i_y < m; i_y++) {
            while(j_y < m && sorted_y[j_y] <= sorted_y[i_y] + L -1)
                j_y++;
            if(j_y - i_y >= C)
                return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d %d", &C, &N);
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &clovers[i].x, &clovers[i].y);
    }
    qsort(clovers, N, sizeof(Clover), compare);
    int low = 0, high = 10000, mid, res = 10000;
    while(low <= high){
        mid = low + (high - low) / 2;
        if(check(mid)){
            res = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    printf("%d\n", res);
    return 0;
}