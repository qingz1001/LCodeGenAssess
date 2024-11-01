#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 200
#define MAX_C 500000
#define MAX_M 200000

int R, C, M;
int P[MAX_R + 1][MAX_C + 1];
long long sum[MAX_R + 1][MAX_C + 1];
int x1[MAX_M], y1[MAX_M], x2[MAX_M], y2[MAX_M];
long long H[MAX_M];

void preprocess() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + P[i][j];
        }
    }
}

long long query(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int binary_search(int day) {
    int left = 1, right = (x2[day] - x1[day] + 1) * (y2[day] - y1[day] + 1);
    long long total = query(x1[day], y1[day], x2[day], y2[day]);
    
    if (total < H[day]) return -1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int count = 0;
        long long sum = 0;
        
        for (int i = x1[day]; i <= x2[day] && count < mid; i++) {
            for (int j = y1[day]; j <= y2[day] && count < mid; j++) {
                sum += P[i][j];
                count++;
            }
        }
        
        if (sum >= H[day]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d %d", &R, &C, &M);
    
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &P[i][j]);
        }
    }
    
    preprocess();
    
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d %lld", &x1[i], &y1[i], &x2[i], &y2[i], &H[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int result = binary_search(i);
        if (result == -1) {
            printf("Poor QLW\n");
        } else {
            printf("%d\n", result);
        }
    }
    
    return 0;
}