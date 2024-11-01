#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 5001

int a, b, c;
int cube[MAX_SIZE][MAX_SIZE];
int sum[MAX_SIZE][MAX_SIZE];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    int result = 0;
    for (int k = 1; k <= c; k++) {
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + cube[i][j];
            }
        }
        
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                if (cube[i][j] == 0) continue;
                int x = i, y = j;
                while (x <= a && y <= b && sum[x][y] - sum[i-1][y] - sum[x][j-1] + sum[i-1][j-1] == (x-i+1) * (y-j+1)) {
                    x++; y++;
                }
                x--; y--;
                result = max(result, min(x-i+1, y-j+1));
            }
        }
    }
    return result;
}

int main() {
    int D;
    scanf("%d", &D);
    while (D--) {
        scanf("%d %d %d", &a, &b, &c);
        for (int k = 1; k <= c; k++) {
            for (int i = 1; i <= a; i++) {
                for (int j = 1; j <= b; j++) {
                    scanf("%d", &cube[i][j]);
                }
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}