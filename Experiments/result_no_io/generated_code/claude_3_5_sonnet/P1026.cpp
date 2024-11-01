#include <stdio.h>
#include <string.h>

#define MAX_LEN 201
#define MAX_DICT 6
#define MAX_WORD 20

char str[MAX_LEN];
char dict[MAX_DICT][MAX_WORD];
int dp[MAX_LEN][41];
int n, k, s;

int max(int a, int b) {
    return a > b ? a : b;
}

int count_words(int start) {
    int count = 0;
    for (int i = 0; i < s; i++) {
        if (strncmp(str + start, dict[i], strlen(dict[i])) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int p;
    scanf("%d %d", &p, &k);
    
    for (int i = 0; i < p; i++) {
        char temp[21];
        scanf("%s", temp);
        strcat(str, temp);
    }
    n = strlen(str);
    
    scanf("%d", &s);
    for (int i = 0; i < s; i++) {
        scanf("%s", dict[i]);
    }
    
    for (int i = 0; i < n; i++) {
        dp[i][1] = count_words(i);
    }
    
    for (int j = 2; j <= k; j++) {
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < i; m++) {
                dp[i][j] = max(dp[i][j], dp[m][j-1] + count_words(i));
            }
        }
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = max(result, dp[i][k]);
    }
    
    printf("%d\n", result);
    
    return 0;
}