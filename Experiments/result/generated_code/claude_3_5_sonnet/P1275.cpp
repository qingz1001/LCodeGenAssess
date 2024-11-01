#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 100
#define MAX_M 100

int board1[MAX_N][MAX_M], board2[MAX_N][MAX_M];
int n, m;

bool check_rows() {
    int diff[MAX_M] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            diff[j] ^= board1[i][j] ^ board2[i][j];
        }
    }
    
    for (int j = 1; j < m; j++) {
        if (diff[j] != diff[0]) return false;
    }
    return true;
}

bool check_columns() {
    int count1[2] = {0}, count2[2] = {0};
    for (int j = 0; j < m; j++) {
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++) {
            sum1 += board1[i][j];
            sum2 += board2[i][j];
        }
        count1[sum1 % 2]++;
        count2[sum2 % 2]++;
    }
    return (count1[0] == count2[0] && count1[1] == count2[1]);
}

int main() {
    int k;
    scanf("%d", &k);
    
    while (k--) {
        scanf("%d %d", &n, &m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board1[i][j]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board2[i][j]);
            }
        }
        
        if (check_rows() && check_columns()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}