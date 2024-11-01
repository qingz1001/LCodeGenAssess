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
        int assigned_flag = 0;
        for (int j = 0; j < mid; j++) {
            int barn = preferences[i][j] - 1;
            if (assigned[barn] < capacity[barn]) {
                assigned[barn]++;
                assigned_flag = 1;
                break;
            }
        }
        if (!assigned_flag) return 0;
    }
    return 1;
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
    
    int left = 1, right = B, result = B;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}