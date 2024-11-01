#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1100000
#define MAX_M 1000

char library[MAX_M][MAX_LEN];
char article[MAX_LEN];
int m, n;

int is_familiar(int l, int start, int end) {
    for (int i = 0; i < m; i++) {
        int len = strlen(library[i]);
        for (int j = 0; j <= len - (end - start); j++) {
            if (strncmp(library[i] + j, article + start, end - start) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int check(int l) {
    int len = strlen(article);
    int dp[MAX_LEN] = {0};
    
    for (int i = l - 1; i < len; i++) {
        if (is_familiar(l, i - l + 1, i + 1)) {
            dp[i] = (i >= l ? dp[i-l] : 0) + l;
        } else if (i > 0) {
            dp[i] = dp[i-1];
        }
    }
    
    return dp[len-1] >= len * 0.9;
}

int binary_search() {
    int left = 1, right = strlen(article);
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        scanf("%s", library[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%s", article);
        printf("%d\n", binary_search());
    }
    
    return 0;
}