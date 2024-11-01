#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_B 20

int N, B;
int preferences[MAX_N][MAX_B];
int capacity[MAX_B];

int check(int mid) {
    int assigned[MAX_B] = {0};
    for (int i = 0; i < N; i++) {
        int placed = 0;
        for (int j = 0; j < mid; j++) {
            int barn = preferences[i][j] - 1;
            if (assigned[barn] < capacity[barn]) {
                assigned[barn]++;
                placed = 1;
                break;
            }
        }
        if (!placed) return 0;
    }
    return 1;
}

int binary_search() {
    int left = 1, right = B;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &B);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &preferences[i][j]);
        }
    }
    
    for (int i = 0; i < B; i++) {
        scanf("%d", &capacity[i]);
    }
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}