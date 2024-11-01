#include <stdio.h>
#include <string.h>

#define MAX_W 30005
#define MAX_DIGITS 205

char result[MAX_DIGITS];
int dp[MAX_W][16];

void add(char *a, char *b) {
    char sum[MAX_DIGITS] = {0};
    int carry = 0, i = strlen(a) - 1, j = strlen(b) - 1, k = 0;
    
    while (i >= 0 || j >= 0 || carry) {
        int s = carry;
        if (i >= 0) s += a[i--] - '0';
        if (j >= 0) s += b[j--] - '0';
        sum[k++] = s % 10 + '0';
        carry = s / 10;
    }
    
    for (i = k - 1, j = 0; i >= 0; i--, j++) {
        a[j] = sum[i];
    }
    a[j] = '\0';
}

int main() {
    int k, w, i, j, l;
    scanf("%d %d", &k, &w);
    
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < (1 << k); i++) {
        dp[k][i] = 1;
    }
    
    for (i = k + 1; i <= w; i++) {
        for (j = 0; j < (1 << k); j++) {
            for (l = j + 1; l < (1 << k); l++) {
                dp[i][j] += dp[i-k][l];
            }
        }
    }
    
    result[0] = '0';
    result[1] = '\0';
    
    for (i = k; i <= w; i++) {
        for (j = 1; j < (1 << k); j++) {
            char temp[MAX_DIGITS];
            sprintf(temp, "%d", dp[i][j]);
            add(result, temp);
        }
    }
    
    printf("%s\n", result);
    
    return 0;
}